#include "PRNGs.h"
uint64_t xorshift_64_state = (uint64_t)std::random_device{}() << 32 | std::random_device{}();

uint64_t next_xorshift_64() {
	xorshift_64_state ^= xorshift_64_state << 13;
	xorshift_64_state ^= xorshift_64_state >> 7;
	xorshift_64_state ^= xorshift_64_state << 17;
	return xorshift_64_state;
}