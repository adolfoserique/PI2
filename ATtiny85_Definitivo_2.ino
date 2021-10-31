#include <Wire.h> 
#include <VL53L0X.h>

#define CS_SPI      PB4                               // set CS SPI to pin PB4
#define SCLK_SPI    PB3                               // set SCLK SPI to pin PB3
#define MISO_SPI    PB1                               // set MOSI SPI to pin PB1
#define SYNC_LASER  PB5                               // set Sync to pin PB5

int d = 0;
const byte numBits = 8;                                                                                         // set number of bits to send
byte i = 0;
byte state = 0;
byte num = 0;
byte num_last = 0;


VL53L0X sensor;


void setup() {
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.setMeasurementTimingBudget(20000);                                                                       // set timing budget to 20ms

  DDRB |= 0<<CS_SPI;                                                                                              // set CS as input
  DDRB |= 0<<SCLK_SPI;                                                                                             // set CLK as input
  DDRB |= 1<<MISO_SPI;                                                                                            // set MISO as output
  DDRB |= 0<<SYNC_LASER;                                                                                          // set SYNC as input
  PORTB &= ~(1 << MISO_SPI);                                                                                     // set MISO as LOW 
}

void loop() {
  if((PINB & (1<<CS_SPI)) == 0){
    if ((PINB & (1<<SCLK_SPI)) == 0) {
      for (byte i=numBits; i>0; i--) {
        if((PINB & (1<<CS_SPI)) != 0){                                                                        
          break;                                                                                                  // break for
        } // end if cs break
       state = bitRead(num, i-1);                                                                                   // safe sensor value starting with LSB
        if ((PINB & (1<<SCLK_SPI)) != 0){                                                                        // if to check CLK state
          if (d == 0){                                                                                            // if to avoid writing if state HIGH repeat
                switch(state)
               {
                    case 0:
                       PORTB &= ~(1 << MISO_SPI);  //Set MISO as LOW
                        break;
                    case 1:
                        PORTB |= (1 << MISO_SPI);  //Set MISO as HIGH
                        break;
                }
            d = 1;
          }
          else {
            i++;
          }                                                                                                       // end if else state HIGH CLK double check 
         }                                                                                                        
        else {
          d = 0;
          i++;
        }                                                                                                         // end if else state CLK check
      }                                                                                                           // end for
    }
  }
  else {

       i=numBits;
      PORTB &= ~(1 << MISO_SPI); 

  if ((PINB & (1<<SYNC_LASER)) == 0){

       num = num_last;

      }
      else {

        //num = 170;  //teste
       num = sensor.readRangeSingleMillimeters();     // read sensor
       num_last = num;

      }  
  }                                                                                                               // end if else state CS
}                                                                                                                 // end loop
