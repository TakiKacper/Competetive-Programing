#include <iostream>

int main() {
    unsigned long long n; std::cin >> n;

    bool mozna = false;

    for (int a = 0; a * 3 <= n; a++) {
        int reszta = n - 3 * a;
        if (reszta % 8 == 0) {
            mozna = true;
            break;
        }
    }

    std::cout << (mozna ? "TAK" : "NIE");
}
