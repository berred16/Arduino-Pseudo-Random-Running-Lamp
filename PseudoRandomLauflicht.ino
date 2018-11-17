/*
Copyright (C) 2018 Youtube: Berred

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Function:
Pseudo random running light (Elektor, 1978)

Hardware setup: Arduino UNO R3
Ports D1 - 7 output LEDs
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PORT PORTD

// Variables for pseudo random functionaltiy
uint8_t start=1, xor_result = 0, xor1, xor2;
// Variable for timer interrupt
int i = 1;

void timer0_init(void){
    TIMSK0 = (1 << TOIE0); // Enable timer0 interrupt overflow
    TCCR0B = ((1<<CS02)|(1<<CS00)); // Prescaler 1024
    }
    
ISR (TIMER0_OVF_vect){
    i++;
  
    if (i > 30) // Sets speed
    {
      // Pseudo random functionality
      PORTD = start; // set start point to 1
      xor1 = (0x40 & start) >>6; // check xor input at 6th pin
      xor2 = (0x20 & start) >>5; // check xor input at 5th pin
            
      xor_result = xor1 ^ xor2; // connect xor1 and xor2
      
      if (xor_result == 0){
          start = start << 1; // If result it 0, only shift
          }
      if (xor_result == 1){
          start = (start << 1) + xor_result; // If result ist 1, shift and add 1
          } 
      
      i = 1; 
    }
}
  
int main(void){

DDRD = 0xff; // Output all segments
PORTD =0x00; // First all LEDs off

timer0_init(); // Set up the timer0

sei(); // Enable interrupts

  while(1){
      // Thank you and good night...
  }
return 0;
}

