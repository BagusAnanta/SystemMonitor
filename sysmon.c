# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "cpu.h"
# include "mem.h"
# include "disk.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

double memtotal, memfree, memaval, memusage, memtotal, swaptotal, swapfree, swapUsage, diskfree, diskused, disktotal;
const char *unit, *unit1, *unit2, *unit3, *unit4, *unit5, *unit6, *unit7, *unit8;

void cleanup(){
  printf("\033[?25h");
  printf("\033[?1049l");
  fflush(stdout);
}

void handle_sigint(int sig){
  cleanup();
  exit(0);
}

const char* getColor(float usage){
  if (usage < 50){
    return GREEN;
  } else if (usage < 80){
    return YELLOW;
  } else {
    return RED;
  }
}

void drawLine(int row, const char* label, float usage){
  printf("\033[%d;1H", row);

  printf("%s ", label);

  //printf("\033[%d;20H", row);

  // for bar 
  int barwidth = 20;
  int filled = (usage / 100.0) * barwidth;

  printf("[");
  for (int i = 0; i < barwidth; i++){
      if (i < filled){
        printf("#");
      } else {
        printf("-");
      }
  }
  printf("]");
   
  printf("\033[%d;40H", row);
  printf("%s%.2f%%%s", getColor(usage), usage, RESET);

}

void formatSize(double sizeKb, double *value, const char **unit){
  static const char *units[] = {"B","KB", "MB", "GB", "TB"};
  int pos = 1;

  double size = sizeKb;

  while(size >= 1024 && pos < 3){
    size /= 1024;
    pos++;
  }

  *value = size;
  *unit = units[pos];
  
}

int main(){

 atexit(cleanup);
 signal(SIGINT, handle_sigint);
 
 printf("\033[?1049h"); // full screen
 printf("\033[?25l"); // hide cursor 

 while (1){

   // call function for cpu
   CPUusage cpu1UsageData = cpuStat(1);
   CPUusage cpu2UsageData = cpuStat(2);
   CPUusage cpu3UsageData = cpuStat(3);

   // call function for memory
   MEMusage memUsageData = memStat();

   // call function for disk
   DISKusage diskUsageData = diskUsage();

   // clear all character at terminal and back to the top
   printf("\033[2J\033[H");

   // mem format
   formatSize(memUsageData.memTotal, &memtotal, &unit);
   formatSize(memUsageData.memFree, &memfree, &unit);
   formatSize(memUsageData.memAvailable, &memaval, &unit);
   formatSize(memUsageData.memUsage, &memusage, &unit1);;
   
   // disk format 
   formatSize(diskUsageData.used, &diskused, &unit3);
   formatSize(diskUsageData.total, &disktotal, &unit4);
   formatSize(diskUsageData.free, &diskfree, &unit5);

   // swap format
   formatSize(memUsageData.totalSwap, &swaptotal, &unit6);
   formatSize(memUsageData.freeSwap, &swapfree, &unit7);
   formatSize(memUsageData.usageSwap, &swapUsage, &unit8);

   printf("=============================== SYSTEM MONITOR ===========================\n");

   printf("RAM Free  : %.2f %s\n", memfree, unit);
   printf("RAM Available : %.2f %s\n", memaval, unit);
   printf("RAM : %.2f %s Used/ %.2f %s Total\n", memusage,unit1,memtotal,unit);
   printf("SWAP : %.2f %s Used/ %.2f %s Total\n", swapUsage,unit8,swaptotal,unit7);
   printf("Disk : %.2f %s Used / %.2f %s Total\n", diskused, unit3, disktotal, unit4);
   printf("Disk Free  : %.2f %s\n", diskfree, unit5);

   printf("==========================================================================");

   drawLine(9, "Memory Usage", memUsageData.memUsagePercent);
   drawLine(10, "Swap", memUsageData.usageSwapPercent);
   drawLine(11, "Disk Usage", diskUsageData.diskUsage);
   drawLine(12, "CPU Usage", cpu1UsageData.cpuUsage);
   drawLine(13, "CPU 0 Usage", cpu2UsageData.cpuUsage);
   drawLine(14, "CPU 1 Usage", cpu3UsageData.cpuUsage);

   printf("\n==========================================================================");
    
   fflush(stdout);

   sleep(1);

 }
 
  return 0;
}
