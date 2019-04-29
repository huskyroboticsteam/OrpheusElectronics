
sudo echo BB-CAN1 > /sys/devices/platform/bone_capemgr/slots

sudo modprobe can 
sudo modprobe can-raw
sudo modprobe can-dev

sudo ip link set can0 up type can bitrate 125000
sudo ifconfig can0 txqueuelen 1000
sudo ifconfig can0 up
sudo exit
