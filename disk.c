# include <sys/statvfs.h>
# include "disk.h"

DISKusage diskUsage(){
  struct statvfs stat;

  int statvfschk = 0;
  unsigned long used = 0;
  unsigned long free = 0;
  unsigned long total = 0;
  double diskUsage = 0;
  DISKusage data;

  statvfschk = statvfs("/", &stat);

  if (statvfschk == -1){
    // error condition
    
  }

  total = (stat.f_blocks * stat.f_frsize) / 1024.0;

  free = (stat.f_bavail * stat.f_frsize) / 1024.0;

  used = total - free;
  
  diskUsage = ((used * 100.0) / total) / 1024.0;

  data.total = total; 
  data.free = free; 
  data.used = used;
  data.diskUsage = diskUsage;

  // data.total = toGB(total); // convert to GB 
  // data.free = toGB(free); // convert to GB 
  // data.used = toGB(used); // convert to GB
  // data.diskUsage = diskUsage;

  return data; 
}
