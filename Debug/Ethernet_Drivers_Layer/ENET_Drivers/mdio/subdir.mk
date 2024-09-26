################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Ethernet_Drivers_Layer/ENET_Drivers/mdio/fsl_enet_mdio.c 

C_DEPS += \
./Ethernet_Drivers_Layer/ENET_Drivers/mdio/fsl_enet_mdio.d 

OBJS += \
./Ethernet_Drivers_Layer/ENET_Drivers/mdio/fsl_enet_mdio.o 


# Each subdirectory must supply rules for building sources it contributes
Ethernet_Drivers_Layer/ENET_Drivers/mdio/%.o: ../Ethernet_Drivers_Layer/ENET_Drivers/mdio/%.c Ethernet_Drivers_Layer/ENET_Drivers/mdio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\PruebaProyecto\board" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\PruebaProyecto\source" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\PruebaProyecto\drivers" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\PruebaProyecto\device" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\PruebaProyecto\CMSIS" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\PruebaProyecto\utilities" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\PruebaProyecto\component\serial_manager" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\PruebaProyecto\component\uart" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\PruebaProyecto\component\lists" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Ethernet_Drivers_Layer-2f-ENET_Drivers-2f-mdio

clean-Ethernet_Drivers_Layer-2f-ENET_Drivers-2f-mdio:
	-$(RM) ./Ethernet_Drivers_Layer/ENET_Drivers/mdio/fsl_enet_mdio.d ./Ethernet_Drivers_Layer/ENET_Drivers/mdio/fsl_enet_mdio.o

.PHONY: clean-Ethernet_Drivers_Layer-2f-ENET_Drivers-2f-mdio

