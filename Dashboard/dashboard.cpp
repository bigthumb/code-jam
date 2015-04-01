/* -------------------------------------------------------------------------
//  File Name   :   Dashboard.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-1 20:34:49
//  Description :   https://code.google.com/codejam/contest/dashboard?c=2974486
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

int dashboard()
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
    int T = 0;
    scanf("%d", &T);
    for(int i = 0; i < T; ++i)
    {
        int res = dashboard();
        if(MUL == res)
            printf("Case #%d: %s\n", i + 1, "Bad magician!");
        else if(NONE == res)
            printf("Case #%d: %s\n", i + 1, "Volunteer cheated!");
        else
            printf("Case #%d: %d\n", i + 1, res);
    }
    
    return 0;
}


//--------------------------------------------------------------------------
