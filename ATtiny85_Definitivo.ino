// SPI mode: CPOL = 0; CPHA = 1;

#include <VL53L0X.h>
#include <Wire.h> 

const int CS_SPI = 4;                                  // set CS SPI to pin PB4
const int SCLK_SPI = 3;                                // set SCLK SPI to pin PB3
const int MISO_SPI = 1;                                // set MOSI SPI to pin PB1
const int SYNC_LASER = 5;                              // set Sync to pin PB5
int SCLK_STATE = 0;
int CS_STATE = 0;
int SYNC_STATE = 0;
const byte numBits = 8;                                // set number of bits to send
byte i = 0;
byte state = 0;
byte num = 0;
byte num_last = 0;

VL53L0X sensor;

void setup() {

    Wire.begin();
    sensor.init();
    sensor.setTimeout(500);
    sensor.setMeasurementTimingBudget(20000);          // set timing budget to 20ms

    i = numBits;

    DDRB |= 0<<CS_SPI;                                 // set CS as input
    DDRB |= 0<<SCLK_SPI;                               // set SCLK as input
    DDRB |= 1<<MISO_SPI;                               // set MISO as output
    pinMode(SYNC_LASER, INPUT);                       // set SYNC as input
        
    PORTB &= ~(1 << MISO_SPI);                         // set MISO as LOW 

    GIMSK = 0b00100000;                                // turns on pin change interrupts
    PCMSK = 0b00111000;                                // turn on interrupts on pins PB3, PB4 and PB5

}

void loop() {
  
}

      //-------SPI interupt routine (MODE 1)-------//


ISR(PCINT0_vect){                                       // pin change interruption calls => 1°: CS goes high to low; 2°: SCLK goes low to high; 3°: SCLK goes high to low ...; 17°: SCLK goes high to low; 18°: CS goes low to high  

    CS_STATE = (PINB & (1<<CS_SPI));                   // check CS state 
    SCLK_STATE = (PINB & (1<<SCLK_SPI));               // check SCLK state
    SYNC_STATE = digitalRead(SYNC_LASER);

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

      if (SYNC_STATE == 0){

       num = num_last; // receive last value

     }
     else {

       num = sensor.readRangeSingleMillimeters();     // read sensor
       num_last = num;

     }  
   }        
}
