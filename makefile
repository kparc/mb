CC=clang
all:
	rm -f m && $(CC) -ffast-math -fno-unwind-tables -fno-stack-protector -O3 m.c -o m
	./m
	rm -f l && $(CC) -ffast-math -fno-unwind-tables -fno-stack-protector -O3 l.c -o l
	./l
