#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int id;
    int fx, fy, sx, sy;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Rect> r(n);
    for (int i = 0; i < n; i++) {
        r[i].id = i;
        cin >> r[i].fx >> r[i].fy >> r[i].sx >> r[i].sy;
    }

    vector<int> ansX(n), ansY(n);

    // ===== PRZYDZIAŁ X =====
    {
        vector<Rect> v = r;
        sort(v.begin(), v.end(), [](const Rect& a, const Rect& b) {
            return a.sx < b.sx;
        });

        set<int> freeX;
        for (int i = 1; i <= 3000; i++) freeX.insert(i);

        for (auto& rec : v) {
            auto it = freeX.lower_bound(rec.fx);
            if (it == freeX.end() || *it > rec.sx) {
                cout << "NIE\n";
                return 0;
            }
            ansX[rec.id] = *it;
            freeX.erase(it);
        }
    }

    // ===== PRZYDZIAŁ Y =====
    {
        vector<Rect> v = r;
        sort(v.begin(), v.end(), [](const Rect& a, const Rect& b) {
            return a.sy < b.sy;
        });

        set<int> freeY;
        for (int i = 1; i <= 3000; i++) freeY.insert(i);

        for (auto& rec : v) {
            auto it = freeY.lower_bound(rec.fy);
            if (it == freeY.end() || *it > rec.sy) {
                cout << "NIE\n";
                return 0;
            }
            ansY[rec.id] = *it;
            freeY.erase(it);
        }
    }

    // ===== WYNIK =====
    for (int i = 0; i < n; i++) {
        cout << ansX[i] << " " << ansY[i] << "\n";
    }

    return 0;
}
