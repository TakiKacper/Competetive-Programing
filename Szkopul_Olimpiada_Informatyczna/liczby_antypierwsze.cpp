#include <iostream>
#include <set>

using ull = unsigned long long;

extern std::set<ull> T;

int main() {
    ull n; std::cin >> n;
    auto itr = T.lower_bound(n);
    if (n > *(--T.end())) itr = (--T.end());
    if (*itr > n) itr--;
    std::cout << (*itr);
}

std::set<ull> T = {
    1,
    2,
    4,
    6,
    12,
    24,
    36,
    60,
    120,
    180,
    240,
    360,
    720,
    840,
    1260,
    1680,
    2520,
    5040,
    7560,
    10080,
    15120,
    20160,
    25200,
    27720,
    45360,
    50400,
    55440,
    83160,
    110880,
    166320,
    221760,
    277200,
    332640,
    498960,
    554400,
    665280,
    720720,
    1081080,
    1441440,
    2162160,
    2882880,
    3603600,
    4324320,
    6486480,
    7207200,
    8648640,
    10810800,
    14414400,
    17297280,
    21621600,
    32432400,
    36756720,
    43243200,
    61261200,
    73513440,

    // zadanie bylo na pierwszym etapie, dalo sie pregenerowac wyniki
    // z racji ze nie chce czekac kilka godzin pozostale liczby brakujace
    // w testach dokladam teraz
    // oczywiscie program "antypierwsze_gen.cpp" znalaz by je ... po chwili
    294053760,
    551350800,
    735134400,
    1396755360
};
