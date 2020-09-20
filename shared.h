#ifndef SHARED_H
#define SHARED_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include <cstdint>
#include <string>

constexpr long MSG_TYPE = 1;

constexpr std::size_t CAL_SIZE = 1024;

enum struct Weekday: std::uint8_t {mon, tue, wed, thu, fri, sat, sun};

inline int mod(int a, int b) {
	return (a % b + b) % b;
}

template <typename T>
Weekday operator +(Weekday l, T r) {
	return static_cast<Weekday>(mod(static_cast<int>(l) + static_cast<int>(r), static_cast<int>(Weekday::sun) + 1));
}

template <typename T>
Weekday operator -(Weekday l, T r) {
	return l + (-r);
}

template <typename T>
Weekday& operator +=(Weekday& wd, T r) {
	return wd = wd + r;
}

std::ostream& operator <<(std::ostream& os, Weekday wd);

struct clientMsg_t {
	pid_t PID;
	char cal[CAL_SIZE];
};

struct msgbuf_t {
	long type = MSG_TYPE;
	clientMsg_t msg;
};

key_t getMQKey();

int getMQID();

#endif // SHARED_H
