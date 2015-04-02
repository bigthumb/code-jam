/* -------------------------------------------------------------------------
//  File Name   :   cookieclicker.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-2 11:56:50
//  Description :   https://code.google.com/codejam/contest/2974486/dashboard#s=p1
//  ��ÿ���õ�cookie����Ϊan(n=1,2,3...n)����Ȼ���еĵ�����ʽan=a1+(n-1)F(a1=2)����an>0,
//  ��ʱ��Tn=C/a1+C/a2+...+C/a(n-1)+X/an,����
//  Tn-T(n-1)=X/an+C/a(n-1)-X/a(n-1)<0(n>=2)    (1)
//  Tn-T(n+1)=X/an-(C/an+X/an(n+1))<=0          (2)
//  ʽ(1)��ʽ(2)�ֱ𻯼�õ�
//  n<(X/C-a1/F)+1                              (3)
//  n>=(X/C-a1/F)                               (4)
//  ��(X/C-a1/F)=<n<(X/C-a1/F)+1,��k=(X/C-a1/F)���滻��k=<n<k+1������nȡk��������
//  ����n>=2����Ҫ��k>1������n=1����Ҫ��Ҳ���ǲ���Ҫ�����κ�farm
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
