#include<stdlib.h>
#include "swzrandom.h"

typedef struct {
    const char *name;
    uint64_t max;
    uint64_t min;
    size_t size;

    void (*seed)(void *state, uint64_t seed);
    uint64_t (*randInt)(void *state);
    double (*randFloat)(void *state);
}RngType;


struct swzrng{
    const RngType *type;
    void *state;
};
// -*-
static uint64_t _mt_randInt(void *state);
static double _mt_randFloat(void *state);
static void _mt_seed(void *state, uint64_t seed);

#define N   624
#define M   397

// - most significant w-r bits
static const uint64_t UPPER_MASK = 0x80000000UL;
// - least significant r bits
static const uint64_t LOWER_MASK = 0x7fffffffUL;

typedef struct {
    uint64_t mt[N];
    int32_t mti;
}State;

// - mt_get
static uint64_t _mt_randInt(void *state){
    State *self = (State*)state;
    uint64_t k;
    uint64_t* const mt = self->mt;

#define MAGIC(y)    (((y)&0x1) ? 0x9908b0dfUL : 0)

    if(self->mti >= N){
        // generate N words at one time
        int32_t kk;
        for(kk=0; kk < N  - M; kk++){
            uint64_t y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^(y >> 1) ^ MAGIC(y);
        }
        for(; kk < N - 1; kk++){
            uint64_t y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
            mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ MAGIC(y);
        }
        {
            uint64_t y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
            mt[N - 1] = mt[M - 1] ^( y >> 1) ^ MAGIC(y);
        }

        self->mti = 0;
    }

    // - Tempering
    k = mt[self->mti];
    k ^= (k >> 11);
    k ^= (k << 7) & 0x9d2c5680UL;
    k ^= (k << 15) & 0xefc60000UL;
    k ^= (k >> 18);

    self->mti++;
    return k;
}

// - mt_get_double
static double _mt_randFloat(void *state){
    return _mt_randInt(state) / 4294967296.0;
}

// - mt_set
static void _mt_seed(void *state, uint64_t seed){
    State *self = (State*)state;
    int32_t i;
    if(seed == 0){ // default seed is 4357
        seed = 4357;
    }
    self->mt[0] = seed & 0xffffffffUL;
    for(i=1; i < N; i++){
        self->mt[i] = (1812433253UL * (self->mt[i-1] ^ (self->mt[i-1] >> 30)) + i);
        self->mt[i] &= 0xffffffffUL;
    }

    self->mti = i;
}

// -*-
static const RngType rngType = {
    .name="mt19937",
    .max=0xffffffffUL,
    .min=0,
    .size=sizeof(State),
    .seed=_mt_seed,
    .randInt=_mt_randInt,
    .randFloat=_mt_randFloat,
};

static Rng swzRng = {.type=NULL};
static State swzSate = {};

static void _swzrng_init(){
    if(swzRng.type==NULL){
        swzRng.type = &rngType;
        swzRng.state = &swzSate;
        _mt_seed(swzRng.state, 0);
        return;
    }
}

void swzrng_seed(uint64_t seed){
    _swzrng_init();
    swzRng.type->seed(swzRng.state, seed);
}

uint64_t swzrng_randInt(){
    _swzrng_init();
    return swzRng.type->randInt(swzRng.state);
}

double swzrng_randFloat(){
    _swzrng_init();
    return swzRng.type->randFloat(swzRng.state);
}

// -
uint64_t swzrng_min(){
    return swzRng.type->min;
}

// -
uint64_t swzrng_max(){
    return swzRng.type->max;
}