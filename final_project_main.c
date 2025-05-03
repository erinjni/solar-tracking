#include <ti/devices/msp/msp.h>
#include "test_helper.h"
#include "ti_msp_dl_config.h"

// Define Statements
#define UPPER_CLOCKWISE (150) // Parameter for rotating upper servo clockwise
#define UPPER_ANTICLOCKWISE (-150) // Parameter for rotating upper servo anti clockwise

#define LOWER_CLOCKWISE (150) // Parameter for rotating lower servo clockwise
#define LOWER_ANTICLOCKWISE (-150) // Parameter for rotating lower servo anti clockwise

#define IDLE_TIME (3270) // Set this parameter to dictate how long idle time between orients should be

// Operation states
enum current_state_enum {
    IDLE = 0,            // State for tracking lower servo clockwise
    CHECK_LOWER = 1,                // State for checking which direction lower servo should move
    CHECK_UPPER = 2                 // State for checking which direction upper servo should move
};

// TIMG0 Variables
int timerTicked = 0; // flag for timer ISR wakeup

volatile bool gCheckADC = false;
volatile float adc0, adc1, adc2, adc3, adc4, adc5;

/* -------------------------------------------------------------------------------------------------------- */

/**
 * main.c
 */
int main(void)
{
    // Initialise processor and GPIO
    InitializeProcessor();
    InitializeGPIO();

    // Initialise Timer modules G0, A0, and A1
    InitializeTimerG0();
    InitializeTimerA1_PWM();
    InitializeTimerA0_PWM();

    SYSCFG_DL_init();
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
    DL_ADC12_enableConversions(ADC12_0_INST);

    // Set up timer G0 for processor wake up
    NVIC_EnableIRQ(TIMG0_INT_IRQn); // Enable the timer interrupt
    TIMG0->COUNTERREGS.LOAD = IDLE_TIME; // 327 should be half a second, thus 3270 should be a full second.

    // Enable timer A1 and A0
    TIMA1->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_EN_ENABLED;
    TIMA0->COUNTERREGS.CTRCTL |= GPTIMER_CTRCTL_EN_ENABLED;

    // Initialise and set operation state to check upper servo. This will start the system by first rotating panel up/down
    enum current_state_enum requested_op;
    requested_op = CHECK_UPPER;

    // Initialise servo movement to zero in both axis
    TIMA1->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
    TIMA1->COUNTERREGS.CC_01[0] = 0;  // Set PWM

    TIMA0->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
    TIMA0->COUNTERREGS.CC_01[0] = 0;  // Set PWM

    // Begin main while loop
    while (1){

        switch (requested_op){

            case CHECK_LOWER:

                while(1){
                    // Get values of photo cell and compare the cells in the horizontally mounted array.
                    /* !!! Your code goes here !!! */
                    DL_ADC12_startConversion(ADC12_0_INST);
                    while (!gCheckADC) { __WFE(); }
                    gCheckADC = false;

                    float horizontal_adc[3] = {adc0, adc1, adc2};
                    float min_val = horizontal_adc[0];
                    int min_idx = 0;
                    for (int i = 1; i < 3; i++) {
                        if (horizontal_adc[i] < min_val) {
                            min_val = horizontal_adc[i];
                            min_idx = i;
                        }
                    }

                    // If left side cell is getting most intense light, rotate anti clockwise
                    if (min_idx == 0){                         /* !!! REPLACE THE 1 WITH YOUR LOGIC FOR SEEING IF LEFT IS MOST INTENSE !!! */

                        // Upper servo set to no movement
                        TIMA1->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA1->COUNTERREGS.CC_01[0] = 3000 + 0;  // Set PWM

                        // Lower servo set to track anti clockwise
                        TIMA0->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA0->COUNTERREGS.CC_01[0] = 3000 + LOWER_ANTICLOCKWISE;  // Set PWM
                    }

                    // If right side cell is getting most intense light, rotate clockwise
                    if (min_idx == 2){                         /* !!! REPLACE THE 1 WITH YOUR LOGIC FOR SEEING IF RIGHT IS MOST INTENSE !!! */

                        // Upper servo set to no movement
                        TIMA1->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA1->COUNTERREGS.CC_01[0] = 3000 + 0;  // Set PWM

                        // Lower servo set to track clockwise
                        TIMA0->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA0->COUNTERREGS.CC_01[0] = 3000 + LOWER_CLOCKWISE;  // Set PWM
                    }

                    // If center cell is getting most intense light, cease rotation. Then set next state to CHECK_UPPER and break
                    if (min_idx == 1){                         /* !!! REPLACE THE 1 WITH YOUR LOGIC FOR SEEING IF CENTER IS MOST INTENSE !!! */

                        // Upper servo set to no movement
                        TIMA1->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA1->COUNTERREGS.CC_01[0] = 3000 + 0;  // Set PWM

                        // Lower servo set to no movement
                        TIMA0->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA0->COUNTERREGS.CC_01[0] = 3000 + 0;  // Set PWM

                        // Set next state as CHECK_UPPER and break out of check loop
                        requested_op = CHECK_UPPER;
                        break;
                    }
                }

                // Break out of CHECK_LOWER case
                break;

            case CHECK_UPPER:

                while(1){
                    // Get values of photo cell and compare the cells in the vertically mounted array.
                    /* !!! Your code goes here !!! */
                    DL_ADC12_startConversion(ADC12_0_INST);
                    while (!gCheckADC) { __WFE(); }
                    gCheckADC = false;

                    float vertical_adc[3] = {adc3, adc4, adc5};
                    float min_val = vertical_adc[0];
                    int min_idx = 0;
                    for (int i = 1; i < 3; i++) {
                        if (vertical_adc[i] < min_val) {
                            min_val = vertical_adc[i];
                            min_idx = i;
                        }
                    }
                    // If bottom side cell is getting most intense light, rotate anti clockwise
                    if (min_idx == 2){                         /* !!! REPLACE THE 1 WITH YOUR LOGIC FOR SEEING IF BOTTOM IS MOST INTENSE !!! */

                        // Upper servo set to track anti clockwise
                        TIMA1->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA1->COUNTERREGS.CC_01[0] = 3000 + UPPER_ANTICLOCKWISE;  // Set PWM

                        // Lower servo set to no movement
                        TIMA0->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA0->COUNTERREGS.CC_01[0] = 3000 + 0;  // Set PWM
                    }

                    // If top side cell is getting most intense light, rotate clockwise
                    if (min_idx == 0){                         /* !!! REPLACE THE 1 WITH YOUR LOGIC FOR SEEING IF TOP IS MOST INTENSE !!! */

                        // Upper servo set to track clockwise
                        TIMA1->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA1->COUNTERREGS.CC_01[0] = 3000 + UPPER_CLOCKWISE;  // Set PWM

                        // Lower servo set to no movement
                        TIMA0->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA0->COUNTERREGS.CC_01[0] = 3000 + 0;  // Set PWM
                    }

                    // If center cell is getting most intense light, cease rotation. Then set next state to CHECK_UPPER and break
                    if (min_idx == 1){                         /* !!! REPLACE THE 1 WITH YOUR LOGIC FOR SEEING IF CENTER IS MOST INTENSE !!! */

                        // Upper servo set to no movement
                        TIMA1->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA1->COUNTERREGS.CC_01[0] = 3000 + 0;  // Set PWM

                        // Lower servo set to no movement
                        TIMA0->COUNTERREGS.LOAD = (2000000 / 50) - 1; // load register to be set to (8M / 50) -1
                        TIMA0->COUNTERREGS.CC_01[0] = 3000 + 0;  // Set PWM

                        // Set next state as IDLE and break out of check loop
                        requested_op = IDLE;
                        break;
                    }
                }

                // Break out of CHECK_UPPER case
                break;

            case IDLE:

                // Enable timer G0 to allow idle
                TIMG0->COUNTERREGS.CTRCTL |= (GPTIMER_CTRCTL_EN_ENABLED);

                // This state is reached once the lower and upper servos are both checked and aligned. The system waits 5 seconds before checking orientation again
                while (!timerTicked) // Wait for timer wake up
                    __WFI();

                timerTicked = 0; // reset timer interupt flag

                // Disable timer G0 until next IDLE
                TIMG0->COUNTERREGS.CTRCTL &= ~(GPTIMER_CTRCTL_EN_ENABLED);

                // Restart check cycle by setting next state to CHECK_LOWER and breaking from IDLE
                requested_op = CHECK_LOWER;
                break;
        }
    }
}

/* -------------------------------------------------------------------------------------------------------- */

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_MEM3_RESULT_LOADED:
            gCheckADC = true;
            adc0 = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);
            adc1 = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_1);
            adc2 = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_2);
            adc3 = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_3);
            adc4 = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_4);
            adc5 = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_5);
            break;
        default:
            break;
    }
}

// Interrupt Service Routine to wake up processor from IDLE state
void TIMG0_IRQHandler(void)
{
    // This wakes up the processor!

    switch (TIMG0->CPU_INT.IIDX) {
        case GPTIMER_CPU_INT_IIDX_STAT_Z: // Counted down to zero event.
            timerTicked = 1; // set a flag so we can know what woke us up.
            break;
        default:
            break;
    }
}


