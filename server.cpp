#include "shared.h"

#include <sys/types.h>
#include <sys/msg.h>

#include <iostream>

enum WEEKDAY {
	SUNDAY,
	MONDAY,
	TUESDAY,
	WENSDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
};

ssize_t rcv(int mqID, msgbuf_t *msgbuf) {
	auto s = ::msgrcv(mqID, msgbuf, sizeof(msgbuf->msg), MSG_TYPE, 0);
	if (s == -1)
		std::perror("msgrcv");
	return s;
}

WEEKDAY process(clientMsg_t *msg) {
	// std::cout << buf << std::endl;
	return MONDAY;
}

std::string strWeekday(WEEKDAY wd) {
	switch (wd) {
	case SUNDAY:
		return "sunday";
	case MONDAY:
		return "monday";
	case TUESDAY:
		return "tuesday";
	case WENSDAY:
		return "wensday";
	case THURSDAY:
		return "thursday";
	case FRIDAY:
		return "friday";
	case SATURDAY:
		return "saturday";
	}
}

int main() {
	int mqID = getMQID();
	std::cout << "MQ ID: " << mqID << std::endl;

	msgbuf_t msgbuf;
	auto s = rcv(mqID, &msgbuf);
	if (s == -1)
		return EXIT_FAILURE;

	std::cout << "[S] recieved message:" << std::endl
		<< msgbuf.msg.cal << std::endl;

	process(&msgbuf.msg);
	
	return EXIT_SUCCESS;
}
