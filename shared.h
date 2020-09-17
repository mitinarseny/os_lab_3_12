#ifndef SHARED_H
#define SHARED_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <string>

constexpr long MSG_TYPE = 1;

constexpr std::size_t MSG_SIZE = 1024;

struct msg_t {
	long mtype;
	unsigned char mtext[MSG_SIZE];
};

key_t getMQKey();

int getMQID();

#endif // SHARED_H
