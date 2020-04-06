#include "mbed.h"

Serial pc( USBTX, USBRX );
AnalogOut Aout(DAC0_OUT);
AnalogIn Ain(A0);
DigitalIn  Switch(SW3);
DigitalOut greenLED(LED2);
DigitalOut redLED(LED1);


BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int sample = 250;
int i;
int fre = 0;

float ADCdata[250];

int main(){

  fre = 0;
  for (i = 1; i < sample; i++){
   // Aout = Ain;
    ADCdata[i] = Ain;
    if (ADCdata[i-1]<=0.3 && ADCdata[i]>=0.3) {
      fre++;
    }
    if (ADCdata[i-1]>=0.3 && ADCdata[i]<=0.3) {
      fre++;
    }
    //if (ADCdata[i] < 0.5){fre++;}
    wait(1.0/sample);
  }

   for (i = 0; i < sample; i++){
    pc.printf("%1.3f\r\n", ADCdata[i]);
    }

  while(1) {
  fre = 0;
  for (i = 1; i < sample; i++){
    Aout = Ain;
    ADCdata[i] = Ain;
    if (ADCdata[i-1]<=0.3 && ADCdata[i]>=0.3) {
      fre++;
    }
    if (ADCdata[i-1]>=0.3 && ADCdata[i]<=0.3) {
      fre++;
    }
    //if (ADCdata[i] < 0.5){fre++;}
    wait(1.0/sample);
  }

   /*for (i = 0; i < sample; i++){
    pc.printf("%1.3f\r\n", ADCdata[i]);
    }*/
  
  

  int fre0 = (fre/2) % 10 ;
  int fre1 = ((fre/2) % 100) / 10 ;
  int fre2 = (fre/2) / 100 ;

if( Switch == 1 ){
      greenLED = 0;
      redLED = 1;
      display = 0x00;
    }
  else{
      greenLED = 1;
      redLED = 0;
      switch (fre2){
    case 0: display = table[0] ;break;
    case 1: display = table[1] ;break;
    case 2: display = table[2] ;break;
    case 3: display = table[3] ;break;
    case 4: display = table[4] ;break;
    case 5: display = table[5] ;break;
    case 6: display = table[6] ;break;
    case 7: display = table[7] ;break;
    case 8: display = table[8] ;break;
    case 9: display = table[9] ;break;
    default : display = 0x80;

  } 
  wait(0.5);
  switch (fre1){
    case 0: display = table[0] ;break;
    case 1: display = table[1] ;break;
    case 2: display = table[2] ;break;
    case 3: display = table[3] ;break;
    case 4: display = table[4] ;break;
    case 5: display = table[5] ;break;
    case 6: display = table[6] ;break;
    case 7: display = table[7] ;break;
    case 8: display = table[8] ;break;
    case 9: display = table[9] ;break;

  } 
  wait(0.5);
  switch (fre0){
    case 0: display = 0xBF ;break;
    case 1: display = 0x86 ;break;
    case 2: display = 0xDB ;break;
    case 3: display = 0xCF ;break;
    case 4: display = 0xE6 ;break;
    case 5: display = 0xED ;break;
    case 6: display = 0xFD ;break;
    case 7: display = 0x87 ;break;
    case 8: display = 0xFF ;break;
    case 9: display = 0xEF ;break;

  } 
  wait(0.5);
  }

  /*for( i=0; i<2; i+=0.05 ){
      Aout = 0.5 + 0.5*sin(i*3.14159);
      wait(0.001);
    }*/
  }
  
}