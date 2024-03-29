#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/types.h>

#include<time.h>

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

void sprint_humansize(char *buf,off_t size) {
  // assumed that buf has min 6 bytes
  char *abbreviations = " KMGT";
  int scale_count = 0;
  float size_f = size;
  while(size_f > 1000 && scale_count < 5){
    size_f /= 1024.0;
    scale_count++;
  }
  if(scale_count == 0){
    sprintf(buf,"%3ld B",size);
  }else{
    char floatbuf[9];
    sprintf(floatbuf,"%f",size_f);
    if(floatbuf[2]=='.') floatbuf[2] = ' ';
    sprintf(buf,"%.3s%cB",floatbuf,abbreviations[scale_count]);
  }
}

off_t print_fstat(char *filepath) {
  struct stat statbuf;
  int status;
  status = stat(filepath,&statbuf);
  if(status < 0) {
    printf("Error %d while statting file [%s]: %s\n",errno,filepath,strerror(errno));
    return 0;
  }
  char mode[10];
  smodef(mode,statbuf.st_mode);
  // char size[6];
  // sprint_humansize(size,statbuf.st_size);
  char time[26];
  ctime_r(&statbuf.st_atim.tv_sec,time);
  printf("%s %12ld B %.12s %s\n",mode,statbuf.st_size,time+4,filepath);
  return statbuf.st_size;
}

off_t fsize(char *filepath) {
  // for a situation in which you want the size but you don't want to print all the other stat info
  struct stat statbuf;
  int status;
  status = stat(filepath,&statbuf);
  if(status < 0) {
    printf("Error while getting size of file %s: [%d] - %s\n",filepath,errno,strerror(errno));
    return 0;
  }
  return statbuf.st_size;
}
