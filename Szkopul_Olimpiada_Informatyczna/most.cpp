#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];

    sort(t.begin(), t.end());

    long long ans = 0;
    int i = n - 1;

    while (i >= 3) {
        long long A = 2 * t[1] + t[0] + t[i];
        long long B = 2 * t[0] + t[i] + t[i - 1];
        ans += min(A, B);
        i -= 2;
    }

    if (i == 2) {
        ans += t[0] + t[1] + t[2];
    } else if (i == 1) {
        ans += t[1];
    } else if (i == 0) {
        ans += t[0];
    }

    cout << ans << "\n";
}
