#ifndef PSTAT_H
#define PSTAT_H

void smodef(char *buf, mode_t mode);

void sprint_humansize(char *buf,off_t size);

off_t print_fstat(char *filepath);

off_t fsize(char *filepath);

#endif
