/*
USER: dionyzi1
TASK: sprime
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

typedef unsigned long long int lli;

const int K = 20;

lli powmod(lli base, lli exponent, lli mod) {
    lli ret = 1;

    while (exponent) {
        if (exponent & 1) {
            ret *= base;
            ret %= mod;
        }
        base *= base;
        base %= mod;
        exponent >>= 1;
    }

    return ret;
}

bool miller_rabin(lli n) {
    if (n % 2 == 0) {
        return false;
    }
    if (n == 3) {
        return true;
    }
    lli m = n - 1;
    lli s = 0;

    while ((m & 1) == 0) {
        ++s;
        m >>= 1;
    }

    srand(time(NULL));
    for (int i = 0; i < K; ++i) {
        lli a = (rand() % (n - 4)) + 2;
        lli x = powmod(a, m, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool prime = false;
        for (lli j = 0; j < s - 1; ++j) {
            x = (x * x) % n;
            if (x == 1) {
                return false;
            }
            if (x == n - 1) {
                prime = true;
                break;
            }
        }
        if (prime) {
            continue;
        }
        return false;
    }
    return true;
}

int main() {
    const lli primes[] = {2, 3, 5, 7};
    vector< set< int > > sprimes;
    FILE* in = fopen("sprime.in", "r"),
        * out = fopen("sprime.out", "w");
    int N = 2;

    sprimes.push_back(set< int >());
    for (int i = 0; i < 4; ++i) {
        sprimes[0].insert(primes[i]);
    }
    fscanf(in, "%i", &N);
    for (int i = 1; i < N; ++i) {
        sprimes.push_back(set< int >());
        for (set< int >::iterator it = sprimes[i - 1].begin(); it != sprimes[i - 1].end(); ++it) {
            for (int j = 1; j <= 9; j += 2) {
                int candidate = *it * 10 + j;
                if (miller_rabin(candidate)) {
                    sprimes[i].insert(candidate);
                }
            }
        }
    }
    for (set< int >::iterator it = sprimes[N - 1].begin(); it != sprimes[N - 1].end(); ++it) {
        fprintf(out, "%i\n", *it);
    }

    return 0;
}
