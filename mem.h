#ifndef MEM
#define MEM

typedef struct {
  long memTotal;
  long memFree;
  long memAvailable;
  long totalSwap;
  long freeSwap;
  long usageSwap;
  
  double memUsage;
  double memUsagePercent;
  double usageSwapPercent;
} MEMusage;

MEMusage memStat();


#endif
