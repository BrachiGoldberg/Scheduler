#ifndef GENERAL_SETTINGS_H
#define GENERAL_SETTINGS_H

static long ID = 0;
#define SCHED_LATENCY 20      // Latency  in milliseconds
#define MIN_QUANTUM 5         // Minimum quantum time in milliseconds

#define QUANTUM_TREE 3        // Quantum-The number of tasks  in the tree structure 
#define QUANTUM_QUEUE 5       // Quantum-The number of tasks  in the queue 

#define DEFULT_WEIGHT 1024    // Default task weight (neutral priority)

#define MIN_TIME_SLICE 1      // Minimum time slice in milliseconds

#define LOGGER_FILE "log.log"
#define MAX_LOGGER_FILE_SIZE (1024 * 1024) // 1MB
#define MAX_LOGGER_BUCKUP_FILES 20

#endif // !GENERAL_SETTINGS_H