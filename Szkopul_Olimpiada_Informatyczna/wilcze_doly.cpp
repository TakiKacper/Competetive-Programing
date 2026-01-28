#include <iostream>
#include <set>

// Config
constexpr int max_n = 2'000'000;
using ull = unsigned long long;

// Data
ull n, p, d;
ull w[max_n];

// Precomuted
ull wd[max_n]; // suma na przedziale [i - d, i]

// State
int ans = 0;

int front = -1;
int begin = 0;

ull bf_sum = 0; // suma [begin - front]

// zakryte pola, ostatnie pole dechy
std::set<std::pair<ull, int>> opcje_dechy;

bool front_end() {
    return front + 1 == n;
}

void push_front_no_plank() {
    front++;
    bf_sum += w[front];
}

void push_front() {
    front++;

    bf_sum += w[front];
    opcje_dechy.insert({wd[front], front});
}

bool invalid() {
    ull sum;

    if (opcje_dechy.size() == 0) sum = bf_sum;
    else                         sum = (bf_sum - (--opcje_dechy.end())->first);

    return sum > p;
}

void pop_back() {
    // kasujemy opcje dechy ktora nasuwa sie na to pole
    auto itr = opcje_dechy.find({wd[begin + d - 1], begin + d - 1});
    if (itr != opcje_dechy.end()) opcje_dechy.erase(itr);

    bf_sum -= w[begin];
    begin++;
}

// Main Algo
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> n >> p >> d;

    ull sum = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> w[i]; sum += w[i];
        if (i >= d) sum -= w[i - d];
        wd[i] = sum;
    }

    for (int i = 0; i < d - 1; i++) push_front_no_plank();
    push_front();
    ans = std::max(ans, front - begin + 1);

    while (!front_end()) {
        push_front();
        while (invalid()) pop_back();
        ans = std::max(ans, front - begin + 1);
    }

    std::cout << ans;
}
