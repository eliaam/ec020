################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cr_startup_lpc17.c \
../display_oled.c \
../main.c \
../sensor.c 

OBJS += \
./cr_startup_lpc17.o \
./display_oled.o \
./main.o \
./sensor.o 

C_DEPS += \
./cr_startup_lpc17.d \
./display_oled.d \
./main.d \
./sensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\aluno\Desktop\FreeRTOS_Library\demo_code" -I"C:\Users\aluno\Desktop\CMSISv1p30_LPC17xx\inc" -I"C:\Users\aluno\Desktop\FreeRTOS_Library\include" -I"C:\Users\aluno\Desktop\FreeRTOS_Library\portable" -I"C:\Users\aluno\Desktop\Lib_CMSISv1p30_LPC17xx\inc" -I"C:\Users\aluno\Desktop\Lib_EaBaseBoard\inc" -I"C:\Users\aluno\Desktop\Lib_MCU\inc" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


