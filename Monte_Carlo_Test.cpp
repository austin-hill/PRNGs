#include "PRNGs.h"
using namespace std;

uint32_t hypersphere_count;
uint64_t temp;
double current_point;
double divisor_64 = pow(2, 128);
float divisor_31 = pow(2, 62);

double mc_test(uint16_t n_dim, uint32_t n_iterations) {
	hypersphere_count = 0;
	for (uint32_t i = 0; i < n_iterations; i++) {
		current_point = 0;
		for (uint32_t j = 0; j < n_dim; j++) {
			temp = next_lcg_64(); // Choose which generator to test
			current_point += (double)temp * temp / divisor_31;
		}
		if (current_point <= 1) {
			hypersphere_count++;
		}
	}
	return (double)hypersphere_count * pow(2, n_dim) / n_iterations;
}

void monte_carlo() {
	cout << "2D hypersphere volume: " << mc_test(2, (uint32_t)1 << 30) << endl;
	cout << "3D hypersphere volume: " << mc_test(3, (uint32_t)1 << 30) << endl;
	cout << "4D hypersphere volume: " << mc_test(4, (uint32_t)1 << 30) << endl;
	cout << "5D hypersphere volume: " << mc_test(5, (uint32_t)1 << 30) << endl;
}