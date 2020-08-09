#pragma once
#include <iostream>

#define pr_err(msg, args...) fprintf(stderr, "ERROR: " msg "\n", ##args)
#define pr_warn(msg, args...) fprintf(stderr, "WARNING: " msg "\n", ##args)
#define pr_dbg(msg, args...) fprintf(stderr, "DEBUG(%s:%d): " msg "\n", __FILE__, __LINE__, ##args)
#define pr_info(msg, args...) fprintf(stderr, "INFO: " msg "\n", __FILE__, __LINE__, ##args)

enum ClientMessages {
	ERROR = -1,
	FOREVARD = 0,
	STOP,
	ROTATE,
};