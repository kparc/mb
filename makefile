ifeq ($(shell uname),Darwin)
 # on darwin m1, stock clang will do the trick
 CC=clang
else
 CC=$(shell env env which gcc-13||which gcc-12||which gcc-11||which gcc-10||env which gcc-9||env which gcc-8||echo gcc) # on linux rpi4/x86 and similar junk, gcc is for the win
 #O=-ftree-parallelize-loops=100
endif

W=-Wno-ignored-optimization-argument
O+= -funroll-all-loops -funsafe-math-optimizations -fno-unwind-tables -fprefetch-loop-arrays -fno-stack-protector -Ofast $W

all: clean
	$(shell $(CC) -v | grep version)
	@$(CC) -ULUT $O m.c -or && ./r
	@$(CC) -DLUT $O m.c -ol && ./l

clean:
	@rm -f r l
