#include "PRNGs.h"

uint32_t lcg_state = std::random_device{}();
uint32_t a = 65539;
uint32_t m = 2147483648;

uint32_t next_RANDU() {
	lcg_state = (lcg_state * a) % m;
	return lcg_state;
}