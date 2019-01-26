# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\austc\OneDrive\Documents\GitHub\Electronics2018-19\Psoc Arm\CAN_Full_P4_Example01.cydsn\CAN_Full_P4_Example01.cyprj
# Date: Tue, 20 Nov 2018 08:56:32 GMT
#set_units -time ns
create_clock -name {UART_SCBCLK(FFB)} -period 708.33333333333326 -waveform {0 354.166666666667} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {CyRouted1} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyLFCLK} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 17 35} -nominal_period 708.33333333333326 [list]


# Component constraints for C:\Users\austc\OneDrive\Documents\GitHub\Electronics2018-19\Psoc Arm\CAN_Full_P4_Example01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\austc\OneDrive\Documents\GitHub\Electronics2018-19\Psoc Arm\CAN_Full_P4_Example01.cydsn\CAN_Full_P4_Example01.cyprj
# Date: Tue, 20 Nov 2018 08:56:27 GMT
