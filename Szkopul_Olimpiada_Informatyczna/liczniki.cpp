#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);
	
	int n, m; std::cin >> n >> m;
	
	std::vector<std::pair<int, unsigned long long>> c(n);
	for (int i = 0; i < n; i++) std::cin >> c[i].first;
	for (int i = 0; i < n; i++) std::cin >> c[i].second;
	
	std::sort(c.begin(), c.end());
	
	std::vector<unsigned long long> prev(n);
	for (int i = 0; i < n; i++) prev[i] = c[i].second;
	
	unsigned long long k = 0;
	
	while (m--) {
		std::multiset<int> z;
		for (int i = 0; i < n; i++) {
			int x; std::cin >> x;
			z.insert(x);
		}
		
		for (int i = n - 1; i != -1; i--) {
			auto itr = z.lower_bound(prev[i]);
			
			if (itr == z.end() || *itr < prev[i]) {
				std::cout << "NIE"; return 0;
			}
			
			k += (*itr - prev[i]) * c[i].first;
			prev[i] = *itr;
			
			z.erase(itr);
		}
	}
	
	std::cout << k;
}
