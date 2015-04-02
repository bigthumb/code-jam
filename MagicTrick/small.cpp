/* -------------------------------------------------------------------------
//  File Name   :   magictrick.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-1 22:35:35
//  Description :  
//
// -----------------------------------------------------------------------*/

#include <cstdio>

//-------------------------------------------------------------------------

// Multiple cards
#define MUL     (-1)
// Without corrective cards
#define NONE    (0)

// The card's value is the array's index, an element's value is the row
int rowmap[16] = {0};

int findcard()
{
    int answer1 = 0;
    scanf("%d", &answer1);

    for(int i = 0; i < 16; ++i)
    {
        int t = -1;
        scanf("%d", &t);
        rowmap[t - 1] = i / 4 + 1;
    }

    int answer2 = 0;
    scanf("%d", &answer2);

    int res = NONE;
    for(int i = 0; i < 16; ++i)
    {
        int t = -1;
        scanf("%d", &t);
        // Check how many card's value in the selected row for first question,
        // which are in the selected row for second question too
        if(i / 4 + 1 == answer2 && rowmap[t - 1] == answer1)
        {
            if(NONE == res)
                res = t;
            else
                res = MUL;
        }
    }

    return res;
}

int main(int argc, const char* argv[])
{
    freopen("A-small-practice.in", "r", stdin);
    freopen("A-small-practice.out", "w", stdout);

    int T = 0;
    scanf("%d", &T);
    for(int i = 1; i <= T; ++i)
    {
        int res = findcard();
        if(MUL == res)
            printf("Case #%d: %s\n", i, "Bad magician!");
        else if(NONE == res)
            printf("Case #%d: %s\n", i, "Volunteer cheated!");
        else
            printf("Case #%d: %d\n", i, res);
    }

    return 0;
}

//--------------------------------------------------------------------------
