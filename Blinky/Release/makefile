#http://www.jiggerjuice.net/electronics/projects/sample-makefile

#.SUFFIXES : .c .o 

# MCU name
MCU = atmega168


TARGET = ChordedKeyboard

DIR_SRC = ..
DIR_ARDUINO = ../../ArduinoCore
DIR_KEYEVENT = ../../ChordedKeyboard/tests

OBJS = keyevent.o 
CPP_OBJS = main.o testpoint.o
#SRC = keyevent.c main.cpp

CFLAGS =  -c -g -Os -w -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=7372800L -I$(DIR_ARDUINO) -I$(DIR_KEYEVENT)
CPPFLAGS =  -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=7372800L -I$(DIR_ARDUINO) -I$(DIR_KEYEVENT) -I$(DIR_SRC)

RM := rm -rf

# All Target
all: clean
all: OBJS += main.o 
all: elf secondary-outputs

# testpoint Target
testpoint: clean
testpoint: TARGET = Testpoint
testpoint: OBJS = testpoint.o 
testpoint: elf secondary-outputs

$(OBJS): %.o: $(DIR_KEYEVENT)/%.c
	@echo ' '
	avr-gcc $(CFLAGS) $< -o $@

$(CPP_OBJS): %.o: $(DIR_SRC)/%.cpp
	@echo ' '
	avr-g++ $(CPPFLAGS) $< -o $@

elf: $(OBJS) $(CPP_OBJS) 
	@echo 'Building target: $(TARGET)'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc -Os -Wl,--gc-sections -mmcu=atmega168 -o $(TARGET).elf $(OBJS) $(DIR_ARDUINO)/Debug/libArduinoCore.a -L"../../ArduinoCore" -lm
	@echo 'Finished building target: $(TARGET)'
	@echo ' '

lss: 
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S $(TARGET).elf > $(TARGET).lss
	@echo 'Finished building: $(TARGET)'
	@echo ' '

hex: 
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex $(TARGET).elf $(TARGET).hex
	@echo 'Finished building: $@'
	@echo ' '

sizedummy:
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega168 $(TARGET).elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: 
	@echo 'Invoking: AVRDude'
	C:\work\WinAVR-20100110\bin\avrdude -pm168 -carduino -PCOM1 -b19200 -F -Uflash:w:$(TARGET).hex:a
	@echo 'Finished building: $@'
	@echo ' '


clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ELFS) *.lss *.hex $(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS) *.elf *.o
	-@echo ' '

secondary-outputs: lss hex sizedummy avrdudedummy

.PHONY: all clean dependents testpoint

.SECONDARY: