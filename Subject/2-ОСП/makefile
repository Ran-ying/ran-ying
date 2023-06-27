.PHONY: all clean
all: main
clean:
	rm -rf *.o lab12 libuuid.so

lab12.o: lab12.c
	gcc -c lab12.c -std=gnu99
main: lab12.o
	gcc -shared -fPIC -o libuuid.so uuid.c -std=gnu99
	gcc -o lab12 lab12.o -ldl
