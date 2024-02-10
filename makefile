CC=gcc
O=-funroll-all-loops -faggressive-loop-optimizations -funsafe-math-optimizations -fno-unwind-tables -fprefetch-loop-arrays -fno-stack-protector -Ofast

all: clean
	@$(CC) -ULUT $O m.c -or && ./r
	@$(CC) -DLUT $O m.c -ol && ./l

clean:
	@rm -f r l
