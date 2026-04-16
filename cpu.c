# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include "cpu.h"

CPUData cpuJiffies(int option){
    // I want get more data from 0 and 1 data, so I make some integer select for select
    // where all, core 1 (0) and core 2 (1)
    // so :
    // 1 -> All cpu
    // 2 -> core 1 (0)
    // 3 -> core 2 (1)
    
    // cpu user nice system idle   iowait irq softirq steal guest guest_nice
    // cpu 3305 13   2145   178309 14682  0   15      0     0     0
    // user : user works
    // nice : where program not using lot source while using cpu / lower priority
    // system : os system
    // idle : system idle
  
    FILE *file;
    char line[256];

    long user, nice, system, idle, iowait, irq, softirq, steal; 
    CPUData data;

    file = fopen("/proc/stat", "r");

    if (file == NULL){
      printf("Cannot open stat file\n");
    }

    while(fgets(line, sizeof(line), file)){

    switch(option){
     case 1 :
      // get cpu 
        if (strncmp(line, "cpu ", 4) == 0){
          sscanf(line, "cpu %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
        }

        break;
     case 2 : 
      // get core 1 (0)
        if (strncmp(line, "cpu0", 4) == 0){
          sscanf(line, "cpu0 %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
        }

        break;
     case 3 :
      // get core 2 (1)
        if (strncmp(line, "cpu1", 4) == 0){
          sscanf(line, "cpu1 %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
        }

        break;
    }

     
    }
      
    fclose(file);

    data.total = user + nice + system + idle + iowait + irq + softirq + steal;
    data.idle = idle + iowait;
   
    return data;

 }

CPUusage cpuStat(int cpuOption){

   // t0 and t1 (t meaning data total user + nice + system + idle... etc)
   long t0Total;
   long t1Total;

   long t0Idle;
   long t1Idle;

   long deltaTotal;
   long deltaIdle;

   double cpuUsage = 0;
   CPUusage data;
   
   // get t1 data total and Idle
   CPUData CPUdata = cpuJiffies(cpuOption);
   t0Total = CPUdata.total;
   t0Idle = CPUdata.idle;

   // suspend or sleep on 1 sec
   sleep(1);

   // get t2 data total and Idle 
   CPUData CPUdatanew = cpuJiffies(cpuOption);
   t1Total = CPUdatanew.total;
   t1Idle = CPUdatanew.idle;

   deltaTotal = t1Total - t0Total;
   deltaIdle = t1Idle - t0Idle;

   // cpu usage
   // evaluate this formula
   cpuUsage = (deltaTotal - deltaIdle) * 100.0 / deltaTotal;

   data.cpuUsage = cpuUsage;

   return data;
   
}
