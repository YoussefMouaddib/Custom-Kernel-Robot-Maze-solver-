
/******************************************************************************
Robot Maze solver for RPi4B.
Youssef Mouaddib, IEEE St. Mary's University, spring 2023.
*******************************************************************************/

#include <stdio.h>
#include "main.h"
#include "read32.h"
#include "pmwleft.h"
int main()
{
  /* Set up GPIO */
  setup_io();
  // Set the speed of the motor. Duty cycle between 0 and 1023
  #define HIGH 1
  #define LOW 0

    //Loop
    int Run = 1;
    while (Run == 1) {
    /* Read from GPIO 20, 21, 22*/
    uint32_t IR1 = read32(20);
    uint32_t IR2 = read32(21);
    uint32_t IR3 = read32(22);
    

    /* Print values */
    printf("GPIO 20: %d\n", IR1);
    printf("GPIO 21: %d\n", IR2);
    printf("GPIO 22: %d\n", IR3);

    if (IR1 == LOW && IR2 == HIGH && IR3 == LOW)//forward
    {
     pmwlefthigh();
     pmwrighthigh();
    }

  if (IR1 == HIGH && IR2 == LOW && IR3 == LOW)//Left 
    {
      pmwleftoff();
      pmwrighthigh();
    }

  if (IR1 == LOW && IR2 == LOW && IR3 == HIGH)//Right 
    {
      pmwlefthigh();
      pmwrightoff();
    }

  if (IR1 == HIGH && IR2 == LOW && IR3 == HIGH)//left
    {
      pmwleftoff();
      pmwrighthigh();
    }

  if (IR1 == HIGH && IR2 == HIGH && IR3 == LOW)//Left 
    {
      pmwleftoff();
      pmwrighthigh();

  if (IR1 == LOW && IR2 == HIGH && IR3 == HIGH)//Straight
    {
      pmwlefthigh();
      pmwrighthigh();
    }

  if (IR1 == LOW && IR2 ==LOW && IR3 == LOW)//U Turn
    {
      pmwleftoff();
      pmwrighthigh();
    }

  if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH)//2 case: Finish Station or 4way intersection
    {
      pmwleftoff();
      pmwrightoff();
     
     delay(300); /* wait for 300 ms the time to move forward a bit more
                  then update the inputs to see what case it is. */

     if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH) // Finish Station 
        {
          pmwleftoff();
          pmwrightoff();
          printf("FINISHED!");
          return 0;
        }
     else
        {
         pmwleftoff();
         pmwrighthigh();
        }
    }
}
    return 0;
}


}