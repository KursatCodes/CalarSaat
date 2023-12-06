
// PIC16F628A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 4000000

short sayac=0,saniye=0,dakika=0,saat=0;

void __interrupt() timer1(){
    if(TMR1IF){
        TMR1=15536;
        TMR1IF=0;
        sayac++;
        if(sayac==20){
            sayac=0;
            saniye++;
        }
    }
}

main() {
    PCONbits.OSCF=1;//dahili osilator secildi
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIE1bits.TMR1IE=1;
    T1CONbits.T1CKPS0=0;
    T1CONbits.T1CKPS1=0;
    T1CONbits.TMR1CS=0;
    T1CONbits.TMR1ON=1;
            
    TRISB=0x00;
    PORTB=0;
    while(1){
        
        if(saniye>=60){//zamani artrima kodu
            saniye=0;
            dakika++;
            if(dakika>=60){
                dakika=0;
                saat++;
                if(saat>=24){
                    saat=0;
                }
            }
        }
        short saatOnluk=saat/10, saatBirlik=saat%10,
              dkOnluk=dakika/10,dkBirlik=dakika%10,
              sanOnluk=saniye/10,sanBirlik=saniye%10;
        PORTB=sanOnluk;
    }
}
