/* -------------------------------------------------------------------------
//  File Name   :   minesweeper.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-2 20:39:48
//  Description :   https://code.google.com/codejam/contest/2974486/dashboard#s=p2
//  步骤：
//  (1) 比较当前矩阵的行row和列col，若row大，则填充一行，否则填充一列，重复该步骤直至要填充的mine不足以
//      填满一行或一列；
//  (2) 先同时从左上角向右填充和右下角向左填充，直至填完mine或和填充方向的列边界间隔3个单元（cell），接着
//      同时从左上角向下填充和右下角向上填充，直至填完mine或和填充方向的行边界间隔3个单元（cell），最后判断
//      剩余mine，若为0，则成功，否则失败。
//
// -----------------------------------------------------------------------*/

#include <stdio.h>

//-------------------------------------------------------------------------

static const int num = 52;
static char matrix[num][num];

static int midRow = 0;
static int midCol = 0;

static const char clean     = '.';
static const char mine      = '*';
static const char click     = 'c';

bool fillCorner(int r1, int c1, int r2, int c2, int m)
{
    int i = 0;
    while(m > 0)
    {
        if(c2 - (c1 + i) >= 3)
        {
            matrix[r1][c1 + i] = mine;
            --m;
            if(m > 0)
            {
                matrix[r2][c2 - i] = mine;
                --m;
            }
            ++i;
        }
        else
        {
            break;
        }
    }

    int j = 1;
    while(m > 0)
    {
        if(r2 - (r1 + j) >= 3)
        {
            matrix[r1 + j][c1] = mine;
            --m;
            if(m > 0)
            {
                matrix[r2 - j][c2] = mine;
                --m;
            }
            ++j;
        }
        else
        {
            break;
        }
    }

    return (0 == m);
}

inline bool isClean(int r, int c)
{
    return (
        (clean == matrix[r][c]) && (clean == matrix[r][c - 1]) && (clean == matrix[r][c + 1]) && 
        (clean == matrix[r - 1][c - 1]) && (clean == matrix[r - 1][c]) && (clean == matrix[r - 1][c + 1]) && 
        (clean == matrix[r + 1][c - 1]) && (clean == matrix[r + 1][c]) && (clean == matrix[r + 1][c + 1])
    );
}

bool markClick(int r1, int c1, int r2, int c2)
{
    for(int i = r2; i >= r1; --i)
    {
        for(int j = c1; j <= c2; ++j)
        {
            if(isClean(i, j))
            {
                matrix[i][j] = click;
                return true;
            }
        }
    }

    return false;
}

bool fill(int r1, int c1, int r2, int c2, int m)
{
    int row = r2 - r1 + 1;
    int col = c2 - c1 + 1;
    if(row > col)
    {
        if(m >= col)
        {
            int r = (midRow - r1 > r2 - midRow ? r1++ : r2--);
            for(int i = c1; i <= c2; ++i)
            {
                matrix[r][i] = mine;
            }

            return fill(r1, c1, r2, c2, m - col);
        }
        else
        {
            if(fillCorner(r1, c1, r2, c2, m))
                return markClick(r1, c1, r2, c2);
            else
                return false;
        }
    }
    else
    {
        if(m >= row)
        {
            int c = (midCol - c1 > c2 - midCol ? c1++ : c2--);
            for(int i = r1; i <= r2; ++i)
            {
                matrix[i][c] = mine;
            }

            return fill(r1, c1, r2, c2, m - row);
        }
        else
        {
            if(fillCorner(r1, c1, r2, c2, m))
                return markClick(r1, c1, r2, c2);
            else
                return false;
        }
    }
}

int main(int argc, const char* argv[])
{
    freopen("C-small-practice.in", "r", stdin);
    freopen("C-small-practice.out", "w", stdout);

    int T = 0;
    scanf("%d", &T);
    for(int i = 1; i <= T; ++i)
    {
        int R, C, M;
        scanf("%d %d %d", &R, &C, &M);

        for(int k = 0; k <= R + 1; ++k)
        {
            for(int t = 0; t <= C + 1; ++t)
            {
                matrix[k][t] = clean;
            }
        }

        midRow = (1 + R) / 2;
        midCol = (1 + C) / 2;

        if(!fill(1, 1, R, C, M))
            printf("Case #%d:\n%s\n", i, "Impossible");
        else
        {
            printf("Case #%d:\n", i);
            for(int k = 1; k <= R; ++k)
            {
                for(int t = 1; t <= C; ++t)
                {
                    printf("%c ", matrix[k][t]);
                }
                printf("\n");
            }
        }
    }

    return 0;
}

//--------------------------------------------------------------------------
