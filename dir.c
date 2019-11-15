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
  // printf("const DT_DIR: %hhd\n",DT_DIR);
  // printf("const DT_REG: %hhd\n",DT_REG);
  struct dirent *dirfile = readdir(cwd);
  while(dirfile) {
    // printf("file of type %hhd\n",dirfile->d_type);
    switch(dirfile->d_type) {
    case DT_DIR:
      printf("is a directory\n");
      break;
    case DT_REG:
      printf("is a file\n");
      break;
    default:
      printf("is something else\n");
      break;
    }
    dirfile = readdir(cwd);
  }
  return 0;
}
