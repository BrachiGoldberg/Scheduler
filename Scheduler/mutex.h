#ifndef MUTEX_H
#define MUTEX_H

#include <Windows.h>

#include "logger.h"
#include "consts.h"

HANDLE tree_mutex;
HANDLE queue_mutex;

//create tree mutex
void create_tree_mutex();

//lock tree mutex
void lock_tree_mutex();

//release tree mutex
void release_tree_mutex();

//create queue mutex
void create_queue_mutex();

//lock queue mutex
void lock_queue_mutex();

//release queue mutex
void release_queue_mutex();

#endif // !MUTEX_H
