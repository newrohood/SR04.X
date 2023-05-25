#include<xc.h>
#define _XTAL_FREQ 8000000
#pragma config FOSC=INTOSC_EC
#pragma config WDT=OFF
#define TRIGGER RD0
#define ECHO RC2
void Transmitir(unsigned char);
void main(void){
  unsigned int t;
  unsigned char d;
  OSCCON=0b01110000;
  __delay_ms(1);
  TRISD0=0;
  LATD0=0;
  TXSTA=0b00100000;
  RCSTA=0b10000000;
  BAUDCON=0b00000000;
  SPBRG=12;
  T1CON=0b10010000;
  while(1){
    t=0;  
    CCP1CON=0b00000100;
    TMR1=0;
    CCP1IF=0;
    TRIGGER=1;
    __delay_us(10);
    TRIGGER=0;
        
    while(ECHO==0);
    /*
    while(ECHO==1){
      __delay_us(10);
      t++;
    }
    d=t/5.8;*/
    TMR1ON=1;
    while(CCP1IF==0);
    TMR1ON=0;
    d=CCPR1/58;
    Transmitir(d/100 + 48);
    Transmitir((d%100)/10 + 48);
    Transmitir(d%10 + 48);
    __delay_ms(1000);    
  }  
}
void Transmitir(unsigned char BufferT){
  while(TRMT==0);
  TXREG=BufferT;  
}
