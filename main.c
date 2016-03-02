#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LAMBDA 1.0523
#define ECHANT 890
#define KEYLENGTH 32

void logistic_bmap_chaos(float* x, float* y);
void conversion_fltob ( int* tab, float x, float y );

int main()
{
    int keygen[3][2]={{0,0},{0,0},{0,0}};
    int key[KEYLENGTH];
    float x,y;
    x=0.321;
    y=0.823;
    int i;
    int j;
    j = 0;
    float* xptr;
    float* yptr;

    xptr = &x;
    yptr = &y;

    for (i=1;i<KEYLENGTH*ECHANT+1;i++)
    {
        keygen[0][1]=keygen[1][1];
        keygen[1][1]=keygen[2][1];
        logistic_bmap_chaos(xptr,yptr);
        conversion_fltob(keygen[2],x,y);
        if ((i%ECHANT)== 0)
        {
            if (keygen[0][1])
            {
                if (keygen[1][1]) key[j] = (keygen[2][1]+1)%2;
                else key[j] = keygen[2][1];
            }else{
            if (keygen[1][1]) key[j] = (keygen[2][0]+1)%2;
            else key[j] = keygen[2][0];
            }


        j++;
        }
    }

    for (i=0; i<KEYLENGTH; i++ )
    {
        printf("%d\n",key[i]);
    }

    return 0;
}


void logistic_bmap_chaos(float* x, float* y)
{
    float xtmp;
    float ytmp;
    xtmp = LAMBDA*(3*(*y)+1)*(*x)*(1-(*x));
    ytmp = LAMBDA*(3*(*x)+1)*(*y)*(1-(*y));

    *x = xtmp;
    *y = ytmp;

}

void conversion_fltob ( int* tab, float x, float y )
{
    float p4 = (1+sqrtf(4-3/LAMBDA))/3;
    *tab = !( x > y );
    *(tab+1) = ((y < x)& (y <(-x+2*p4)))|((!(x>y))&(!(y<(-x+2*p4))));
}


