#include "PRNGs.h"

uint32_t randu_state = std::random_device{}();
uint32_t ar = 65539;
uint32_t m = 2147483648;

uint32_t next_RANDU() {
	randu_state = (randu_state * ar) % m;
	return randu_state;
}