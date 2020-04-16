#ifndef UART__H__
#define UART__H__

void initUART();
void writeUART(char*);
void readUART(char * message, int maxLength);

#endif // UART__H__