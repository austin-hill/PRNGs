#include <stdint.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <random>
#include <iomanip>
#include <chrono>

uint64_t next_lcg_64();
uint64_t next_xorshift_64();
uint64_t next_xorshift_64s();
uint32_t next_RANDU();
void serial_tests();
void prob_test();
void monte_carlo();