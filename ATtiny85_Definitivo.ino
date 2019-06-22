// SPI mode: CPOL = 0; CPHA = 1;

#include <Wire.h> 
#include <VL53L0X.h>

const int CS_SPI = 4;                                  // set CS SPI to pin PB4
const int CLK_SPI = 3;                                 // set SCLK SPI to pin PB3
const int MISO_SPI = 1;                                // set MOSI SPI to pin PB1
//const int SYNC_LASER = 5;                              // set Sync to pin PB5
int CLK_STATE = 0;
int CS_STATE = 0;
const byte numBits = 8;                                // set number of bits to send
byte i = 0;
byte state = 0;
byte num = 0;

VL53L0X sensor;

void setup() {
    Wire.begin();
    sensor.init();
    sensor.setTimeout(500);
    sensor.setMeasurementTimingBudget(20000);          // set timing budget to 20ms

    i = numBits;

    DDRB |= 0<<CS_SPI;                                 // set CS as input
    DDRB |= 0<<CLK_SPI;                                // set CLK as input
    //DDRB |= 0<<SYNC_LASER;                             // set SYNC as input
    DDRB |= 1<<MISO_SPI;                               // set MISO as output
    
    PORTB &= ~(1 << MISO_SPI);                         // set MISO as LOW 
  
    GIMSK = 0b00100000;                                // turns on pin change interrupts
    PCMSK = 0b00011000;                                // turn on interrupts on pins PB3 and PB4
}

void loop() {

//     if (PINB & (1<<SYNC_LASER) != 0){
//
//        num = sensor.readRangeSingleMillimeters();        // read sensor
//        //num = 167; // test
//     
//     }
//     else {
//        
//        num = 0;
//        
//     }
  
  }                                                                                                                

ISR(PCINT0_vect)                                       // pin change interruption 1° call: CS goes high to low; 2°: CLK goes low to high; 3°: CLK goes high to low ...; 17°: CLK goes high to low; 18°: CS goes low to high  
{
    CS_STATE = (PINB & (1<<CS_SPI));
    CLK_STATE = (PINB & (1<<CLK_SPI));
    
    if (CS_STATE == 0){
      
        if (CLK_STATE == 0){

          state = bitRead(num, i-1);
          i--;
        
        }
        else {

          switch(state){
            
             case 0:
                PORTB &= ~(1 << MISO_SPI);
                break;
             case 1:
                PORTB |= (1 << MISO_SPI);
                break;
                
          } 
       }        
    }
    else {
      
      i=numBits;
      PORTB &= ~(1 << MISO_SPI);                         // disble pin
      
    }        
}
