#ifndef CFS_H
#define CFS_H

#include "rb_tree.h"
#include "scheduler.h"
#include "general_settings.h"
#include "logger.h"
#include "consts_logs.h"

void execute_tree(rb_tree* tasks_tree);

#endif