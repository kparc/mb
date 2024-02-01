CC=clang
all:
	rm -f m && $(CC) -ffast-math -Os m.c -o m
	./m
	rm -f l && $(CC) -ffast-math -Os l.c -o l
	./l
