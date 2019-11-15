#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>

int main() {
  DIR *cwd = opendir(".");
  if(!cwd) {
    printf("Error while opening .: [%d] - %s\n",errno,strerror(errno));
  }
  struct dirent *dirfile = readdir(cwd);
  while(dirfile) {
    printf("file\n");
    dirfile = readdir(cwd);
  }
  return 0;
}
