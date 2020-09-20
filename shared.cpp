#include "shared.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

#include <string>
#include <iostream>

const std::string PATH = "/tmp/os_lab_mq";
constexpr int     ID   = 1234;

std::ostream& operator <<(std::ostream& os, Weekday wd) {
	std::string s;
	switch (wd) {
	case Weekday::mon: s = "monday";   break;
	case Weekday::tue: s = "tuesday";  break;
	case Weekday::wed: s = "wensday";  break;
	case Weekday::thu: s = "thursday"; break;
	case Weekday::fri: s = "friday";   break;
	case Weekday::sat: s = "saturday"; break;
	case Weekday::sun: s = "sunday";   break;
	}
	return os << s;
}

key_t getMQKey() {
	if (::creat(PATH.c_str(), 0666) == -1) {
		std::perror("creat");
		return -1;
	}
	std::system(("touch " + PATH).c_str());
	key_t key = ::ftok(PATH.c_str(), ID);
	if (key == -1) {
		std::perror("ftok");
	}
	return key;
}

int getMQID() {
	key_t key = getMQKey();
	int id = ::msgget(getMQKey(), IPC_CREAT | 0666);
	if (id == -1) {
		std::perror("msgget");
	}
	return id;
}
