#ifndef DISK
#define DISK

typedef struct {
  unsigned long free;
  unsigned long used;
  unsigned long total;
  
  double diskUsage;
} DISKusage;

DISKusage diskUsage();

#endif 
