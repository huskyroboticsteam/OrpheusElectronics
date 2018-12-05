avr-objcopy avr_mc.elf -O ihex avr_mc.hex
avrdude -p at90can128 -c avrisp -P COM3 -b 19200 -V -U avr_mc.hex
