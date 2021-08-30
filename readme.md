Test code for some sensor
For board nucleo F446RE
Using MbedOS

To run install
make, arm-none-eabi-gcc, arm-none-eabi-newlib


For Ubuntu
https://community.arm.com/developer/ip-products/processors/f/cortex-m-forum/8993/installing-arm-gcc-toolchain-on-ubuntu
For ArchLinux
https://archlinux.org/packages/community/x86_64/arm-none-eabi-gcc/
https://archlinux.org/packages/community/any/arm-none-eabi-newlib/


To build type
make

To flash copy bin file to nucleo

If there is any problem, try erase *print* wrapper
from makefile

Available sensor
- AMG              --V
- CMPS             --X
- LCD              --V
- Gripper Servo    --V
- Ping             --V
- TCS230           --V
- Button           --V
- IR Sharp         --V

- All at once      --V
