#ifndef SHARED_H
#define SHARED_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include <string>

constexpr long MSG_TYPE = 1;

constexpr std::size_t CAL_SIZE = 1024;

struct clientMsg_t {
	pid_t PID;
	unsigned char cal[CAL_SIZE];
};

struct msgbuf_t {
	long type = MSG_TYPE;
	clientMsg_t msg;
};

key_t getMQKey();

int getMQID();

#endif // SHARED_H
