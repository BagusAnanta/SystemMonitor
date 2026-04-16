#ifndef CPU
#define CPU

typedef struct {
  long total;
  long idle;
} CPUData;

typedef struct {
  double cpuUsage;
} CPUusage;

CPUData cpuJiffies(int option);
CPUusage cpuStat(int cpuOption);

#endif 
