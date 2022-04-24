/*
 * File:   prelab8.c
 * Author: Esli Vivar.
 *
 * Created el 20 de abril del 202
 * 
 * Descripcion: TIMER0 aumenta PORTC y y dos botones en PORTB aumenta PORTA
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>

/*
 * Constantes
 */
#define _XTAL_FREQ 4000000

/*
 * Variables 
 */

/*
 * Prototipos de funciones
 */

void setup(void);


/*
 * Interrupcion 
 */

void __interrupt() isr (void)
{
    //Interrupción del ADC
    if(PIR1bits.ADIF) {
        if(ADCON0bits.CHS == 5)
            
             // Mostramos ADRESH en PORTC
            PORTA = ADRESH;
        
         // Limpiamos bandera de interrupción
        PIR1bits.ADIF = 0;
    }
}

/*
 * Codigo Principal
 */
void main (void)
{
    setup();
    ADCON0bits.GO =1; //empezar una conversion inicial
    while(1)
    {
           // No hay proceso de conversion
        // loop principal
        if (ADCON0bits.GO == 0) {
            ADCON0bits.CHS = 5;
            
            // Iniciamos proceso de conversión
            ADCON0bits.GO =1;
        }
            
    }
}
/*
 * Funciones
 */
void setup(void) 
{
    // Configuraciones de entradas y salidas 
    ANSEL = 0b0010000;
    ANSELH = 0;
    
    //Puerto A0 como salida
    TRISAbits.TRISA0 = 0;
    //Puerto A1 como salida
    TRISAbits.TRISA1 = 0;
    //Puerto A2 como salida
    TRISAbits.TRISA2 = 0; 
    //Puerto A3 como salida
    TRISAbits.TRISA3 = 0; 
    //Puerto A4 como salida
    TRISAbits.TRISA4 = 0;
    //Puerto A5 como salida
    TRISAbits.TRISA5 = 0;
    //Puerto A6 como salida
    TRISAbits.TRISA6 = 0; 
    //Puerto A7 como salida
    TRISAbits.TRISA7 = 0; 
    
    //TRISC = 0;
    
    //Puerto E0 como salida
    TRISEbits.TRISE0 = 0;
    //Puerto E1 como salida
    TRISEbits.TRISE1 = 0;
    //Puerto E2 como salida
    TRISEbits.TRISE2 = 0; 
    
    
    //Valores iniciales
    //Se limpia el puerto A0
    PORTAbits.RA0 = 0;
    //Se limpia el puerto A1
    PORTAbits.RA1 = 0;
    //Se limpia el puerto A2
    PORTAbits.RA2 = 0;
    //Se limpia el puerto A3
    PORTAbits.RA3 = 0;
    //Se limpia el puerto A4
    PORTAbits.RA4 = 0;
     //Se limpia el puerto A5
    PORTAbits.RA5 = 0;
    //Se limpia el puerto A6
    PORTAbits.RA6 = 0;
    //Se limpia el puerto A7
    PORTAbits.RA7 = 0;
    
    //PORTC = 0;
    
    //Se limpia el puerto E0
    PORTEbits.RE0 = 0;
    //Se limpia el puerto E1
    PORTEbits.RE1 = 0;
    //Se limpia el puerto E2
    PORTEbits.RE2 = 0;
    
    //Configuracion de oscilador
    OSCCONbits.IRCF = 0b0110; //4MHz
    OSCCONbits.SCS = 1; //ocsilador interno
    
    //Configuracion del ADC
    // 4MHz --> Fosc/8 se recomienda con 2us
    ADCON1bits.ADFM = 0; //justificado a la izquierda
    ADCON1bits.VCFG0 = 0; //VDD 
    ADCON1bits.VCFG1 = 0; //tierra
    
    ADCON0bits.ADCS = 0b01; //Fosc/8
    ADCON0bits.CHS = 5; //Canal 5 (AN5)
    ADCON0bits.ADON = 1; //change selection on 
    __delay_us(50);   //delay para que se cargue el capacitor en e modulo 
    
    //Configuracion de las interrupciones
    //apagar la bandera de ADC
    PIR1bits.ADIF = 0; 
  
    //habilitar interrupcion analogica
    PIE1bits.ADIE = 1; 
    
    //interrupciones perifericas
    INTCONbits.PEIE = 1;
    
    //interrupciones globales
    INTCONbits.GIE  = 1;
    
    return;
}