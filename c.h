#include<time.h>
#include<stdio.h> 
#include<stdlib.h> 

typedef double F;

#define BENCH()           F wall=0;struct timespec start,end;
#define TIME(x)           clock_gettime(CLOCK_REALTIME,&x);
#define MSEC(x)           (x.tv_sec*1000+x.tv_nsec/1000000.0)
#define WALL(a...)        TIME(start);a;TIME(end);wall=(MSEC(end)-MSEC(start))/1000.0;
#define SEED
//#define SEED              srand(time(0));

#define ROUNDS 200

typedef unsigned int I;
#define O printf
#define N(n,a...){I i=0,_n=(n);while(i<_n){a;++i;}}
#define Nj(n,a...){I j=0,_n=(n);while(j<_n){a;++j;}}

int pick(){
    return (rand() % (11 - 0 + 1)) + 0; 
}

const size_t bigger_than_cachesize = 10 * 1024 * 1024;
long p[bigger_than_cachesize];

#define BUSYWORK() for(int i=0;i<bigger_than_cachesize;i++)p[i]=rand();

//:~