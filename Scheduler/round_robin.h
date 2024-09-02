
#ifndef _ROUND_ROBIN_H
#define _ROUND_ROBIN_H

#include <Windows.h>

#include "general_settings.h"
#include "RealTimeTaskQueue.h"
#include "QueueNode.h"
#include "RealTimeTask.h"

void execute_queue(struct real_time_task_queue* queue);

#endif // !_ROUND_ROBIN_H