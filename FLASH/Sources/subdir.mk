################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/MCF52255_sysinit.c" \
"../Sources/adc.c" \
"../Sources/cfm.c" \
"../Sources/delay.c" \
"../Sources/exceptions.c" \
"../Sources/gpio.c" \
"../Sources/i2c_master.c" \
"../Sources/lcd.c" \
"../Sources/main.c" \
"../Sources/mpu6050.c" \
"../Sources/pit.c" \
"../Sources/qspi.c" \
"../Sources/uart.c" \

C_SRCS += \
../Sources/MCF52255_sysinit.c \
../Sources/adc.c \
../Sources/cfm.c \
../Sources/delay.c \
../Sources/exceptions.c \
../Sources/gpio.c \
../Sources/i2c_master.c \
../Sources/lcd.c \
../Sources/main.c \
../Sources/mpu6050.c \
../Sources/pit.c \
../Sources/qspi.c \
../Sources/uart.c \

OBJS += \
./Sources/MCF52255_sysinit_c.obj \
./Sources/adc_c.obj \
./Sources/cfm_c.obj \
./Sources/delay_c.obj \
./Sources/exceptions_c.obj \
./Sources/gpio_c.obj \
./Sources/i2c_master_c.obj \
./Sources/lcd_c.obj \
./Sources/main_c.obj \
./Sources/mpu6050_c.obj \
./Sources/pit_c.obj \
./Sources/qspi_c.obj \
./Sources/uart_c.obj \

OBJS_QUOTED += \
"./Sources/MCF52255_sysinit_c.obj" \
"./Sources/adc_c.obj" \
"./Sources/cfm_c.obj" \
"./Sources/delay_c.obj" \
"./Sources/exceptions_c.obj" \
"./Sources/gpio_c.obj" \
"./Sources/i2c_master_c.obj" \
"./Sources/lcd_c.obj" \
"./Sources/main_c.obj" \
"./Sources/mpu6050_c.obj" \
"./Sources/pit_c.obj" \
"./Sources/qspi_c.obj" \
"./Sources/uart_c.obj" \

C_DEPS += \
./Sources/MCF52255_sysinit_c.d \
./Sources/adc_c.d \
./Sources/cfm_c.d \
./Sources/delay_c.d \
./Sources/exceptions_c.d \
./Sources/gpio_c.d \
./Sources/i2c_master_c.d \
./Sources/lcd_c.d \
./Sources/main_c.d \
./Sources/mpu6050_c.d \
./Sources/pit_c.d \
./Sources/qspi_c.d \
./Sources/uart_c.d \

OBJS_OS_FORMAT += \
./Sources/MCF52255_sysinit_c.obj \
./Sources/adc_c.obj \
./Sources/cfm_c.obj \
./Sources/delay_c.obj \
./Sources/exceptions_c.obj \
./Sources/gpio_c.obj \
./Sources/i2c_master_c.obj \
./Sources/lcd_c.obj \
./Sources/main_c.obj \
./Sources/mpu6050_c.obj \
./Sources/pit_c.obj \
./Sources/qspi_c.obj \
./Sources/uart_c.obj \

C_DEPS_QUOTED += \
"./Sources/MCF52255_sysinit_c.d" \
"./Sources/adc_c.d" \
"./Sources/cfm_c.d" \
"./Sources/delay_c.d" \
"./Sources/exceptions_c.d" \
"./Sources/gpio_c.d" \
"./Sources/i2c_master_c.d" \
"./Sources/lcd_c.d" \
"./Sources/main_c.d" \
"./Sources/mpu6050_c.d" \
"./Sources/pit_c.d" \
"./Sources/qspi_c.d" \
"./Sources/uart_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/MCF52255_sysinit_c.obj: ../Sources/MCF52255_sysinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/MCF52255_sysinit.args" -o "Sources/MCF52255_sysinit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/adc_c.obj: ../Sources/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/adc.args" -o "Sources/adc_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/cfm_c.obj: ../Sources/cfm.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/cfm.args" -o "Sources/cfm_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/delay_c.obj: ../Sources/delay.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/delay.args" -o "Sources/delay_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/exceptions_c.obj: ../Sources/exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/exceptions.args" -o "Sources/exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/gpio_c.obj: ../Sources/gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/gpio.args" -o "Sources/gpio_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/i2c_master_c.obj: ../Sources/i2c_master.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/i2c_master.args" -o "Sources/i2c_master_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/lcd_c.obj: ../Sources/lcd.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/lcd.args" -o "Sources/lcd_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/mpu6050_c.obj: ../Sources/mpu6050.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/mpu6050.args" -o "Sources/mpu6050_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/pit_c.obj: ../Sources/pit.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/pit.args" -o "Sources/pit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/qspi_c.obj: ../Sources/qspi.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/qspi.args" -o "Sources/qspi_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart_c.obj: ../Sources/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/uart.args" -o "Sources/uart_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


