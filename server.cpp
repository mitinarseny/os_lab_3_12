#include "shared.h"

#include <sys/types.h>
#include <sys/msg.h>

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <limits>

std::istream& operator >>(std::istream& is, Weekday& wd) {
	std::string s;
	is >> s;
	if (s == "Mo")
		wd = Weekday::mon;
	else if (s == "Tu")
		wd = Weekday::tue;
	else if (s == "We")
		wd = Weekday::wed;
	else if (s == "Th")
		wd = Weekday::thu;
	else if (s == "Fr")
		wd = Weekday::fri;
	else if (s == "Sa")
		wd = Weekday::sat;
	else if (s == "Su")
		wd = Weekday::sun;
	return is;
}

ssize_t rcv(int mqID, msgbuf_t& msgbuf) {
	auto s = ::msgrcv(mqID, &msgbuf, sizeof(msgbuf.msg), MSG_TYPE, 0);
	if (s == -1)
		std::perror("msgrcv");
	return s;
}

Weekday firstDayOfMonth(const char cal[CAL_SIZE]) {
	std::istringstream ss(cal);

	ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // month

	Weekday weekStart;
	ss >> weekStart;
	ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip other weekdays
	
	std::string firstWeekDates;
	std::getline(ss, firstWeekDates);
	auto firstWeekday = static_cast<Weekday>(firstWeekDates.find("1") / 3); // each date is 3 chars

	return weekStart + firstWeekday;
}

void process(clientMsg_t& msg) {
	auto now = std::time(nullptr);
	auto firstDay = firstDayOfMonth(msg.cal);
	Weekday currentDayOfWeek = firstDayOfMonth(msg.cal) + std::localtime(&now)->tm_mday - 1;
	std::cout << "PID: " << msg.PID << ", day of week: " <<  currentDayOfWeek << std::endl;
}

int main() {
	int mqID = getMQID();
	std::cout << "MQ ID: " << mqID << std::endl;
	
	msgbuf_t msgbuf;
	while (auto s = rcv(mqID, msgbuf)) {
		if (s == -1)
			return EXIT_FAILURE;
		
		std::cout << "[S] ";
		process(msgbuf.msg);
	}
	return EXIT_SUCCESS;
}
