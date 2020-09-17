#include "shared.h"

#include <sys/types.h>
#include <sys/msg.h>

#include <iostream>

int main() {
	int id = getMQID();
	std::cout << "MQ ID: " << id << std::endl;

	msg_t msg;
	ssize_t s = ::msgrcv(id, &msg, sizeof(msg.mtext), MSG_TYPE, 0);
	std::cout << "msgrcv: " << s << std::endl << msg.mtext << std::endl;
}
