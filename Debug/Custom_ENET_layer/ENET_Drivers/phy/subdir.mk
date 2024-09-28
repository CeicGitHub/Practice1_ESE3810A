################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Custom_ENET_layer/ENET_Drivers/phy/fsl_phyksz8081.c 

C_DEPS += \
./Custom_ENET_layer/ENET_Drivers/phy/fsl_phyksz8081.d 

OBJS += \
./Custom_ENET_layer/ENET_Drivers/phy/fsl_phyksz8081.o 


# Each subdirectory must supply rules for building sources it contributes
Custom_ENET_layer/ENET_Drivers/phy/%.o: ../Custom_ENET_layer/ENET_Drivers/phy/%.c Custom_ENET_layer/ENET_Drivers/phy/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\board" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\source" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\drivers" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\device" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\CMSIS" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\utilities" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\component\serial_manager" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\component\uart" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\component\lists" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\Custom_ENET_layer" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\Custom_ENET_layer\ENET_Drivers" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\Custom_ENET_layer\ENET_Drivers\CMSIS_driver" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\Custom_ENET_layer\ENET_Drivers\mdio" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\Custom_ENET_layer\ENET_Drivers\phy" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practice1_752964_aes128_crc32\Custom_ENET_layer\AES128" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Custom_ENET_layer-2f-ENET_Drivers-2f-phy

clean-Custom_ENET_layer-2f-ENET_Drivers-2f-phy:
	-$(RM) ./Custom_ENET_layer/ENET_Drivers/phy/fsl_phyksz8081.d ./Custom_ENET_layer/ENET_Drivers/phy/fsl_phyksz8081.o

.PHONY: clean-Custom_ENET_layer-2f-ENET_Drivers-2f-phy

