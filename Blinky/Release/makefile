#http://www.jiggerjuice.net/electronics/projects/sample-makefile

RM := rm -rf

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Blinky.lss \

FLASH_IMAGE += \
Blinky.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: Blinky.elf secondary-outputs

# Tool invocations
Blinky.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
#	avr-gcc -c -g -Os -w -ffunction-sections -fdata-sections -mmcu=atmega168 -DF_CPU=7372800L -I"../../ArduinoCore" -I"../ChordedKeyboard/tests" ../../ChordedKeyboard/tests/keyevent.c -o keyevent.o
	avr-gcc -c -g -Os -w -ffunction-sections -fdata-sections -mmcu=atmega168 -DF_CPU=7372800L -I"../../ArduinoCore" -I"../../ChordedKeyboard/tests" ../../ChordedKeyboard/tests/keyevent.c -o keyevent.o
	avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega168 -DF_CPU=7372800L -I"../../ArduinoCore" -I"../../ChordedKeyboard/tests" -I"../" ../main.cpp -o main.o
	avr-gcc -Os -Wl,--gc-sections -mmcu=atmega168 -o Blinky.elf main.o keyevent.o ../../ArduinoCore/Debug/libArduinoCore.a -L"../../ArduinoCore" -lm
	@echo 'Finished building target: $@'
	@echo ' '

Blinky.lss: Blinky.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Blinky.elf  >"Blinky.lss"
	@echo 'Finished building: $@'
	@echo ' '

Blinky.hex: Blinky.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Blinky.elf  "Blinky.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Blinky.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega168 Blinky.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: Blinky.elf
	@echo 'Invoking: AVRDude'
	C:\work\WinAVR-20100110\bin\avrdude -pm168 -carduino -PCOM1 -b19200 -F -Uflash:w:Blinky.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(AVRDUDEDUMMY)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) Blinky.elf *.o
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:
