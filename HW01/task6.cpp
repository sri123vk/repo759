#include <cstdio>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " N\n";
        return 1;
    }

    int N = std::stoi(argv[1]);

    for (int i = 0; i <= N; i++) {
        std::printf("%d%s", i, (i == N) ? "\n" : " ");
    }

    for (int i = N; i >= 0; i--) {
        std::cout << i << (i == 0 ? '\n' : ' ');
    }

    return 0;
}
