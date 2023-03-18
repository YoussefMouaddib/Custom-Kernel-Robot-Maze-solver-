
/******************************************************************************
Robot Maze solver for RPi4B.
Youssef Mouaddib, IEEE St. Mary's University, spring 2023.
*******************************************************************************

This assembly file loads the address of the main 
function and jumps to it, effectively starting the main 
program. It then creates an infinite loop that waits for 
interrupts to occur.
*/

.section ".text.boot"
 
.global _start
 
_start:
	ldr r3, =main
	blx r3

halt:
	wfe
	b halt
