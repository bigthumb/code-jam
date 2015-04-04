/* -------------------------------------------------------------------------
//  File Name   :   minesweeper.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-2 20:39:48
//  Description :   https://code.google.com/codejam/contest/2974486/dashboard#s=p2
//  步骤：
//  (1) 比较矩阵的要填充的行row和列col，若row大，则填充一行，否则填充一列，填充方向是从上往下或从左往右，
//      重复该步骤直至要填充的mine不足以填满一行或一列；
//  (2) 左上角向右填充和向下填充，直至填完mine，或者剩余最后2行或2列， 最后判断剩余mine，若为0，则成功，否则失败。
//
// -----------------------------------------------------------------------*/

#include <stdio.h>

//-------------------------------------------------------------------------

static const int num = 52;
static char matrix[num][num];

static const char clean     = '.';
static const char mine      = '*';
static const char click     = 'c';

void fillCorner(int r1, int c1, int r2, int c2, int& m)
{
    for(int i = r1; m > 0 && i <= r2; ++i)
    {
        for(int j = c1; m > 0 && j <= c2; ++j)
        {
            matrix[i][j] = mine;
            --m;
        }
    }
}

bool fill(int R, int C, int M)
{
    // 只有1个单元格没有mine
    if(1 == R * C - M)
    {
        for(int i = 0; i < R; ++i)
        {
            for(int j = 0; j < C; ++j)
            {
                matrix[i][j] = mine;
            }
        }

        matrix[R - 1][C - 1] = click;
        return true;
    }

    if(1 == R || 1 == C)
    {
        for(int i = 0; i < M; ++i)
        {
            matrix[i % R][i / R] = mine;
        }

        for(int j = M; j < R * C; ++j)
        {
            matrix[j % R][j / R] = clean;
        }

        matrix[R - 1][C - 1] = click;
        return true;
    }

    // 全部填充clean
    for(int i = 0; i < R; ++i)
    {
        for(int j = 0; j < C; ++j)
        {
            matrix[i][j] = clean;
        }
    }

    int m = M;
    int r1 = 0;
    int c1 = 0;
    int r2 = R - 1;
    int c2 = C - 1;
    while(m > 0 && (r1 <= r2 - 2 || c1 <= c2 - 2))
    {
        int row = r2 - r1 + 1;
        int col = c2 - c1 + 1;
        if(row > col)
        {
            if(m < col)
            {
                fillCorner(r1, c1, r2 - 2, c2 - 2, m);
                break;
            }
            else
            {
                for(int i = c1; i <= c2; ++i)
                {
                    matrix[r1][i] = mine;
                }

                ++r1;
                m -= col;
            }
        }
        else
        {
            if(m < row)
            {
                fillCorner(r1, c1, r2 - 2, c2 - 2, m);
                break;
            }
            else
            {
                for(int i = r1; i <= r2; ++i)
                {
                    matrix[i][c1] = mine;
                }

                ++c1;
                m -= row;
            }
        }
    }

    if(0 == m)
        matrix[R - 1][C - 1] = click;

    return (0 == m);
}

int main(int argc, const char* argv[])
{
    freopen("C-large-practice.in", "r", stdin);
    freopen("C-large-practice.out", "w", stdout);

    int T = 0;
    scanf("%d", &T);
    for(int i = 1; i <= T; ++i)
    {
        int R, C, M;
        scanf("%d %d %d", &R, &C, &M);

        if(!fill(R, C, M))
            printf("Case #%d:\n%s\n", i, "Impossible");
        else
        {
            printf("Case #%d:\n", i);
            for(int k = 0; k < R; ++k)
            {
                for(int t = 0; t < C; ++t)
                {
                    printf("%c", matrix[k][t]);
                }
                printf("\n");
            }
        }
    }

    return 0;
}

//--------------------------------------------------------------------------
