#include "PRNGs.h"

uint64_t xorshift_64s_state = (uint64_t)std::random_device{}() << 32 | std::random_device{}();
const uint64_t multiplier = 2685821657736338717;

uint64_t next_xorshift_64s() {
	xorshift_64s_state ^= xorshift_64s_state << 12;
	xorshift_64s_state ^= xorshift_64s_state >> 25;
	xorshift_64s_state ^= xorshift_64s_state << 27;
	return xorshift_64s_state * multiplier;
}