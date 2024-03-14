#include<stdio.h>
typedef int I;typedef short H;typedef unsigned short UH;
#define R return
#define O printf
#define W(b...)     while((b))
#define N(n,a...)   {I i=0,_n=(n);W(i<_n){a;++i;}}
#define Nj(n,a...)   {I j=0,_n=(n);W(j<_n){a;++j;}}
#define Nk(n,a...)   {I k=0,_n=(n);W(k<_n){a;++k;}}
#define _ __attribute__ ((noinline))
#define ZI static I


ZI mB[]={0,31,61,92,122,153,184,214,245,275,306,337};      //!< lut
ZI _ mbl(I m){R mB[m];}                                    //!< lookup
ZI _ mba(I m){R(306*m+5)*13107>>17;}                       //!< aab
ZI _ mbK(I m){R(153*m+2)*1639>>13;}                        //!< kelas#1
ZI _ mbd(I m){R(((UH)((m*3914)+83))>>7);}                  //!< dzaima
ZI _ mbk(I m){R(((m*979)+15)>>5);}                         //!< kelas#2

#define T(f) N(12,O("%d ",f(i)))O("\n");

I main(){
 T(mbl)
 T(mba)
 T(mbK)
 T(mbd)
 T(mbk)
}
