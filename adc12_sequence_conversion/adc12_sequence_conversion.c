#include "ti_msp_dl_config.h"

volatile bool gCheckADC;

#define RESULT_SIZE (3)
volatile uint16_t gAdcResult0[RESULT_SIZE];
volatile uint16_t gAdcResult1[RESULT_SIZE];
volatile uint16_t gAdcResult2[RESULT_SIZE];
volatile uint16_t gAdcResult3[RESULT_SIZE];
//volatile uint16_t gAdcResult4[RESULT_SIZE];
//volatile uint16_t gAdcResult5[RESULT_SIZE];
//volatile uint16_t gAdcResult6[RESULT_SIZE];
//volatile uint16_t gAdcResult7[RESULT_SIZE];

volatile float adc0;
volatile float adc1;
volatile float adc2;
volatile float adc3;

int main(void)
{
    /* Initialize peripherals and enable interrupts */
    SYSCFG_DL_init();
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);

    gCheckADC  = false;
    uint16_t i = 0;

    while (1) {
        DL_ADC12_startConversion(ADC12_0_INST);

        /* Wait until all data channels have been loaded. */
        while (gCheckADC == false) {
            __WFE();
        }

        /* Store ADC Results into their respective buffer */
        gAdcResult0[i] =
            DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);
        gAdcResult1[i] =
            DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_1);
        gAdcResult2[i] =
            DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_2);
        gAdcResult3[i] =
            DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_3);
//        gAdcResult4[i] =
//            DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_4);
//        gAdcResult5[i] =
//            DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_5);
//        gAdcResult6[i] =
//            DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_6);
//        gAdcResult7[i] =
//            DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_7);

        i++;
        gCheckADC = false;
        /* Reset index of buffers, set breakpoint to check buffers. */
        if (i >= RESULT_SIZE) {
            __BKPT(0);
            i = 0;
        } else {
            ; /*No action required*/
        }
        DL_ADC12_enableConversions(ADC12_0_INST);
    }
}

/* Check for the last result to be loaded then change boolean */
void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_MEM3_RESULT_LOADED:
            gCheckADC = true;
            adc0 = gAdcResult0[1];
            adc1 = gAdcResult1[1];
            adc2 = gAdcResult2[1];
            adc3 = gAdcResult3[1];
            // __BKPT(0);
            break;
        default:
            break;
    }
}
