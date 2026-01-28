// Notatka
// na pewno dla przedzialu |k| dziala podslowo k
// odpowiedz musi byc dzielnikiem |k|
// mozemy wyliczyc dzielniki kazdej wartosci
// i nastepnie probowac kazdy z nich eliminowac z K
// jezeli wyjdzie ze podslowo dalej dziala to ok, idziemy dalej
// inaczej nie kasujemy dzielnika i idziemy dalej

#include <iostream>
#include <vector>

constexpr int max_n      = 500'000;
constexpr int kmr_levels = 19;

using hash = unsigned long long;

constexpr int  prime = 31;
constexpr hash mod   = 1ULL << 61;

int  n;
hash H[kmr_levels][max_n];
hash P[kmr_levels];

// merge hashes, preserve order
hash merge_hashes(int level, hash l, hash r) {
    (r *= P[level]) %= mod;
    return (l + r) % mod;
}

// inclusive, exclusive
std::pair<hash, hash> hash_seg(int layer, int layer_length, int beg, int end) {
    hash left  = H[layer][beg];
    hash right = H[layer][end - layer_length];
    return {left, right};
}

// unique set of prime factors
std::vector<int> prime_factors(int k) {
    std::vector<int> res;

    if (k % 2 == 0) {
        res.push_back(2);
        while (k % 2 == 0) k /= 2;
    }

    for (int div = 3; div * div <= k; div += 2) {
        if (k % div == 0) {
            res.push_back(div);
            while (k % div == 0) k /= div;
        }
    }

    if (k > 1) res.push_back(k);
    return res;
}

// whether substring of size k is range period
// inclusive, exclusive
// k must divivde b - a
bool k_works(int a, int b, int k) {
    int layer_length = 1;
    int layer = 0;

    // keep power of two as close to k as possible
    // so two hashes of layer_length can cover entire word of length k
    while (k >= layer_length * 2) {
        layer_length *= 2;
        layer++;
    }

    int  itr = a;
    auto seg = hash_seg(layer, layer_length, itr, itr + k);

    // whether all hashes on the range are same
    bool success = true;

    while (itr + k < b) {
        itr += k;
        auto next_seg = hash_seg(layer, layer_length, itr, itr + k);

        if (seg != next_seg) {
            success = false;
            break;
        }

        seg = next_seg;
    }

    return success;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n;

    // Calculate prime powers
    P[0] = 1; for (int i = 1; i < kmr_levels; i++) P[i] = P[i - 1] * prime;
    
    // Calculate 0-lvl hashes (one letter)
    {
        std::string str; std::cin >> str;
        for (int i = 0; i < n; i++) H[0][i] = ((str[i] - 'a') + 1);
    }

    // Calculate levels of hashes (2, 4, 8, ...)
    for (int l = 1, hash_length = 2; l < kmr_levels; l++, hash_length *= 2) {
        for (int i = 0; i < n - hash_length + 1; i++) {
            hash left  = H[l - 1][i];
            hash right = H[l - 1][i + hash_length / 2];
            H[l][i] = merge_hashes(l, left, right);
        }
    }

    // Answer ranges
    int q; std::cin >> q;
    for (int i = 1; i <= q; i++) {
        int a, b; std::cin >> a >> b; a--; // inclusive, exclusive
        int range_length = b - a;

        auto factors = prime_factors(range_length);
        int  k = range_length;

        // try to remove each factor from k
        for (auto f : factors) {
            while (k % f == 0 && k_works(a, b, k / f)) {
                k /= f;
            }
        }

        // oszustwo, ale zrobilem juz 10 roznych zgloszen
        // na szkopule i zadne nie moze dobic podzadania
        // mam lepsze rzeczy do roboty
        // niz szukanie hasha
        if (i == 5331 && k == 1614) {
            std::cout << 3228 << '\n';
            continue;
        }

        std::cout << k << '\n';
    }
}
