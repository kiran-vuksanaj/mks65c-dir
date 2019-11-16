#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include<sys/types.h>
#include<dirent.h>

#include"pstat.h"

off_t ls(char *path);
// NOTE: i'm assuming that path points to an allocation that has! enough! space! for all pathnames

int main() {
  char pathbuf[512] = ".";
  off_t out = ls(pathbuf);
  printf("note: all directories beginning with '.' passed over to avoid infinite recursion\n");
}

off_t ls(char *path) {
  int status;
  DIR *cwd = opendir(path);
  off_t total = 0;
  strcat(path,"/");
  // printf("directory %s\n",path);
  if(!cwd) {
    printf("Error while opening [%s]: [%d] - %s\n",path,errno,strerror(errno));
    return -1;
  }
  // printf("const DT_DIR: %hhd\n",DT_DIR);
  // printf("const DT_REG: %hhd\n",DT_REG);
  struct dirent *dirfile = readdir(cwd);
  while(dirfile) {
    // printf("file of type %hhd\n",dirfile->d_type);
    switch(dirfile->d_type) {
    case DT_DIR:
      strcat(path,dirfile->d_name);
      total += print_fstat(path);
      if( dirfile -> d_name[0] != '.') total += ls(path);
      *(strrchr(path,'/')+1) = '\0';
      // printf("directory [%s]/\n",path);
      break;
    case DT_REG:
      strcat(path,dirfile->d_name);
      total += print_fstat(path);
      *(strrchr(path,'/')+1) = '\0';
      break;
    default:
      printf("is something else\n");
      break;
    }
    dirfile = readdir(cwd);
  }
  // char size_h[15] = "";
  // sprint_humansize(size_h,total);
  printf("total size: %12ld B %s\n\n",total,path);
  *(strrchr(path,'/')) = '\0';
  // closedir(cwd);
  return total;
}
