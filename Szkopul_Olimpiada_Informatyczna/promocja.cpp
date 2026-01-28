#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    priority_queue<int> maxq;
    priority_queue<int, vector<int>, greater<int>> minq;
    unordered_map<int, int> cnt;

    long long koszt = 0;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        for (int j = 0; j < a; j++) {
            int x;
            cin >> x;
            maxq.push(x);
            minq.push(x);
            cnt[x]++;
        }

        // znajdź maksimum
        while (cnt[maxq.top()] == 0)
            maxq.pop();
        int mx = maxq.top();
        cnt[mx]--;

        // znajdź minimum
        while (cnt[minq.top()] == 0)
            minq.pop();
        int mn = minq.top();
        cnt[mn]--;

        koszt += mx - mn;
    }

    cout << koszt;
}
