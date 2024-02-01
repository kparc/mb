#include<stdio.h>
#include"c.h"

int main(){
    SEED;
    I r=0;
    BENCH();
    WALL(
        Nj(ROUNDS,
            //r+=(153*pick()+2)*3277>>14
            r+=(153*pick()+2)*1639>>13;
            BUSYWORK();
        )
    )
    O("%u %f %u\n",r,wall,n);
}
//:~
