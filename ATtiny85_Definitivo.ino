// SPI mode: CPOL = 0; CPHA = 1;

#include <Wire.h> 
#include <VL53L0X.h>

const int CS_SPI = 4;                                  // set CS SPI to pin PB4
const int SCLK_SPI = 3;                                // set SCLK SPI to pin PB3
const int MISO_SPI = 1;                                // set MOSI SPI to pin PB1
//const int SYNC_LASER = 5;                              // set Sync to pin PB5
int SCLK_STATE = 0;
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
    DDRB |= 0<<SCLK_SPI;                               // set SCLK as input
    //DDRB |= 0<<SYNC_LASER;                             // set SYNC as input
    DDRB |= 1<<MISO_SPI;                               // set MISO as output
    
    PORTB &= ~(1 << MISO_SPI);                         // set MISO as LOW 
  
    GIMSK = 0b00100000;                                // turns on pin change interrupts
    PCMSK = 0b00011000;                                // turn on interrupts on pins PB3 and PB4
}

void loop() {

//     if (PINB & (1<<SYNC_LASER) != 0){
//
//        num = sensor.readRangeSingleMillimeters();     // read sensor
//        //num = 167; // test
//     
//     }
//     else {
//        
//        num = 0;
//        
//     }
  
  }

      //-------SPI interupt routine (MODE 1)-------//

ISR(PCINT0_vect)                                       // pin change interruption calls => 1°: CS goes high to low; 2°: SCLK goes low to high; 3°: SCLK goes high to low ...; 17°: SCLK goes high to low; 18°: CS goes low to high  
{
    CS_STATE = (PINB & (1<<CS_SPI));                   // check CS state 
    SCLK_STATE = (PINB & (1<<SCLK_SPI));               // check SCLK state
    
    if (CS_STATE == 0){
      
        if (SCLK_STATE == 0){

          state = bitRead(num, i-1);                   // save bit MSB first
          i--;                                         // next bit
        
        }
        else {

          switch(state){
            
             case 0:
                PORTB &= ~(1 << MISO_SPI);              // write bit 0
                break;
             case 1:
                PORTB |= (1 << MISO_SPI);               // write bit 1
                break;
                
          } 
       }        
    }
    else {
      
      i=numBits;                                        // restart
      PORTB &= ~(1 << MISO_SPI);                        // disable pin
      
    }        
}
