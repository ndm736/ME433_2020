void initUART() {
    // set the U1TX pin to B3
    RPB3Rbits.RPB3R = 0b0001;

    // set the U1RX pin to B2
    U1RXRbits.U1RXR = 0b0100;

    // turn on UART1 without an interrupt
    U1MODEbits.BRGH = 0; // set baud to 9600 bits/sec
    U1BRG = ((48000000 / 9600) / 16) - 1;

    // 8 bit, no parity bit, and 1 stop bit (8N1 setup)
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;

    // configure TX & RX pins as output & input pins
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    // enable the UART
    U1MODEbits.ON = 1;
}

void writeUART(char * string) {
    while (*string != '\0') {
        while (U1STAbits.UTXBF) {
            ; // wait until TX buffer isn't full
        }
        U1TXREG = *string;
        ++string;
    }
}

// Read from UART1
// block other functions until you get a '\r' or '\n'
// send the pointer to your char array and the number of elements in the array
void readUART(char * message, int maxLength) {
  char data = 0;
  int complete = 0, num_bytes = 0;
  // loop until you get a '\r' or '\n'
  while (!complete) {
    if (U1STAbits.URXDA) { // if data is available
      data = U1RXREG;      // read the data
      if ((data == '\n') || (data == '\r')) {
        complete = 1;
      } else {
        message[num_bytes] = data;
        ++num_bytes;
        // roll over if the array is too small
        if (num_bytes >= maxLength) {
          num_bytes = 0;
        }
      }
    }
  }
  // end the string
  message[num_bytes] = '\0';
}