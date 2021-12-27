#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/**
 *  a[0] = S (modulo 2^31)
 *  for i = 1 to N-1
 *  a[i] = a[i-1]*P+Q (modulo 2^31) 
 * 
 */

int main()
{
    uint32_t counter = 0;
    uint32_t N, S, P, Q;
    long long a = 0, old;
    int max = (1<<31);

    std::cin >> N >> S >> P >> Q;
    counter = N;
    a = S;

    for (uint32_t i = 1; i < N; i++)
    {
        a = a * P + Q;
        a = a % max;
        if(a == old)
        {
            counter = i;
            break;
        }
        old =  a;
    }
    cout << counter;
    return 0;
}