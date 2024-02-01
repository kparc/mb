#include<time.h>
#include<stdio.h> 
#include<stdlib.h> 

typedef double F;typedef int I; typedef unsigned int UI;typedef unsigned long long UJ;
#define Zin __attribute__((always_inline)) inline

#define ARENA 10000000
#define ROUNDS 2000

#define BENCH()           F wall=0;struct timespec start,end;
#define TIME(x)           clock_gettime(CLOCK_REALTIME,&x);
#define MSEC(x)           (x.tv_sec*1000+x.tv_nsec/1000000.0)
#define WALL(a...)        TIME(start);a;TIME(end);wall=(MSEC(end)-MSEC(start))/1000.0;
#define SEED(s)           !s?:srand(time(0));

#define R return
#define O printf
#define N(n,a...){I i=0,_n=(n);while(i<_n){a;++i;}}
#define Nj(n,a...){I j=0,_n=(n);while(j<_n){a;++j;}}

I rnd(I l,I h){R(rand()%(h-l+1))+l;}

I*gen(){
    I*vec = malloc(sizeof(I)*3*ARENA);
    N(ARENA,vec[i++]=rnd(2010,2034);vec[i++]=rnd(1,12);vec[i++]=rnd(1,28);)
    R vec;
}

#define GEN() I*vec=gen();UJ r=0;

#define DONE() O("%llu %f\n",r,wall);R 0;

#ifdef LT

const I LUT[12]={0,31,61,92,122,153,184,214,245,275,306,337};
#define mb(m) LUT[m]

#else

#define mb(m) ((m*306+5)*13107>>17) //courtesy aab
//#define mb(m)  ((153*m+2)*3277>>14)
//#define mb(m)  ((153*m+2)*1639>>13)

#endif

Zin UI ymd(UI y,UI m,UI d){R y-=2001,m=12*y+m+9,m/12*1461/4+mb(m%12)-307+d;}


//:~