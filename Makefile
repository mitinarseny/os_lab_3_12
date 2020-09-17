CPPFLAGS := \
	--std=c++2a \
	-Wall

PROGS := client server

.PHONY: build
build: $(PROGS)


$(PROGS): %: %.cpp shared.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -o $@ $^

