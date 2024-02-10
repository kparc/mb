//!fast month boundary \copyright (c) 2020-2024 the regents of kparc \license mit
#include<time.h>
#include<stdio.h> 
#include<stdlib.h> 

typedef double F;typedef int I; typedef unsigned int UI;typedef unsigned long long UJ;

#define R return
#define O printf
#define W while
#define N(n,a...){UI i=0,_n=(n);W(i<_n){a;++i;}}
#define Nj(n,a...){UI j=0,_n=(n);W(j<_n){a;++j;}}

#define BENCH()           F wall=0;struct timespec start,end;
#define TIME(x)           clock_gettime(CLOCK_REALTIME,&x);
#define MSEC(x)           (x.tv_sec*1000+x.tv_nsec/1000000.0)
#define WALL(a...)        TIME(start);a;TIME(end);wall=(MSEC(end)-MSEC(start))/1000.0;
#define SEED(s)           !s?:srand(time(0));

static I rnd(I l,I h){R(rand()%(h-l+1))+l;}

#ifdef LUT
#define TAG "lut"
const I lut[12]={0,31,61,92,122,153,184,214,245,275,306,337};
#define mb(m) lut[m]
#else
#define TAG "kpc"
//#define mb(m) ((m*306+5)*13107>>17) //!< courtesy aab
#define mb(m)    ((m*153+2)*1639>>13) //!< regents of kparc
#endif

#define Zin __attribute__((always_inline)) inline

//:~
