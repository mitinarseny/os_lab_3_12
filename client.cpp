#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/errno.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "shared.h"

int main() {
	int mqID = getMQID();
	pid_t PID = ::getpid();
	std::cout << "[C] MQ ID: " << mqID << ", PID: " << PID << std::endl;

	int fds[2];
	if (pipe(fds) != 0) {
		std::perror("pipe");
		return EXIT_FAILURE;
	}
	pid_t chPID;
	switch (chPID = fork()) {
	case -1:
		std::perror("fork");
		return EXIT_FAILURE;
	case 0: //child
		while (dup2(fds[1], STDOUT_FILENO) == -1) {
			if (errno == EINTR)
				continue;
			std::perror("dup2");
			return EXIT_FAILURE;
		}
		if (close(fds[0]) == -1) {
			std::perror("close");
			return EXIT_FAILURE;
		}
		if (close(fds[1]) == -1) {
			std::perror("close");
			return EXIT_FAILURE;
		}
		execl("/usr/bin/cal", "cal", "-h", NULL);
		std::perror("execl");
		return EXIT_FAILURE;
	}

	if (close(fds[1]) == -1) {
		std::perror("close");
		return EXIT_FAILURE;
	}

	clientMsg_t msg {
		.PID = PID,
	};
	for (auto [count, n] = std::tuple{0, 0}; n = read(fds[0], msg.cal + count, sizeof(msg.cal) - count); count += n) {
		if (n == -1) {
			if (errno == EINTR) {
				continue;
			}
			std::perror("read");
			return EXIT_FAILURE;
		}
		// std::cout << msg.cal + count;
	}
	
	int ws;
	if (waitpid(chPID, &ws, 0) == -1) {
	  std::perror("waitpid");
		return EXIT_FAILURE;
	}
	
	if (ws != EXIT_SUCCESS) {
		std::cerr << "cal (PID " << chPID << ") exited with code " << ws << std::endl; 
		return EXIT_FAILURE;
	}
	msgbuf_t msgbuf {
		.msg = msg,
	};
	if (::msgsnd(mqID, &msgbuf, sizeof(msgbuf.msg), IPC_NOWAIT) == -1) {
		std::perror("msgsnd");
		return EXIT_FAILURE;
	}

	std::cout << "[C] message was sent!" << std::endl;

	return EXIT_SUCCESS;
}
