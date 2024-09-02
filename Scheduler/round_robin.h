#ifndef _ROUND_ROBIN_H
#define _ROUND_ROBIN_H

#include <Windows.h>
#include "general_settings.h"
#include "real_time_task_queue.h"
#include "queue_node.h"
#include "real_time_task.h"
#include "logger.h"
#include "consts.h"

void execute_queue( real_time_task_queue* queue);

#endif // !_ROUND_ROBIN_H