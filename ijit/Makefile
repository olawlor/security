all: ijit32 ijit64

ijit32: ijit.c
	gcc -m32 ijit.c -g -o ./ijit32

ijit64: ijit.c
	gcc -m64 ijit.c -g -o ./ijit64

run32: ijit32
	nc -l -p 8888 | sudo -u nobody ./ijit32 

clean:
	rm ijit32 ijit64
