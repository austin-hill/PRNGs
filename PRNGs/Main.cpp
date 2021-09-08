#include "PRNGs.h"

int main() {
	std::cout << std::setprecision(10);
	serial_tests();
	prob_test();
	monte_carlo();
	system("pause");
	return 0;
}