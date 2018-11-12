avr-objcopy avr_mc.elf -O ihex avr_mc.hex
avrdude -p at90can128 -c avrisp -P COM5 -b 19200 -U avr_mc.hex
