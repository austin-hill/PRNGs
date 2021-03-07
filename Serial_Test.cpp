#include "PRNGs.h"
#include <boost/math/distributions/chi_squared.hpp>
using namespace std;

const uint32_t n_iterations = (uint32_t)1 << 30;
const uint8_t pow_1d = 27;
const uint8_t pow_2d = 13;
const uint8_t pow_3d = 9;
const uint32_t n_partitions_1d = (uint32_t)1 << 27;
const uint32_t n_partitions_2d = (uint32_t)1 << 13;
const uint32_t n_partitions_3d = (uint32_t)1 << 9;
const int E1 = n_iterations / n_partitions_1d;
const int E2 = n_iterations / (n_partitions_2d * n_partitions_2d);
const int E3 = n_iterations / (n_partitions_3d * n_partitions_3d * n_partitions_3d);
int X[n_partitions_1d] = {};
int X_2[n_partitions_2d][n_partitions_2d] = {};
int X_3[n_partitions_3d][n_partitions_3d][n_partitions_3d] = {};

double chi_squared(int X[]) {
	double chi2 = 0;
	for (uint32_t i = 0; i < n_partitions_1d; i++) {
		chi2 += pow(X[i] - E1, 2) / E1;
	}
	return chi2;
}

double chi_squared(int X[][n_partitions_2d]) {
	double chi2 = 0;
	for (uint32_t i = 0; i < n_partitions_2d; i++) {
		for (uint32_t j = 0; j < n_partitions_2d; j++) {
			chi2 += pow(X[i][j] - E2, 2) / E2;
		}
	}
	return chi2;
}

double chi_squared(int X[][n_partitions_3d][n_partitions_3d]) {
	double chi2 = 0;
	for (uint32_t i = 0; i < n_partitions_3d; i++) {
		for (uint32_t j = 0; j < n_partitions_3d; j++) {
			for (uint32_t k = 0; k < n_partitions_3d; k++) {
				chi2 += pow(X[i][j][k] - E3, 2) / E3;
			}
		}
	}
	return chi2;
}

float p_value(int X[]) {
	boost::math::chi_squared mydist(n_partitions_1d - 1);
	double p = boost::math::cdf(mydist, chi_squared(X));
	return p;
}

float p_value(int X[][n_partitions_2d]) {
	boost::math::chi_squared mydist(n_partitions_2d * n_partitions_2d - 1);
	double p = boost::math::cdf(mydist, chi_squared(X));
	return p;
}

float p_value(int X[][n_partitions_3d][n_partitions_3d]) {
	boost::math::chi_squared mydist(n_partitions_3d * n_partitions_3d * n_partitions_3d - 1);
	double p = boost::math::cdf(mydist, chi_squared(X));
	return p;
}

double one_dim_test() {
	memset(X, 0, sizeof(X));
	for (uint32_t i = 0; i < n_iterations; i++) { // If using RANDU, replace 64 with 31
		X[next_lcg_64() >> (64 - pow_1d)]++;
	}
	return p_value(X);
}

double two_dim_test() {
	memset(X_2, 0, sizeof(X_2[0][0]) * n_partitions_2d * n_partitions_2d);
	for (uint32_t i = 0; i < n_iterations; i++) { // If using RANDU, replace 64 with 31
		X_2[next_lcg_64() >> (64 - pow_2d)][next_lcg_64() >> (64 - pow_2d)]++;
	}
	return p_value(X_2);
}

double three_dim_test() {
	memset(X_3, 0, sizeof(X_3[0][0][0]) * n_partitions_3d * n_partitions_3d * n_partitions_3d);
	for (uint32_t i = 0; i < n_iterations; i++) { // If using RANDU, replace 64 with 31
		X_3[next_lcg_64() >> (64 - pow_3d)][next_lcg_64() >> (64 - pow_3d)][next_lcg_64() >> (64 - pow_3d)]++;
	}
	return p_value(X_3);
}

void serial_tests() {
	cout << "Serial tests:\nNumber of iterations: " << n_iterations;
	cout << "\n\nOne dimension: " << one_dim_test();
	cout << "\nTwo dimensions: " << two_dim_test();
	cout << "\nThree dimensions: " << three_dim_test() << "\n\n";
}