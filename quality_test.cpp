#include "PRNGs.h"
#include <boost/math/distributions/chi_squared.hpp>

using namespace std;

const uint32_t n_iterations = (uint32_t) 1 << 25;
const int n_partitions = (uint32_t) 1 << 14;
const uint64_t partition64_size = (uint64_t) 1 << 50;
const uint32_t partition31_size = (uint32_t) 1 << 17;
const int E = n_iterations / n_partitions;

float chi_squared(int X[]) {
	float chi2 = 0;
	for (int i = 0; i < n_partitions; i++) {
		chi2 += pow(X[i] - E, 2) / E;
	}
	return chi2;
}

float p_value(int X[]) {
	boost::math::chi_squared mydist(n_partitions -1);
	float p = boost::math::cdf(mydist, chi_squared(X));
	return p;
}

int main() {
	cout << "Number of iterations: " << n_iterations << "\n";
	cout << "Number of partitions: " << n_partitions << "\n";
	int X[n_partitions] = {};
	for (uint32_t i = 0; i < n_iterations; i++) {
		int index = next_lcg_64() / partition64_size;
		X[index]++;
	}
	cout << "LCG 64 p-value: " << p_value(X) << "\n";
	int Y[n_partitions] = {};
	for (uint32_t i = 0; i < n_iterations; i++) {
		int index = next_xorshift_64() / partition64_size;
		Y[index]++;
	}
	cout << "Xorshift 64 64 p-value: " << p_value(Y) << "\n";
	int Z[n_partitions] = {};
	for (uint32_t i = 0; i < n_iterations; i++) {
		int index = next_xorshift_64s() / partition64_size;
		Z[index]++;
	}
	cout << "Xorshift 64* p-value: " << p_value(Z) << "\n";
	int W[n_partitions] = {};
	for (uint32_t i = 0; i < n_iterations; i++) {
		int index = next_RANDU() / partition31_size;
		W[index]++;
	}
	cout << "RANDU p-value: " << p_value(W) << "\n";
	return 0;
}