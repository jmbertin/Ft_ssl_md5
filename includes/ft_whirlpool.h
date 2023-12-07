#ifndef FT_WHIRLPOOL_H
# define FT_WHIRLPOOL_H

# include <stdint.h>

/**
 * Macro defining the Whirlpool operation.
 * This macro performs a series of transformations on a part of the message block
 * using the Whirlpool's S-boxes. It's a part of the internal transformation
 * function used in the Whirlpool hashing algorithm.
 *
 * @param src Source array containing parts of the message block.
 * @param shift The amount by which the message block is shifted in each operation.
 * @return Result of the Whirlpool operation on the shifted message block.
 */
#define WHIRLPOOL_OP(src, shift) ( \
	rhash_whirlpool_sbox[0][(int)(src[ shift      & 7] >> 56)       ] ^ \
	rhash_whirlpool_sbox[1][(int)(src[(shift + 7) & 7] >> 48) & 0xff] ^ \
	rhash_whirlpool_sbox[2][(int)(src[(shift + 6) & 7] >> 40) & 0xff] ^ \
	rhash_whirlpool_sbox[3][(int)(src[(shift + 5) & 7] >> 32) & 0xff] ^ \
	rhash_whirlpool_sbox[4][(int)(src[(shift + 4) & 7] >> 24) & 0xff] ^ \
	rhash_whirlpool_sbox[5][(int)(src[(shift + 3) & 7] >> 16) & 0xff] ^ \
	rhash_whirlpool_sbox[6][(int)(src[(shift + 2) & 7] >>  8) & 0xff] ^ \
	rhash_whirlpool_sbox[7][(int)(src[(shift + 1) & 7]      ) & 0xff])

# define WHIRLPOOL_DIGEST_SIZE 64
# define whirlpool_block_size 64

/**
 * Structure representing the Whirlpool hashing context.
 * This structure holds the internal state of the Whirlpool hash computation,
 * including the current hash value, a message buffer for processing,
 * and the total length of the processed data.
 */
typedef struct	whirlpool_ctx
{
	uint64_t		hash[8];						/* 512-bit algorithm internal hashing state */
	unsigned char	message[whirlpool_block_size];	/* 512-bit buffer to hash */
	uint64_t		length;							/* number of processed bytes */
}				whirlpool_ctx;

#endif
