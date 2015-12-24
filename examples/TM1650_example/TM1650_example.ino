/*
 * 
 * Copyright (c) 2015. Mario Mikočević <mozgy>
 * 
 * MIT Licence
 *
 */

#include <Wire.h>
#include <TM1650.h>

TM1650 Disp4Seg;

// I2C pins
#define SDA_pin 4
#define SCL_pin 5

void setup() {

  Serial.begin(115200);
  Serial.println( "TM1650 4 segment display example" );

  Wire.begin( SDA_pin, SCL_pin );
  Wire.setClock( 400000 );

  Disp4Seg.Init();
  delay(1000);

}

void loop() {

  Disp4Seg.SetBrightness( 1 );

  for( uint16_t i=0; i<10000; i++ ) {
    Disp4Seg.WriteNum( i );
    ( i & 0x10 ) ? Disp4Seg.ColonON() : Disp4Seg.ColonOFF();
    delay(8);
  }
  Disp4Seg.ColonOFF();


  for( uint8_t k=0; k<3; k++ ) {
    for( uint8_t i=0; i<4; i++ ) {
      for( uint8_t j=1; j<0x40; j=j<<1 ) {
        Disp4Seg.SendDigit( j, i );
        delay(50);
      }
      Disp4Seg.SendDigit( 0, i );
    }
  }

  Disp4Seg.WriteNum( 8888 );
  Disp4Seg.SetDot( 0, true );
  Disp4Seg.SetDot( 1, true );
  Disp4Seg.SetDot( 2, true );
  Disp4Seg.SetDot( 3, true );
  delay(4000);
  
  for( uint8_t i=0; i<3; i++ ) {
    Disp4Seg.DisplayOFF();
    delay(400);
    Disp4Seg.DisplayON();
    delay(400);
  }

}
