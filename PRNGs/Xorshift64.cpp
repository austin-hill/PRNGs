#include "PRNGs.h"

uint64_t xorshift_64_state = (uint64_t)std::random_device{}() << 32 | std::random_device{}();

uint64_t next_xorshift_64() {
	xorshift_64_state ^= xorshift_64_state << 18;
	xorshift_64_state ^= xorshift_64_state >> 31;
	xorshift_64_state ^= xorshift_64_state << 11;
	return xorshift_64_state;
}