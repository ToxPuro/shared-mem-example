shared-mem.o: shared-mem-write.o shared-mem-read.o shared-mem.cpp
	g++ -o shared-mem.o shared-mem.cpp
shared-mem-write.o:  shared-mem-write.cpp
	g++ -o shared-mem-write.o shared-mem-write.cpp
shared-mem-read.o:  shared-mem-read.cpp
	g++ -o shared-mem-read.o shared-mem-read.cpp
