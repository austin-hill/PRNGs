 #include "PRNGs.h"
#include <boost/math/distributions/chi_squared.hpp>
#include <boost/math/distributions/poisson.hpp>
using namespace std;

const uint32_t n_iterations = (uint32_t)1 << 30;
const uint8_t n_cells = 20;
int hit_count[n_cells];
double hit_cdf[n_cells];
bool in_target;
bool overlaps;

double chi_squared(int X[], int mean) {
	double chi2 = 0;
	for (uint32_t i = 0; i < n_cells; i++) {
		chi2 += pow(X[i] - mean, 2) / mean;
	}
	return chi2;
}

void n_dim_test(uint16_t n_dim, int success_mean, uint8_t part_per_dim_pow, uint64_t cell_size, uint64_t max_target_size) {
	auto target_cell = new uint64_t[n_dim][n_cells];
	uint64_t* current_point = new uint64_t[n_dim];
	memset(hit_count, 0, sizeof(hit_count));

	for (uint8_t k = 0; k < n_cells; k++) {
		overlaps = true;
		for (uint32_t i = 0; i < n_dim; i++) {
			do {
				target_cell[i][k] = (uint64_t)std::random_device{}() << 32 | std::random_device{}();
			} while (target_cell[i][k] >= max_target_size);
			for (uint32_t j = 0; j < k; j++) {
				if (target_cell[i][k]+cell_size <= target_cell[i][j] || target_cell[i][k] >= target_cell[i][j]+cell_size) {
					overlaps = false;
				}
			}
		}
		if (overlaps==true && k >= 1) { k--; }
	}

	for (uint32_t i = 0; i < n_iterations; i++) {
		for (uint32_t j = 0; j < n_dim; j++) {
			current_point[j] = next_lcg_64(); // * ((uint64_t)1 << 33) if using RANDU
		}
		for (uint8_t k = 0; k < n_cells; k++) {
			in_target = 1;
			for (uint32_t j = 0; j < n_dim; j++) {
				if (current_point[j] < target_cell[j][k] || current_point[j] >= target_cell[j][k] + cell_size) {
					in_target = 0;
					break;
				}
			}
			if (in_target == 1) {
				hit_count[k]++;
			}
		}
	}
	delete[] target_cell;
	delete[] current_point;

	cout << "\n\nNumber of dimensions: " << n_dim << endl;
	cout << "Number of partitions in each dimension: " << ((uint32_t)1 << part_per_dim_pow) << endl;

	boost::math::poisson this_cell(success_mean);
	cout << "Single cell:\n" << "Hit count: " << hit_count[0];
	cout << "\np-value: " << boost::math::cdf(this_cell, hit_count[0]);

	boost::math::chi_squared mydist(n_cells - 1);
	cout << "\nMultiple cells:\n" << "Hit counts: ";
	for (uint8_t k = 0; k < n_cells; k++) {
		cout << hit_count[k] << ", ";
	}
	cout << "\np-value: " << boost::math::cdf(mydist, chi_squared(hit_count, success_mean));
}

void prob_test() {
	cout << "Probabilistic test results:";
	n_dim_test(1, 64, 24, (uint64_t)1 << 40, ((uint64_t)1 << 40) * ((1 << (64 - 59)) - 1));
	n_dim_test(2, 64, 12, (uint64_t)1 << 52, ((uint64_t)1 << 52) * ((1 << (64 - 59)) - 1));
	n_dim_test(3, 64, 8, (uint64_t)1 << 56, ((uint64_t)1 << 56) * ((1 << (64 - 59)) - 1));
	n_dim_test(4, 64, 6, (uint64_t)1 << 58, ((uint64_t)1 << 58) * ((1 << (64 - 59)) - 1));
	n_dim_test(5, 32, 5, (uint64_t)1 << 59, ((uint64_t)1 << 59) * ((1 << (64 - 59)) - 1));
	cout << "\n\n";
}