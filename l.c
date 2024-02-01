#include<stdio.h>
#include"c.h"

int LUT[12]={0,31,61,92,122,153,184,214,245,275,306,337};
int main(){
    SEED; 
    I r=0;
    BENCH();
    WALL(
        Nj(ROUNDS,
            r+=LUT[pick()]
        )
    )
    O("%llu %f\n",r,wall);
}
//:~
