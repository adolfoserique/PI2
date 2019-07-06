#include <Wire.h>
#include <VL53L0X.h>
#include "SPI.h"

VL53L0X sensor;

int laser_int = 0;
byte laser = 0;
byte laser_last = 0;
const int SYNC = 9;

void setup()
{
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);
  sensor.setMeasurementTimingBudget(20000);


  pinMode(MISO,OUTPUT);
  pinMode(SYNC, INPUT_PULLUP);
  

  SPCR |= _BV(SPE); // iniciar como escravo
  
  SPI.attachInterrupt();

}

void loop()
{
  if (digitalRead(SYNC) == 1){
   laser = sensor.readRangeSingleMillimeters();
  }
  else {

    laser_last = laser;
    
    }
}


ISR (SPI_STC_vect)
{
  SPDR = laser;                                     
}
