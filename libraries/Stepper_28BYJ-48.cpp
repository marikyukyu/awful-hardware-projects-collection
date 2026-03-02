/* 
 *
 * Drives 28BYJ-48 stepper motor. 
 *
 *  
 * Stepper.cpp - Stepper library for Wiring/Arduino - Version 1.1.0
 *
 * Original library        (0.1)   by Tom Igoe.
 * Two-wire modifications  (0.2)   by Sebastian Gassner
 * Combination version     (0.3)   by Tom Igoe and David Mellis
 * Bug fix for four-wire   (0.4)   by Tom Igoe, bug fix from Noah Shibley
 * High-speed stepping mod         by Eugene Kozlenko
 * Timer rollover fix              by Eugene Kozlenko
 * Five phase five wire    (1.1.0) by Ryan Orendorff
 * 28BYJ-48 support                by github.com/marikyukyu /shrug
 * 
 * built-in Stepper Library actually didn't properly work.
 * For one example the steps are too big somehow.
 * And a huge problem of it not being able to reverse!
 * 
 * I used this datasheet:
 * https://rajguruelectronics.com/Product/1467/28BYJ-48%20-%205V%20Stepper%20Motor.pdf
 * 
 * For the constructor, use this. (forgot where i got the value from teehee~)
 * const int stepsPerRevolution = 4076; 
 * 
 * 
 * 
 * LICENSE:
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 * Step C0 C1 C2 C3
 * 0    1  1  1  0
 * 1    1  1  0  0
 * 2    1  1  0  1
 * 3    1  0  0  1
 * 4    1  0  1  1
 * 5    0  0  1  1
 * 6    0  1  1  1
 * 7    0  1  1  0
 */

#include "Arduino.h"

class StepperBy
{
  public:
    int direction;            // Direction of rotation
    unsigned long step_delay; // delay between steps, in ms, based on speed
    int number_of_steps;      // total number of steps this motor can take
    int pin_count;            // how many pins are in use.
    int step_number;          // which step the motor is on

    // motor pin numbers:
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;

    unsigned long last_step_time; // time stamp in us of when the last step was taken



StepperBy(int number_of_steps, int motor_pin_1, int motor_pin_2,
                 int motor_pin_3, int motor_pin_4)
{
    this->step_number = 0;                   // which step the motor is on
    this->direction = 0;                     // motor direction
    this->last_step_time = 0;                // time stamp in us of the last step taken
    this->number_of_steps = number_of_steps; // total number of steps for this motor

    // Arduino pins for the motor control connection:
    this->motor_pin_1 = motor_pin_1;
    this->motor_pin_2 = motor_pin_2;
    this->motor_pin_3 = motor_pin_3;
    this->motor_pin_4 = motor_pin_4;

    // setup the pins on the microcontroller:
    pinMode(this->motor_pin_1, OUTPUT);
    pinMode(this->motor_pin_2, OUTPUT);
    pinMode(this->motor_pin_3, OUTPUT);
    pinMode(this->motor_pin_4, OUTPUT);
}

/*
 * Sets the speed in revs per minute
 */
void setSpeed(long whatSpeed)
{
    this->step_delay = 60L * 1000L * 1000L / this->number_of_steps / whatSpeed;
}

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void step(int steps_to_move)
{
    int steps_left = abs(steps_to_move); // how many steps to take

    // determine direction based on whether steps_to_mode is + or -:
    if (steps_to_move > 0)
    {
        this->direction = 1;
    }
    if (steps_to_move < 0)
    {
        this->direction = 0;
    }

    // decrement the number of steps, moving one step each time:
    while (steps_left > 0)
    {
        unsigned long now = micros();
        // move only if the appropriate delay has passed:
        if (now - this->last_step_time >= this->step_delay)
        {
            // get the timeStamp of when you stepped:
            this->last_step_time = now;
            // increment or decrement the step number,
            // depending on direction:
            if (this->direction == 1)
            {
                this->step_number++;
                if (this->step_number == this->number_of_steps)
                {
                    this->step_number = 0;
                }
            }
            else
            {
                if (this->step_number == 0)
                {
                    this->step_number = this->number_of_steps;
                }
                this->step_number--;
            }
            // decrement the steps left:
            steps_left--;
            // step the motor to step number 0, 1, ..., {3 or 10}
            stepMotor(this->step_number % 8);
        }
    }
}

/*
 * Moves the motor forward or backwards.
 */
void stepMotor(int thisStep)
{
    switch (thisStep)
    {
    case 0: // 1110
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);
        break;
    case 1: // 1100
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, LOW);
        break;
    case 2: // 1101
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, HIGH);
        break;
    case 3: // 1001
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, HIGH);
        break;
    case 4: // 1011
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, HIGH);
        break;
    case 5: // 0011
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, HIGH);
        break;
    case 6: // 0111
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, HIGH);
        break;
    case 7: // 0110
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);
        break;
    }
}
};
