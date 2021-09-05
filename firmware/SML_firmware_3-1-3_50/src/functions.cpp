#include "functions.h"

// computes an integer from a given byte array
unsigned long bytes2int(byte* bdata) {
  unsigned long val = 0;
  for (int i = 1; i <= sizeof(bdata); i++) {
    val += bdata[i - 1] << (sizeof(bdata) - i) * 8;
  }
  return val;
}

// splits an integer into bytes and fills a given array with it
void int2bytes(int val, byte* bdata) {
  for (int i = 0; i < sizeof(bdata); i++) {
    bdata[i] = (val >> (i * 8)) & 0xFF;
  }
}