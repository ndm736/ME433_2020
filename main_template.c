#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro

// DEVCFG0
#pragma config DEBUG = x // disable debugging
#pragma config JTAGEN = x // disable jtag
#pragma config ICESEL = x // use PGED1 and PGEC1
#pragma config PWP = x // disable flash write protect
#pragma config BWP = x // disable boot write protect
#pragma config CP = x // disable code protect

// DEVCFG1
#pragma config FNOSC = x // use primary oscillator with pll
#pragma config FSOSCEN = x // disable secondary oscillator
#pragma config IESO = x // disable switching clocks
#pragma config POSCMOD = x // high speed crystal mode
#pragma config OSCIOFNC = x // disable clock output
#pragma config FPBDIV = x // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = x // disable clock switch and FSCM
#pragma config WDTPS = x // use largest wdt
#pragma config WINDIS = x // use non-window mode wdt
#pragma config FWDTEN = x // wdt disabled
#pragma config FWDTWINSZ = x // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = x // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = x // multiply clock after FPLLIDIV
#pragma config FPLLODIV = x // divide clock after FPLLMUL to get 48MHz

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = x // allow multiple reconfigurations
#pragma config IOL1WAY = x // allow multiple reconfigurations

int main() {

    __builtin_disable_interrupts(); // disable interrupts while initializing things

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    // do your TRIS and LAT commands here

    __builtin_enable_interrupts();

    while (1) {
        // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
        // remember the core timer runs at half the sysclk

    }
}
