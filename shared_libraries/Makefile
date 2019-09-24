all: preload.so

preload.so: preload.c
	gcc -fPIC -shared preload.c -o preload.so

clean:
	-rm preload.so

