#include <iostream>
#include <vector>
#include <unordered_set>

constexpr int max_n = 200'000;
int n;

constexpr int layers = 18;
using hash_t = unsigned long long;

// wartosc hashu dla danej dlugosci (1, 2, 4, ...)
// i dla kazdej pozycji, zdefiniowane tak daleko jak sie da (niewykraczajac za zakres)
// H_LR - hash od lewej  do prawej
// H_RL - hash do prawej do lewej
hash_t H_LR[layers][max_n];
hash_t H_RL[layers][max_n];

hash_t merge_with_order(hash_t h1, hash_t h2) {
    h2 *= 200'003; return (h1 + h2);
}

// inclusive, inclusive
hash_t hash_on_fragment(int layer, int layer_length, int beg, int end) {
    int l_beg = beg;
    int r_beg = std::max(0, end - layer_length + 1);

    hash_t lr_left  = H_LR[layer][l_beg];
    hash_t lr_right = H_LR[layer][r_beg];
    hash_t lr_hash  = merge_with_order(lr_left, lr_right);

    hash_t rl_left  = H_RL[layer][l_beg];
    hash_t rl_right = H_RL[layer][r_beg];
    hash_t rl_hash  = merge_with_order(rl_right, rl_left);

    return std::min(lr_hash, rl_hash);
}

int main() {
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> H_LR[0][i];
        H_RL[0][i] = H_LR[0][i];
    }

    int layer_length = 2;
    for (int l = 1; l < layers; l++) {
        int itr = 0;

        while (itr + layer_length <= n) {
            int l_beg = itr;
            int r_beg = itr + layer_length / 2;

            // Zlacz hashe, od lewej do prawej
            {
                auto left_hash  = H_LR[l - 1][l_beg];
                auto right_hash = H_LR[l - 1][r_beg];  
                H_LR[l][itr] = merge_with_order(left_hash, right_hash);
            }

            // Zlacz hashe od prawej do lewej
            {
                auto left_hash  = H_RL[l - 1][l_beg];
                auto right_hash = H_RL[l - 1][r_beg];  
                H_RL[l][itr] = merge_with_order(right_hash, left_hash);
            }

            itr++;
        }

        layer_length *= 2;
    }
    
    int              best_fragments = 0;
    std::vector<int> best_k;

    int layer    = 0;
    layer_length = 1;

    std::unordered_set<hash_t> unique_fragments;

    for (int k = 1; k <= n; k++) {
        unique_fragments.clear();

        if (k >= layer_length * 2) {
            layer_length *= 2;
            layer++;
        }

        int itr = 0;
        while (itr + k <= n) {
            auto frag_hash = hash_on_fragment(
                layer, 
                layer_length,
                itr, 
                itr + k - 1
            );

            unique_fragments.insert(frag_hash);
            itr += k;
        }

        if (unique_fragments.size() == best_fragments) {
            best_k.push_back(k);
        }
        else if (unique_fragments.size() > best_fragments) {
            best_fragments = unique_fragments.size();

            best_k.clear();
            best_k.push_back(k);
        }
    }

    std::cout << best_fragments << ' ' << best_k.size() << '\n';
    for (int k : best_k) std::cout << k << ' ';
}
