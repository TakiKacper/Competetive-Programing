#include <iostream>
#include <string>

#define pair_cond(x, y) ((x != 0 && y != 0) && (x == y))

int c, b, s;

int n;
std::string str;

inline bool good() {
    return !(pair_cond(c, b) || pair_cond(b, s) || pair_cond(c, s));
}

int solve_segment(int inc_beg, int exc_end) {
	c = 0; b = 0; s = 0;
	int score = 0;
	
	for (int x = inc_beg; x < exc_end; x++) {
        if      (str[x] == 'B') b++;
        else if (str[x] == 'C') c++;
        else if (str[x] == 'S') s++;
        
        if (good()) score = std::max(score, c + b + s);
    }
    
    return score;
}

int solve_segment_reverse(int inc_rev_beg) {
	c = 0; b = 0; s = 0;
	int score = 0;
	
	for (int x = inc_rev_beg; x != -1; x--) {
		if      (str[x] == 'B') b++;
        else if (str[x] == 'C') c++;
        else if (str[x] == 'S') s++;
        
        if (good()) score = std::max(score, c + b + s);
	}
	
	return score;
}

int solve_square() {
	int best = 0;

    for (int beg = 0; beg < n; beg++) {
        c = 0; b = 0; s = 0;

        for (int x = beg; x < n; x++) {
            if      (str[x] == 'B') b++;
            else if (str[x] == 'C') c++;
            else if (str[x] == 'S') s++;
            
            if (good()) best = std::max(best, c + b + s);
        }
    }
    
    return best;
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
    
    std::cin >> n;
    std::cin >> str;

	if (n <= 10) {
		std::cout << solve_square();
	}
	else {
		int best = 0;
		
		best = std::max(best, solve_segment(0, n));
		best = std::max(best, solve_segment(1, n));
		best = std::max(best, solve_segment(2, n));
		
		best = std::max(best, solve_segment_reverse(n - 1));
		best = std::max(best, solve_segment_reverse(n - 2));
		best = std::max(best, solve_segment_reverse(n - 3));
		
		std::cout << best;
	}
}
