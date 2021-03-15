#include "PRNGs.h"
#include <boost/math/constants/constants.hpp>
using namespace std;

uint32_t hypersphere_count;
uint64_t temp;
double current_point;
double divisor_64 = pow(2, 128);
float divisor_31 = pow(2, 62);
const double pi = boost::math::constants::pi<double>();
const double two_dim_vol = pi;
const double three_dim_vol = 4*pi/3;
const double four_dim_vol = pow(pi, 2)/2;
const double five_dim_vol = 8*pow(pi, 2)/15;


double mc_test(uint16_t n_dim, uint32_t n_iterations) {
	hypersphere_count = 0;
	for (uint32_t i = 0; i < n_iterations; i++) {
		current_point = 0;
		for (uint32_t j = 0; j < n_dim; j++) {
			temp = next_lcg_64(); // Choose which generator to test
			current_point += (double)temp * temp / divisor_64;
		}
		if (current_point <= 1) {
			hypersphere_count++;
		}
	}
	return (double)hypersphere_count * pow(2, n_dim) / n_iterations;
}

void monte_carlo() {
	cout << "Monte Carlo test results:" << endl;
	cout << "2D error: " << mc_test(2, (uint32_t)1 << 30) - two_dim_vol << endl;
	cout << "3D error: " << mc_test(3, (uint32_t)1 << 30) - three_dim_vol << endl;
	cout << "4D error: " << mc_test(4, (uint32_t)1 << 30) - four_dim_vol << endl;
	cout << "5D error: " << mc_test(5, (uint32_t)1 << 30) - five_dim_vol << endl;
}