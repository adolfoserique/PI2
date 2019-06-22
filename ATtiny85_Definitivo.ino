// SPI mode: CPOL = 0; CPHA = 1;

//#include <Wire.h> 
//#include <VL53L0X.h>

const int CS_SPI = 4;                                                                                           // set CS SPI to pin PB4
const int CLK_SPI = 3;                                                                                          // set SCLK SPI to pin PB3
const int MISO_SPI = 1;                                                                                         // set MOSI SPI to pin PB1
const int CLK_LSTATE = 0;
const int CS_LSTATE = 0;
int CLK_ASTATE = 0;
int CS_ASTATE = 0;
const byte numBits = 8;                                                                                         // set number of bits to send
byte i = 0;
byte state = 0;
byte num = 0;


//VL53L0X sensor;


void setup() {
  //Wire.begin();
  //sensor.init();
  //sensor.setTimeout(500);
  //sensor.setMeasurementTimingBudget(20000);                                                                       // set timing budget to 20ms

  i = numBits;

  DDRB |= 0<<CS_SPI;                                                                                              // set CS as input
  DDRB |= 0<<CLK_SPI;                                                                                             // set CLK as input
  DDRB |= 1<<MISO_SPI;                                                                                            // set MISO as output
  PORTB &= ~(1 << MISO_SPI);                                                                                     // set MISO as LOW 
  
  GIMSK = 0b00100000;                                                                                           // turns on pin change interrupts
  PCMSK = 0b00011000;                                                                                           // turn on interrupts on pins PB3 and PB4
}

void loop() {
  
  }                                                                                                                

ISR(PCINT0_vect) // pin chenge interruption 1° call: CS goes high to low; 2°: CLK goes low to high; 3°: CLK goes high to low ...; 17°: CLK goes high to low; 18°: CS goes low to high  
{
    CS_ASTATE = (PINB & (1<<CS_SPI));
    CLK_ASTATE = (PINB & (1<<CLK_SPI));
    if (CS_ASTATE == CS_LSTATE){
        if (CLK_ASTATE == CLK_LSTATE){

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
      //num = sensor.readRangeSingleMillimeters();                                                                  // read sensor
      num = 167;
      PORTB &= ~(1 << MISO_SPI);                                                                               // disble pin
      
    }        
}
