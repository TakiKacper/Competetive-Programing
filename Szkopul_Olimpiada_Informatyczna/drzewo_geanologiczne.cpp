#include <iostream>

using hash = long long;

constexpr int tree_base_size = 1 << 20;
constexpr int tree_size      = 2 * tree_base_size;

constexpr hash prime_big   = 1'000'000'007;
constexpr hash prime_small = 31;

std::string s1;
hash hash_tree_s1[tree_size];

std::string s2;
hash hash_tree_s2[tree_size];

int  substr_b[tree_size];
int  substr_e[tree_size];

hash prime_small_power[tree_base_size + 5];

hash hash_litery(char c) {
    return (c - 'a' + 1);
}

hash zlacz_hashe(hash h1, hash h2, hash p_pwr) {
    return (std::min(h1, h2) * p_pwr + std::max(h1, h2)) % prime_big;
}

void aktualizuj_polaczenie(int v, hash* ht) {
    int l = v * 2;
    int r = v * 2 + 1;

    int len_r = substr_e[r] - substr_b[r] + 1;
    hash p_pwr = prime_small_power[len_r];

    hash h1 = ht[l];
    hash h2 = ht[r];

    ht[v] = zlacz_hashe(h1, h2, p_pwr);
}

void aktualizuj_pozycje(int p, char c, std::string* str, hash* ht) {
    str->at(p) = c;
    
    p += tree_base_size;
    ht[p] = hash_litery(c);

    while (p /= 2) aktualizuj_polaczenie(p, ht);
}

void inicjalizuj_drzewa() {
    for (int i = 0; i < s1.size(); i++) {
        int p = i + tree_base_size;
        
        hash_tree_s1[p] = hash_litery(s1[i]);
        hash_tree_s2[p] = hash_litery(s2[i]);

        substr_b[p] = i;
        substr_e[p] = i;
    }

    int beg = tree_base_size;
    int end = tree_base_size * 2;

    while ((beg /= 2) && (end /= 2)) {
        for (int p = beg; p < end; p++) {
            int l = p * 2;
            int r = p * 2 + 1;

            substr_b[p] = substr_b[l];
            substr_e[p] = substr_e[r];

            aktualizuj_polaczenie(p, hash_tree_s1);
            aktualizuj_polaczenie(p, hash_tree_s2);
        }
    }
}

void odpowiedz() {
    bool g = hash_tree_s1[1] == hash_tree_s2[1];
    std::cout << (g ? "TAK\n" : "NIE\n");
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, q; std::cin >> n >> q;
    std::cin >> s1 >> s2;

    prime_small_power[0] = 1;
    for (int i = 1; i <= tree_base_size; i++)
    prime_small_power[i] = (prime_small_power[i - 1] * prime_small) % prime_big;

    inicjalizuj_drzewa();
    odpowiedz();

    while (q--) {
        int s, p; char c;
        std::cin >> s >> p >> c; p--;
        
        if (s == 1) aktualizuj_pozycje(p, c, &s1, hash_tree_s1);
        if (s == 2) aktualizuj_pozycje(p, c, &s2, hash_tree_s2);

        odpowiedz();
    }
}
