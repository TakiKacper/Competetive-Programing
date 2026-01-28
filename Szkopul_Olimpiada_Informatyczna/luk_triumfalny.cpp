#include <iostream>
#include <vector>

bool             vis[300000];
std::vector<int> adj[300000];

int sprawdz(int v, int k, int p) {
    int sum = 0;
    for (auto& u : adj[v]) {
        if (u == p) continue;
        sum += sprawdz(u, k, v) + 1;
    }
    return std::max(0, sum - k);
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    int n; std::cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        adj[x0].push_back(x1);
        adj[x1].push_back(x0);
    }

    int lower_k = 1;
    int upper_k = n - 1;

    while (lower_k < upper_k) {
        int k = (lower_k + upper_k) / 2;
        int r = sprawdz(0, k, 0);

        // to k dziala, mozemy probowac mniej
        if (r == 0) {
            if (k == upper_k) upper_k--;
            else upper_k = k;
        }
        // to k nie dziala, musimy probowac wiecej
        else {
            if (k == lower_k) lower_k++;
            else lower_k = k;
        }
    }

    std::cout << upper_k;
}
