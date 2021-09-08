#include "PRNGs.h"

uint64_t lcg_state = (uint64_t)std::random_device{}() << 32 | std::random_device{}();
uint64_t a = 2862933555777941757;

uint64_t next_lcg_64() {
	lcg_state = lcg_state * a + 1;
	return lcg_state;
}