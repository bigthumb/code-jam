/* -------------------------------------------------------------------------
//  File Name   :   minesweeper.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-2 20:39:48
//  Description :   https://code.google.com/codejam/contest/2974486/dashboard#s=p2
//  ��ʣ��δ������Ϊrow����Ϊcol�����mine�Ĳ��裺
//  (1) ����max(row, col)>2����row>col�������һ�У�row��1�����������һ�У�col��1�����ظ��ò���
//      ֱ��ʣ���mine����������һ�л�һ�У�
//  (2) Ԥ���Ҳ�2�к��²�2�в���䣬�������Һʹ����������ʣ��ĵ�Ԫ��
//  (3) �ж�ʣ��mine����Ϊ0����ɹ�������ʧ�ܡ�
//
// -----------------------------------------------------------------------*/

#include <stdio.h>

//-------------------------------------------------------------------------

static const int num = 52;
static char matrix[num][num];

static const char clean     = '.';
static const char mine      = '*';
static const char click     = 'c';

bool fillMine(int R, int C, int M)
{
    // ����1����Ԫ����mine
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

    // ����2����Ԫ����mine����������2�к�2�У���ȫ�����clean
    for(int i = 0; i < R; ++i)
    {
        for(int j = 0; j < C; ++j)
        {
            matrix[i][j] = clean;
        }
    }

    int m = M;
    int r = 0;
    int c = 0;
    while(m > 0)
    {
        int row = R - r;
        int col = C - c;
        if(row <= 2 && col <= 2)
            break;

        if(row > col)
        {
            if(m < col)
                break;
            else
            {
                for(int i = c; i < C; ++i)
                {
                    matrix[r][i] = mine;
                }

                ++r;
                m -= col;
            }
        }
        else
        {
            if(m < row)
                break;
            else
            {
                for(int i = r; i < R; ++i)
                {
                    matrix[i][c] = mine;
                }

                ++c;
                m -= row;
            }
        }
    }

    for(int i = r; m > 0 && i < R - 2; ++i)
    {
        for(int j = c; m > 0 && j < C - 2; ++j)
        {
            matrix[i][j] = mine;
            --m;
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

        if(!fillMine(R, C, M))
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
