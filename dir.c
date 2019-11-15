#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>

int main() {
  int status;
  DIR *cwd = opendir(".");
  if(!cwd) {
    printf("Error while opening .: [%d] - %s\n",errno,strerror(errno));
    return 1;
  }
  // printf("const DT_DIR: %hhd\n",DT_DIR);
  // printf("const DT_REG: %hhd\n",DT_REG);
  struct dirent *dirfile = readdir(cwd);
  struct stat statbuf;
  while(dirfile) {
    // printf("file of type %hhd\n",dirfile->d_type);
    switch(dirfile->d_type) {
    case DT_DIR:
      printf("directory [%s]/\n",dirfile->d_name);
      break;
    case DT_REG:
      status = stat(dirfile->d_name,&statbuf);
      if(status < 0){
	printf("Error while statting [%s]: [%d] - %s",dirfile->d_name,errno,strerror(errno));
	break;
      }
      printf("%9o [%s] (%ld bytes)\n",statbuf.st_mode,dirfile->d_name,statbuf.st_size);
      break;
    default:
      printf("is something else\n");
      break;
    }
    dirfile = readdir(cwd);
  }
  return 0;
}
