#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    uint n; std::cin >> n;

    std::vector<uint> S; S.resize(n);
    for (int i = 0; i < n; i++) std::cin >> S[i];

    std::sort(S.begin(), S.end());

    if (S.size() == 1) {
        std::cout << S[0];
        return 0;
    }

    uint sum = 0;
    uint pre = 0; // wartosc premii

    int b = 0;
    int e = S.size() - 1;

    while (b < e) {
        int lesser = S[b];
        int bigger = S[e];

        sum += lesser + bigger;
        pre += (bigger - lesser);

        b++;
        e--;
    }

    if (b == e) sum += S[b];
    std::cout << (sum + pre);
}
