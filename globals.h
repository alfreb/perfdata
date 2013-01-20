#ifndef GLOBALS_H
#define GLOBALS_H
//Number of columns pr. cpu in /proc/stat
#define CPU_PROP_COUNT 10
  
//Names for the columns
enum cpu_prop {USER,NICE,SYSTEM,IDLE,IOWAIT,IRQ,SOFTIRQ,STEAL,USER_RT,SYSTEM_RT}; 

#endif
