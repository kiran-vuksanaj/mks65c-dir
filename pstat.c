#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/types.h>

void smodef(char *buf, mode_t mode) {
  // printf("[mode octal: %o]\n",mode);
  short b = 0400; // the first byte to be considered is 0400, you can right shift until you've examined every bite
  short i;
  for( i = 0; i < 9; i++ ) {
    // printf("[byte octal: %6o]\n",b);
    if( b & mode ) {
      if( i % 3 == 0 ) buf[i] = 'r';
      if( i % 3 == 1 ) buf[i] = 'w';
      if( i % 3 == 2 ) buf[i] = 'x';
    }else {
      buf[i] = '-';
    }
    b = b >> 1;
  }
  buf[i] = '\0';
}
