#include <iostream>
#include <vector>

constexpr unsigned int max_n = 2000001;
unsigned int n, m;
unsigned int seg_length = 0;

unsigned int expc[max_n];
unsigned int curr[max_n];

unsigned int A[max_n];

unsigned int result = 0;

void load() {
    std::cin >> n >> m;

    std::vector<unsigned int> amounts;

    for (unsigned int i = 0; i < m; i++) {
        unsigned int a; std::cin >> a;
        amounts.push_back(a);
        seg_length += a;
    }

    for (unsigned int i = 0; i < m; i++) {
        unsigned int c; std::cin >> c;
        expc[c] = amounts[i];
    }

    for (unsigned int i = 0; i < n; i++) std::cin >> A[i];   
}

void iter() {
    if (n < seg_length) return;

    unsigned int not_matching_colors = m;

    auto change_elem = [&](unsigned int i, int mod) {
        if (i < 0 || i > n) return;

        auto& seg_color_amount = curr[A[i]];

        if (seg_color_amount == expc[A[i]]) {
            not_matching_colors++;
        }

        seg_color_amount += mod;

        if (seg_color_amount == expc[A[i]]) {
            not_matching_colors--;
        }
    };

    for (unsigned int i = 0; i < seg_length; i++) change_elem(i, 1);

    if (not_matching_colors == 0) result++;

    for (unsigned int i = seg_length; i < n; i++) {
        change_elem(i - seg_length, -1);
        change_elem(i, 1);
        if (not_matching_colors == 0) result++;
    }
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    load();
    iter();

    std::cout << result;
}
