#ifndef SWZ_RANDOM_H
#define SWZ_RANDOM_H

#include<stdint.h>
#include<stddef.h>


typedef struct swzrng Rng;

// -
//Rng* swzrng_alloc(const RngType *type);
//void swzrng_deall(Rng *rng);
//void swzrng_set(const Rng *rng, uint64_t seed);
//uint64_t swzrng_max(const Rng *rng);
// uint64_t swzrng_min(const Rng *rng);
// const char* swzrng_name(const Rng *rng);
//size_t swzrng_size(const Rng *rng);

uint64_t swzrng_min();
uint64_t swzrng_max();
void swzrng_seed(uint64_t seed);
uint64_t swzrng_randInt();
double swzrng_randFloat();

#endif