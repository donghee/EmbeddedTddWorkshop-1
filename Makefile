# MCU 
MCU = atmega168
F_CPU = 7372800L

TARGET = ChordedKeyboard

# AVRDUDE
PORT=COM1
BAUD=19200
PROTOCOL=stk500v1
PART=m168
AVRDUDE=C:\work\WinAVR-20100110\bin\avrdude

# Directory 
DIR_SRC = src
DIR_ARDUINO = ArduinoCore
CUT_INCLUDE = ChordedKeyboard/include
CUT_SRC = ChordedKeyboard/src

# Objects
OBJS = press_button.o
CPP_OBJS = main.o 

CFLAGS =  -c -g -Os -w -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(DIR_ARDUINO) -I$(CUT_INCLUDE)
CPPFLAGS =  -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU==$(F_CPU) -I$(DIR_ARDUINO) -I$(CUT_INCLUDE) -I$(DIR_SRC)

RM := rm -rf

# All Target
all: clean
all: OBJS += main.o 
all: elf secondary-outputs


$(OBJS): %.o: $(CUT_SRC)/%.c
	@echo 'Compile '
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
	avr-objdump -h -S $(TARGET).elf > $(TARGET).lss
	@echo 'Finished building: $(TARGET)'
	@echo ' '

hex: 
	@echo 'Create Flash image (ihex format)'
	avr-objcopy -R .eeprom -O ihex $(TARGET).elf $(TARGET).hex
	@echo 'Finished building: $@'
	@echo ' '

sizedummy:
	@echo 'Invoking: Print Size'
	avr-size --format=avr --mcu=atmega168 $(TARGET).elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: 
	@echo 'Invoking: AVRDude'
	$(AVRDUDE) -p$(PART) -carduino -P$(PORT) -b$(BAUD) -F -Uflash:w:$(TARGET).hex:a
	@echo 'Finished building: $@'
	@echo ' '

clean:
	$(RM) $(OBJS)$(C_DEPS)$(ELFS) *.lss *.hex $(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS) *.elf *.o
	@echo ' '

secondary-outputs: lss hex sizedummy avrdudedummy

.PHONY: all clean dependents testpoint

.SECONDARY:
