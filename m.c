//!fast month boundary \copyright (c) 2020-2024 the regents of kparc \license mit
#include"c.h"

#define ARENA  1024*1024*128
#define ROUNDS 512

//!generate a bunch of random gregorian triplets e.g. (2001,1,1)
I*gen(){UJ n=sizeof(I)*3*ARENA;I*v=malloc(n);
 O("arena %llu mb, %d rounds:\n",n/1048576, ROUNDS);
 N(ARENA,v[i]=rnd(2001,2100);v[i+1]=rnd(1,12);v[i+2]=rnd(1,27);i+=3)R v;}

//!convert gregorian triplet to epoch time
Zin I ymd(I y,I m,I d){R y-=2001,m=12*y+m+9,m/12*1461/4+mb(m%12)-307+d;}

I main(){
    SEED(0)BENCH()
    O("\nmonth boundary benchmark (%s):\n\n", TAG);
    UJ r=0;I*v=gen();

    //N(12,O("%d ",mb(i)))O("\n");

    //!smoke test
    N(3*3,O("%d-%d-%d %d %d\n",v[i],v[i+1],v[i+2],mb(v[i+1]),ymd(v[i],v[i+1],v[i+2]));i+=3)O("...\n");

    WALL(
        Nj(ROUNDS,
            N(ARENA,r+=ymd(v[i],v[i+1],v[i+2]);i+=3)))

    O("checksum: %llu wall time: %fs\n",r,wall);
    R free(v),0;
}
    
//:~
