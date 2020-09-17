CPPFLAGS := \
	--std=c++2a \
	-Wall

.PHONY: build
build: client

# server: server.cpp
# 	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $<

client: shared.cpp client.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -o $@ $^
