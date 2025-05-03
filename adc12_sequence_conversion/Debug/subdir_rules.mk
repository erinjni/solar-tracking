################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/Users/joliewang/rice/24-25/spring25/elec 327/workspacev12/adc12_sequence_conversion_LP_MSPM0G3507_nortos_ticlang" -I"/Users/joliewang/rice/24-25/spring25/elec 327/workspacev12/adc12_sequence_conversion_LP_MSPM0G3507_nortos_ticlang/Debug" -I"/Users/joliewang/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"/Users/joliewang/ti/mspm0_sdk_2_03_00_07/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1884863457: ../adc12_sequence_conversion.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Applications/ti/ccs1281/ccs/utils/sysconfig_1.21.0/sysconfig_cli.sh" --script "/Users/joliewang/rice/24-25/spring25/elec 327/workspacev12/adc12_sequence_conversion_LP_MSPM0G3507_nortos_ticlang/adc12_sequence_conversion.syscfg" -o "." -s "/Users/joliewang/ti/mspm0_sdk_2_03_00_07/.metadata/product.json" -s "/Users/joliewang/ti/mspm0_sdk_2_03_00_07/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1884863457 ../adc12_sequence_conversion.syscfg
device.opt: build-1884863457
device.cmd.genlibs: build-1884863457
ti_msp_dl_config.c: build-1884863457
ti_msp_dl_config.h: build-1884863457
Event.dot: build-1884863457

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/Users/joliewang/rice/24-25/spring25/elec 327/workspacev12/adc12_sequence_conversion_LP_MSPM0G3507_nortos_ticlang" -I"/Users/joliewang/rice/24-25/spring25/elec 327/workspacev12/adc12_sequence_conversion_LP_MSPM0G3507_nortos_ticlang/Debug" -I"/Users/joliewang/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"/Users/joliewang/ti/mspm0_sdk_2_03_00_07/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: /Users/joliewang/ti/mspm0_sdk_2_03_00_07/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/Users/joliewang/rice/24-25/spring25/elec 327/workspacev12/adc12_sequence_conversion_LP_MSPM0G3507_nortos_ticlang" -I"/Users/joliewang/rice/24-25/spring25/elec 327/workspacev12/adc12_sequence_conversion_LP_MSPM0G3507_nortos_ticlang/Debug" -I"/Users/joliewang/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"/Users/joliewang/ti/mspm0_sdk_2_03_00_07/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


