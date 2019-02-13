avr-objcopy avr_mc.elf -O ihex avr_mc.hex
avrdude -p at90can32 -c avrisp -P COM8 -b 19200 -V -U avr_mc.hex
