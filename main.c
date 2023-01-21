/******************************************************************************

Robot Maze solver code.
Youssef mouaddib.

*******************************************************************************/
#include <stdio.h>
// Include the WiringPi library
#include <wiringPi.h>

int main()
{
// Define the GPIO pin you wish to use
#define PIN_NUMBER 0

// Declare an integer variable
int my_variable;

// Set the GPIO pin to an output
pinMode (PIN_NUMBER, OUTPUT);

// Read the value of the variable
my_variable = digitalRead(PIN_NUMBER);

// Write the value of the variable to the pin
digitalWrite(PIN_NUMBER, my_variable);

int IR1 = <PIN 1>
int IR2 = <PIN 2>
int IR3 = <PIN 3>

void setup 
{
  DECLARE IR1 IR2 AND IR3 AS INPUTS
}

void loop 
{
  IR1 = digitalRead(<PIN 1>)
  IR2 = digitalRead(<PIN 2>)
  IR3 = digitalRead(<PIN 3>)

  if (IR1 == LOW && IR2 == HIGH && IR3 == LOW)//forward
    {
     setLM(10);
     setRM(10);
    }

  if (IR1 == HIGH && IR2 == LOW && IR3 == LOW)//Left 
    {
     setLM(5);
     setRM(10);
    }

  if (IR1 == LOW && IR2 == LOW && IR3 == HIGH)//Right 
    {
      setLM(10);
      setRM(5);
    }

  if (IR1 == HIGH && IR2 == LOW && IR3 == HIGH)//left
    {
      setLM(5);
      setRM(10);
    }

  if (IR1 == HIGH && IR2 == HIGH && IR3 == LOW)//Left 
    {
      setLM(5);
      setRM(10);
    }

  if (IR1 == LOW && IR2 == HIGH && IR3 == HIGH)//Right 
    {
     setLM(10);
     setRM(10);
    }

  if (IR1 == LOW && IR2 ==LOW && IR3 == LOW)//U Turn
    {
     setLM(0);
     setRM(10);
    }

  if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH)//2 case: End or 4way intersection
    {
     setLM(10);
     setRM(10);
     
     delay(<Time>);
     
     setLM(0);
     setRM(0);

     if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH)
        {
          Serial.println("ËND OF MAZE");
          setLM(0);
          setRM(0);
        }
     else
        {
         Serial.println("FOUR WAY INTERSECTION");
         setLM(5);
         setRM(10);
        }
    }
}
    return 0;
}

