#include <iostream>

std::string str;
std::pair<int, int> solution[(int)2e6 + 1];

void gen_from_sum(int sum, int beg, int end) {
    while (sum > 0) {
        solution[sum] = {beg + 1, end + 1};

        if (str[beg] == 'T')      beg++;
        else if (str[end] == 'T') end--;
        else { // two 'W'
            beg++;
            end--;
        }
        sum -= 2;
    }
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    int n, m; std::cin >> n >> m;
    std::cin >> str;

    int krw_pos = 0; // najbardziej krancowe w
    int krw_dst = __INT_MAX__;

    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += (str[i] == 'T' ? 2 : 1);
        
        if (str[i] == 'W') {
            int dst_lewo  = i - 0;
            int dst_prawo = n - i - 1;
            int dst = std::min(dst_lewo, dst_prawo);

            if (dst < krw_dst) {
                krw_pos = i;
                krw_dst = dst;
            }
        }
    }

    // suma innej parzystosci istnieje
    if (krw_dst != __INT_MAX__) {
        int dst_lewo  = krw_pos - 0;
        int dst_prawo = n - krw_pos - 1;

        // obcinamy z lewej
        if (dst_lewo < dst_prawo) {
            // skoro krw_pos jest pierwsza 'W' to przed nia same 'T'
            int strata = dst_lewo * 2 + 1;
            gen_from_sum(sum - strata, krw_pos + 1, n - 1);
        }
        else {
            // skoro krw_pos jest pierwsza 'W' to za nia same 'T'
            int strata = dst_prawo * 2 + 1;
            gen_from_sum(sum - strata, 0, krw_pos - 1);
        }
    }

    gen_from_sum(sum, 0, n - 1);

    for (int i = 0; i < m; i++) {
        int k; std::cin >> k;
        auto p = solution[k];
        if (p.first == 0) std::cout << "NIE\n";
        else std::cout << p.first << ' ' << p.second << "\n";
    }
}
