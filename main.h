
/******************************************************************************
Robot Maze solver for RPi4B.
Youssef Mouaddib, IEEE St. Mary's University, spring 2023.
*******************************************************************************/

#include <stdio.h>
#include "arm64_common.h"

#define ARM_GPIO_GPFSEL0   0xfe200000;
#define ARM_GPIO_GPFSEL1   0xfe200004;
#define ARM_GPIO_GPFSEL2   0xfe200008;
#define ARM_GPIO_GPFSEL3   0xfe20000c;
#define ARM_GPIO_GPFSEL3   0xfe200010;