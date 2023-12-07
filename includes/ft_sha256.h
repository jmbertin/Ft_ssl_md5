#ifndef FT_SHA256_H
# define FT_SHA256_H

/**
 * Ensures a 32-bit unsigned value wraps correctly.
 */
#define U32V(v) ((uint32_t)(v) & 0xFFFFFFFFU)

/**
 * Performs a left rotate operation on a 32-bit value.
 * @param v The value to rotate.
 * @param n The number of bits to rotate.
 */
#define ROTL32(v, n) (U32V((uint32_t)(v) << (n)) | ((uint32_t)(v) >> (32 - (n))))

/**
 * Performs a right rotate operation on a 32-bit value.
 * @param v The value to rotate.
 * @param n The number of bits to rotate.
 */
#define ROTR32(v, n) ROTL32(v, 32 - (n))

/**
 * Defines the size of the SHA256 digest output in bytes.
 */
#define SHA256_DIGEST_SIZE 32

/**
 * SHA256 functions for bitwise operations during hashing.
 * These functions are used in the message schedule of the SHA256 algorithm.
 */
#define S0(x) (ROTR32(x, 2) ^ ROTR32(x,13) ^ ROTR32(x, 22))
#define S1(x) (ROTR32(x, 6) ^ ROTR32(x,11) ^ ROTR32(x, 25))
#define s0(x) (ROTR32(x, 7) ^ ROTR32(x,18) ^ (x >> 3))
#define s1(x) (ROTR32(x,17) ^ ROTR32(x,19) ^ (x >> 10))

/**
 * SHA256 message schedule array operations.
 */
#define blk0(i) (W[i] = data[i])
#define blk2(i) (W[i&15] += s1(W[(i-2)&15]) + W[(i-7)&15] + s0(W[(i-15)&15]))

/**
 * SHA256 logical functions used in transformation.
 */
#define Ch(x,y,z) (z^(x&(y^z)))
#define Maj(x,y,z) ((x&y)|(z&(x|y)))

/**
 * Temporary variables used in SHA256 transformation.
 */
#define a(i) T[(0-(i))&7]
#define b(i) T[(1-(i))&7]
#define c(i) T[(2-(i))&7]
#define d(i) T[(3-(i))&7]
#define e(i) T[(4-(i))&7]
#define f(i) T[(5-(i))&7]
#define g(i) T[(6-(i))&7]
#define h(i) T[(7-(i))&7]

/**
 * SHA256 transformation macro.
 */
#define R(i) h(i) += S1(e(i)) + Ch(e(i),f(i),g(i)) + K[i+j] + (j?blk2(i):blk0(i)); d(i) += h(i); h(i) += S0(a(i)) + Maj(a(i), b(i), c(i))

/**
 * Structure to hold SHA256 computation state.
 */
typedef struct	sha256_group_s
{
	uint32_t state[8];
	uint64_t count;
	unsigned char buffer[64];
}				sha256_group_t;

/**
 * SHA256 constant table.
 * Derived from the cube roots of the first 64 primes 2..311.
 */
static const uint32_t K[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#endif
