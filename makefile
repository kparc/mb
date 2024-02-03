CC=gcc-13
O=-ffast-math -fno-unwind-tables -fno-stack-protector -Ofast

all: clean
	@$(CC) -ULUT $O m.c -or
	@./r
	@$(CC) -DLUT $O m.c -ol
	@./l

clean:
	@!rm -f r l
