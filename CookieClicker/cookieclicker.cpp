/* -------------------------------------------------------------------------
//  File Name   :   cookieclicker.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-2 11:56:50
//  Description :   https://code.google.com/codejam/contest/2974486/dashboard#s=p1
//  设每秒获得的cookie数量为an(n=1,2,3...n)，显然数列的递增公式an=a1+(n-1)F(a1=2)，得an>0,
//  总时间Tn=C/a1+C/a2+...+C/a(n-1)+X/an,故有
//  Tn-T(n-1)=X/an+C/a(n-1)-X/a(n-1)<0(n>=2)    (1)
//  Tn-T(n+1)=X/an-(C/an+X/an(n+1))<=0          (2)
//  式(1)和式(2)分别化简得到
//  n<(X/C-a1/F)+1                              (3)
//  n>=(X/C-a1/F)                               (4)
//  即(X/C-a1/F)=<n<(X/C-a1/F)+1,设k=(X/C-a1/F)，替换得k=<n<k+1，看出n取k的上整，
//  由于n>=2，故要求k>1，否则n=1满足要求，也就是不需要购买任何farm
// 
// -----------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>

//-------------------------------------------------------------------------

static const double a1 = 2.0;

inline double calMinTime()
{
    double C, F, X;
    scanf("%lf %lf %lf", &C, &F, &X);

    double k = X / C - a1 / F;
    int n = 1;
    if(k > 1.0)
        n = static_cast<int>(ceil(k));

    double Tn = 0.0;
    double ai = a1;
    for(int i = 1; i <= n; ++i)
    {
        if(i == n)
            Tn += X / ai;
        else
            Tn += C / ai;
        ai += F;
    }

    return Tn;
}

int main(int argc, const char* argv[])
{
    freopen("B-large-practice.in", "r", stdin);
    freopen("B-large-practice.out", "w", stdout);

    int T = 0;
    scanf("%d", &T);
    for(int i = 1; i <= T; ++i)
    {
        double ret = calMinTime();
        printf("Case #%d: %0.7f\n", i, ret);
    }

    return 0;
}

//--------------------------------------------------------------------------
