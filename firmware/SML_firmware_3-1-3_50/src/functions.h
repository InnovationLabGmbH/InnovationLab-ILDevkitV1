#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

using byte = unsigned char;


// functions for byte conversion
unsigned long bytes2int(byte* bdata);
void int2bytes(int val, byte* bdata);

#endif