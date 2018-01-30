//neo pixel
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6
#define NUM_LEDS 16
#define BRIGHTNESS 25
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
// end neo 
#include <IRLibDecodeBase.h> 
#include <IRLib_P01_NEC.h>   
#include <IRLib_P02_Sony.h>  
#include <IRLib_HashRaw.h>  //Must be last protocol
#include <IRLibCombo.h>     // After all protocols, include this
// All of the above automatically creates a universal decoder
// class called "IRdecode" containing only the protocols you want.
// Now declare an instance of that decoder.
IRdecode myDecoder;

// Include a receiver either this or IRLibRecvPCI or IRLibRecvLoop
#include <IRLibRecv.h> 
IRrecv myReceiver(2);    //create a receiver on pin number 2

void setup() {
  Serial.begin(9600);
  //neo pixel
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
    randomSeed(analogRead(0));
  //end neo
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

int white = 20;
void loop() {
  if(myReceiver.getResults()) {
    myDecoder.decode();
     if(myDecoder.value==0x22DDA857){Serial.println(" up "); circular(0,16,255,0,0,white);}
     if(myDecoder.value==0x22DD28D7){Serial.println(" down "); circular(8,16,0,255,0,white);}
     if(myDecoder.value==0x22DDC837){Serial.println(" right "); circular(4,16,0,0,255,white);}
     if(myDecoder.value==0x22DD9867){Serial.println(" left "); circular(12,16,255,255,0,white);}
      Serial.println(white);

    myReceiver.enableIRIn(); 
  }
}


void circular(int s, int lds, int  r,int g,int b,int w){
// s:start   lds:the number of leds  r:red  g:green  b:blue  w:white
int delayVal = 10;// change the delayVal to speed things up
int j;
Serial.println();//debug
for(j = 0; j < 16 ; j++){
    Serial.println (s);//debug
          strip.setPixelColor(s, strip.Color(r,g,b,w));
          delay(delayVal);
           strip.show();  
            s++; // increase s by 1;
            if (s > (lds -1)) { s = 0;}  
 }
}

