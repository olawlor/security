OPTS=-O1
CODE=../../web/cpp
CFLAGS= -I$(CODE)/include  $(OPTS) -Wall -fopenmp -fomit-frame-pointer -fopenmp -marm -mfloat-abi=hard -mfpu=neon 

all: run

smashy: smashy.cpp
	g++ $< -o $@ $(CFLAGS)

bake: bake_gadgets.cpp
	g++ $< -o $@ $(CFLAGS)
	./bake | tee rop_chain

run: bake smashy
	cat rop_chain | strace ./smashy

clean:
	rm smashy

