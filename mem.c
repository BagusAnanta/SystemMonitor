# include <stdio.h>
# include <string.h>
# include "mem.h"

MEMusage memStat(){

    FILE *file;
    char line[256];

    long memTotal = 0;
    long memFree = 0;
    long memAvailable = 0;
    long totalSwap = 0;
    long freeSwap = 0;
    
    double memUsage = 0;
    double memUsagePercent = 0;
    double swapUsage = 0;
    double swapUsagePercent = 0;

    MEMusage data;

    file = fopen("/proc/meminfo", "r");

    // check condition meminfo file
    if (file == NULL){
      printf("Cannot open meminfo file\n");
    }

    // get file
    while(fgets(line, sizeof(line), file)){
      if (strncmp(line, "MemTotal:", 9) == 0){
        sscanf(line, "MemTotal: %ld", &memTotal);
      }

      if (strncmp(line, "MemFree:", 8) == 0){
        sscanf(line, "MemFree: %ld", &memFree);
      }

      if (strncmp(line, "MemAvailable:", 13) == 0){
        sscanf(line, "MemAvailable: %ld", &memAvailable);
      }

      if (strncmp(line, "SwapTotal:", 10) == 0){
        sscanf(line, "SwapTotal: %ld", &totalSwap);
      }

       if (strncmp(line, "SwapFree:", 9) == 0){
        sscanf(line, "SwapFree: %ld", &freeSwap);
      }
    }

    fclose(file);

    memUsage = memTotal - memAvailable;
    swapUsage = totalSwap - freeSwap;
    memUsagePercent = (memUsage / memTotal) * 100.0;
    swapUsagePercent = (swapUsage / freeSwap) * 100.0;
    

    data.memTotal = memTotal;
    data.memFree = memFree;
    data.memAvailable = memAvailable;
    data.memUsage = memUsage;
    data.memUsagePercent = memUsagePercent;
    data.totalSwap = totalSwap;
    data.freeSwap = freeSwap;
    data.usageSwap = swapUsage;
    data.usageSwapPercent = swapUsagePercent;

    return data;

}
