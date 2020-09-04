#pragma once
#include <iostream>

#define pr_err(msg, args...) fprintf(stderr, "ERROR: " msg "\n", ##args)
#define pr_warn(msg, args...) fprintf(stderr, "WARNING: " msg "\n", ##args)
#define pr_dbg(msg, args...) fprintf(stderr, "DEBUG(%s:%d): " msg "\n", __FILE__, __LINE__, ##args)
#define pr_info(msg, args...) fprintf(stderr, "INFO: " msg "\n", __FILE__, __LINE__, ##args)

//Use this in client/server enumerations
#define MSGCODES 	\
	Error = -1, \
	Forevard = 0, \
	Backward, \
	RotateLeft, \
	RotateRight, \
	Stop,

enum ClientMessages {
	MSGCODES
};

enum DataTypeId {
	tDistances = 1
};
