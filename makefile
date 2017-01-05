CC = gcc

CFLAGS = -std=c99 -pedantic -Wall -Werror
#CFLAGS = -std=c99 -pedantic -Wall

#RELEASE_FLAGS = -O2
RELEASE_FLAGS =

DEBUG_FLAGS = -g -DMYDEBUG

run-test : build-release
	./ByteRingBufferU32L_TEST

run-debug : build-debug
	./ByteRingBufferU32L_TEST

run-gdb : build-debug
	gdb ./ByteRingBufferU32L_TEST

run-valgrind : build-debug
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck --track-origins=yes ./ByteRingBufferU32L_TEST

run-valgrind-fullDBG-report : build-debug
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck --track-origins=yes ./ByteRingBufferU32L_TEST > Valgrind_Test_Report.txt 2>&1 

run-valgrind-report : build-release
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck --track-origins=yes ./ByteRingBufferU32L_TEST > Valgrind_Test_Report.txt 2>&1 

build-release : CFLAGS += $(RELEASE_FLAGS)
build-release : ByteRingBufferU32L.o ByteRingBufferU32L_TEST.o ByteRingBufferU32L.h
	$(CC) $(CFLAGS) ByteRingBufferU32L_TEST.o ByteRingBufferU32L.o -o ByteRingBufferU32L_TEST

build-debug : CFLAGS += $(DEBUG_FLAGS)
build-debug : ByteRingBufferU32L.o ByteRingBufferU32L_TEST.o ByteRingBufferU32L.h
	$(CC) $(CFLAGS) ByteRingBufferU32L_TEST.o ByteRingBufferU32L.o -o ByteRingBufferU32L_TEST

ByteRingBufferU32L.o : ByteRingBufferU32L.c ByteRingBufferU32L.h
	$(CC) $(CFLAGS) -c ByteRingBufferU32L.c

ByteRingBufferU32L_TEST.o : ByteRingBufferU32L_TEST.c ByteRingBufferU32L.h
	$(CC) $(CFLAGS) -c ByteRingBufferU32L_TEST.c

clean :
	rm *.o ByteRingBufferU32L_TEST
