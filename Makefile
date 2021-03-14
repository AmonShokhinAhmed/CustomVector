all:
	clang++ ./src/Main.cpp -I ./src -Wall -Werror -Wextra -pedantic -fsized-deallocation -g -std=c++14 -o CustomVector