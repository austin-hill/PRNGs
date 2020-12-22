#pragma once
#include <stdint.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <random>

uint64_t next_lcg_64();
uint64_t next_xorshift_64();
uint64_t next_xorshift_64s();
uint32_t next_RANDU();