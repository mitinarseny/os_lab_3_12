#include "shared.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <string>
#include <iostream>

const std::string PATH = "/tmp/os_lab_mq";
constexpr int     ID   = 1234;

key_t getMQKey() {
	std::system(("touch " + PATH).c_str());
	key_t key = ::ftok(PATH.c_str(), ID);
	if (key == -1) {
		std::perror("ftok");
	}
	return key;
}

int getMQID() {
	key_t key = getMQKey();
	std::cout << "MQ KEY: " << key << std::endl;
	int id = ::msgget(getMQKey(), IPC_CREAT | 0666);
	if (id == -1) {
		std::perror("msgget");
	}
	return id;
}
