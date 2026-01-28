#include <iostream>

using ull = unsigned long long;

int n;
ull t[1000000];

void solve(int k) {
    int pos = 0; // max move -> pos + k
    int tireness = 0;

    while (true) {
        ull c_height = t[pos];

        if (pos + k >= n - 1) {
            if (t[n - 1] >= c_height) tireness++;
            break;
        }

        int highest_lower_pos = pos;
        ull highest_lower     = 0;

        int highest_upper_pos = pos;
        ull highest_upper     = 0;

        for (int npos = pos + 1; npos <= pos + k; npos++) {
            if (t[npos] < c_height) { // lower
                if (t[npos] >= highest_lower) {
                    highest_lower_pos = npos;
                    highest_lower     = t[npos];
                }
            }
            else { // higher or equal 
                if (t[npos] >= highest_upper) {
                    highest_upper_pos = npos;
                    highest_upper     = t[npos];
                }
            }
        }

        if (highest_lower != 0) {
            pos = highest_lower_pos;
        }
        else {
            pos = highest_upper_pos;
            tireness++;
        }
    }

    std::cout << tireness << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> t[i];
    }

    int q; std::cin >> q;
    for (int i = 0; i < q; i++) {
        int k; std::cin >> k;
        solve(k);
    }
}
