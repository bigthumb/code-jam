/* -------------------------------------------------------------------------
//  File Name   :   sevensegment.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-8 10:37:00
//  Description :   https://code.google.com/codejam/contest/3214486/dashboard
//
// -----------------------------------------------------------------------*/

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <vector>
#include <bitset>

//-------------------------------------------------------------------------

static const uint8_t invalid    = 0xFF;

static uint8_t table[256];      // map between digital and segment-number

static uint8_t states[100];  // 1 ≤ N ≤ 100

// i [6,0]<=>[A,B,..,G]
void subset(uint8_t d, int i, std::vector<uint8_t>& sv)
{
    for(; i >= 0 && 0 == (d & (1 << i)); --i)
        ;

    if(i < 0)
        sv.push_back(d);
    else
    {
        subset(d, i - 1, sv);
        subset(d & (~(1 << i) & 0x7F), i - 1, sv);  // i位置为0
    }
}

uint8_t nextState(int N)
{
    uint8_t p = 0;
    for(int i = 0; i < N; ++i)
    {
        p |= states[i];
    }

    // 用1表示待确认的坏边
    p = (~p & 0x7F);

    std::vector<uint8_t> pv;
    subset(p, 6, pv);

    int count = 0;
    uint8_t rs = 0;
    uint8_t rl = invalid;

    int u = 0;
    size_t v = 0;
    uint8_t s = 0;
    uint8_t prev = invalid;
    while(v < pv.size())
    {
        if(0 == u)
        {
            s = 0;
            prev = invalid;
            for(; v < pv.size(); ++v)
            {
                prev = table[states[u] | pv[v]];
                if(invalid != prev)
                {
                    s = pv[v];
                    ++u;

                    break;
                }
            }
        }
        else
        {
            uint8_t next = invalid;
            for(int k = 0; k < pv.size(); ++k)
            {
                next = table[states[u] | pv[k]];
                if(invalid != next && (prev - 1 + 10) % 10 == next)
                {
                    s |= pv[k];
                    break;
                }
                else
                {
                    next = invalid;
                }
            }

            if(invalid != next)
            {
                ++u;
                prev = next;
            }
            else
            {
                ++v;
                u = 0;
            }
        }

        if(u == N && invalid != prev)
        {
            if(0 == count)
            {
                rs = s;
                rl = prev;
            }

            u = 0;
            ++v;
            ++count;
        }
    }

    if(1 == count)
    {
        return (table[(rl - 1 + 10 ) % 10] & ~rs);
    }
    else
    {
        return invalid;
    }
}


int main(int argc, const char* argv[])
{
    ::freopen("A-small-practice.in", "r", stdin);
    ::freopen("A-small-practice.out", "w", stdout);

    ::memset(table, invalid, sizeof(table));

    // 因为不重叠数字和段码之间的映射，可用一个数组表示
    //                             ABC DEFG
    table[0x7E] = 0;            // 111 1110
    table[0x30] = 1;            // 011 0000
    table[0x6D] = 2;            // 110 1101
    table[0x79] = 3;            // 111 1001
    table[0x33] = 4;            // 011 0011
    table[0x5B] = 5;            // 101 1011
    table[0x5F] = 6;            // 101 1111
    table[0x70] = 7;            // 111 0000
    table[0x7F] = 8;            // 111 1111
    table[0x7B] = 9;            // 111 1011
    table[0]    = 0x7E;
    table[1]    = 0x30;
    table[2]    = 0x6D;
    table[3]    = 0x79;
    table[4]    = 0x33;
    table[5]    = 0x5B;
    table[6]    = 0x5F;
    table[7]    = 0x70;
    table[8]    = 0xFF;
    table[9]    = 0x7E;

    char str[32] = {0};

    int T = 0;
    scanf("%d", &T);
    for(int i = 1; i <= T; ++i)
    {
        int N = 1;
        scanf("%d", &N);

        for(int j = 0; j < N; ++j)
        {
            ::scanf("%s", str);
            unsigned long t = std::bitset<7>(str).to_ulong();
            states[j] = static_cast<uint8_t>(t);
        }

        uint8_t n = nextState(N);
        if(invalid == n)
            ::printf("Case #%d: ERROR!\n", i);
        else
        {
            std::string str = std::bitset<7>(n).to_string();
            ::printf("Case #%d: %s\n", i, str.c_str());
        }
    }

    return 0;
}


//--------------------------------------------------------------------------
