#include "../includes/ft_ssl.h"
#include "../includes/libft.h"
#include "../includes/ft_whirlpool.h"

extern uint64_t	rhash_whirlpool_sbox[8][256];

/**
 * Performs a byte swap on a 64-bit unsigned integer.
 * This function swaps the endianness of a 64-bit unsigned integer by reversing
 * the order of its bytes.
 *
 * @param x The 64-bit unsigned integer to be byte-swapped.
 * @return The byte-swapped 64-bit unsigned integer.
 */
static uint64_t	bswap_64(uint64_t x)
{
	uint32_t	low = (x & 0xFFFFFFFF);
	low = ((low << 8) & 0xFF00FF00u) | ((low >> 8) & 0x00FF00FFu);
	low = (low >> 16) | (low << 16);

	uint32_t	high = (x >> 32);
	high = ((high << 8) & 0xFF00FF00u) | ((high >> 8) & 0x00FF00FFu);
	high = (high >> 16) | (high << 16);

	return ((uint64_t)low << 32) | high;
}

/**
 * Copies and byte-swaps a string to an array of 64-bit unsigned integers.
 * This function is used to copy a string from one memory location to another,
 * while simultaneously performing a byte-swap operation for 64-bit alignment.
 *
 * @param to Destination pointer where the data will be copied.
 * @param index Starting index in the destination array where the data will be copied.
 * @param from Source pointer from which the data will be copied.
 * @param length The number of bytes to copy.
 */
static void	swap_copy_str_to_u64(void* to, int index, const void* from, size_t length)
{
	if ( 0 == (( (uintptr_t)to | (uintptr_t)from | (uintptr_t)index | length ) & 7) )
	{
		const uint64_t*	src = (const uint64_t*)from;
		const uint64_t*	end = (const uint64_t*)((const char*)src + length);
		uint64_t*		dst = (uint64_t*)((char*)to + index);
		while (src < end) *(dst++) = bswap_64( *(src++) )
			;
	}
	else
	{
		const char*	src = (const char*)from;
		for (length += index; (size_t)index < length; index++)
			((char*)to)[index ^ 7] = *(src++);
	}
}

/**
 * Initializes the Whirlpool hashing context.
 * This function sets up the initial state of the Whirlpool hashing context,
 * clearing the hash and setting the length to zero.
 *
 * @param ctx Pointer to the whirlpool_ctx structure representing the hashing context.
 */
static void	whirlpool_init(struct whirlpool_ctx* ctx)
{
	ctx->length = 0;
	ft_memset(ctx->hash, 0, sizeof(ctx->hash));
}

/**
 * Processes a single block of data in the Whirlpool hashing algorithm.
 * This function applies the Whirlpool transformation to a single 512-bit block
 * of data to update the hash state.
 *
 * @param hash The current hash state.
 * @param p_block Pointer to the 512-bit block of data to be processed.
 */
static void	whirlpool_process_block(uint64_t* hash, uint64_t* p_block)
{
	int				i;
	uint64_t		K[2][8];
	uint64_t		state[2][8];
	unsigned int	m = 0;
	const int		number_of_rounds = 10;

	static const uint64_t	rc[10] = {
		0x1823c6e887b8014fULL,
		0x36a6d2f5796f9152ULL,
		0x60bc9b8ea30c7b35ULL,
		0x1de0d7c22e4bfe57ULL,
		0x157737e59ff04adaULL,
		0x58c9290ab1a06b85ULL,
		0xbd5d10f4cb3e0567ULL,
		0xe427418ba77d95d8ULL,
		0xfbee7c66dd17479eULL,
		0xca2dbf07ad5a8333ULL
	};

	/* map the message buffer to a block */
	for (i = 0; i < 8; i++)
	{
		/* store K^0 and xor it with the intermediate hash state */
		K[0][i] = hash[i];
		state[0][i] = bswap_64(p_block[i]) ^ hash[i];
		hash[i] = state[0][i];
	}

	/* iterate over algorithm rounds */
	for (i = 0; i < number_of_rounds; i++)
	{
		/* compute K^i from K^{i-1} */
		K[m ^ 1][0] = WHIRLPOOL_OP(K[m], 0) ^ rc[i];
		K[m ^ 1][1] = WHIRLPOOL_OP(K[m], 1);
		K[m ^ 1][2] = WHIRLPOOL_OP(K[m], 2);
		K[m ^ 1][3] = WHIRLPOOL_OP(K[m], 3);
		K[m ^ 1][4] = WHIRLPOOL_OP(K[m], 4);
		K[m ^ 1][5] = WHIRLPOOL_OP(K[m], 5);
		K[m ^ 1][6] = WHIRLPOOL_OP(K[m], 6);
		K[m ^ 1][7] = WHIRLPOOL_OP(K[m], 7);

		/* apply the i-th round transformation */
		state[m ^ 1][0] = WHIRLPOOL_OP(state[m], 0) ^ K[m ^ 1][0];
		state[m ^ 1][1] = WHIRLPOOL_OP(state[m], 1) ^ K[m ^ 1][1];
		state[m ^ 1][2] = WHIRLPOOL_OP(state[m], 2) ^ K[m ^ 1][2];
		state[m ^ 1][3] = WHIRLPOOL_OP(state[m], 3) ^ K[m ^ 1][3];
		state[m ^ 1][4] = WHIRLPOOL_OP(state[m], 4) ^ K[m ^ 1][4];
		state[m ^ 1][5] = WHIRLPOOL_OP(state[m], 5) ^ K[m ^ 1][5];
		state[m ^ 1][6] = WHIRLPOOL_OP(state[m], 6) ^ K[m ^ 1][6];
		state[m ^ 1][7] = WHIRLPOOL_OP(state[m], 7) ^ K[m ^ 1][7];

		m = m ^ 1;
	}

	/* apply the Miyaguchi-Preneel compression function */
	hash[0] ^= state[0][0];
	hash[1] ^= state[0][1];
	hash[2] ^= state[0][2];
	hash[3] ^= state[0][3];
	hash[4] ^= state[0][4];
	hash[5] ^= state[0][5];
	hash[6] ^= state[0][6];
	hash[7] ^= state[0][7];
}

/**
 * Updates the Whirlpool hash with a chunk of data.
 * This function processes the input message in chunks to update the hash state.
 * It handles message blocks that are not aligned on 512-bit boundaries.
 *
 * @param ctx Pointer to the Whirlpool hashing context.
 * @param msg Pointer to the message chunk to be hashed.
 * @param size Size of the message chunk in bytes.
 */
static void	whirlpool_update(whirlpool_ctx* ctx, const unsigned char* msg, size_t size)
{
	unsigned	index = (unsigned)ctx->length & 63;
	unsigned	left;
	ctx->length += size;

	if (index)
	{
		left = whirlpool_block_size - index;
		ft_memcpy(ctx->message + index, msg, (size < left ? size : left));
		if (size < left)
			return;

		whirlpool_process_block(ctx->hash, (uint64_t*)ctx->message);
		msg  += left;
		size -= left;
	}
	while (size >= whirlpool_block_size)
	{
		uint64_t* aligned_message_block;
		if (0 == (7 & (uintptr_t)(msg)))
			aligned_message_block = (uint64_t*)msg;
		else
		{
			ft_memcpy(ctx->message, msg, whirlpool_block_size);
			aligned_message_block = (uint64_t*)ctx->message;
		}

		whirlpool_process_block(ctx->hash, aligned_message_block);
		msg += whirlpool_block_size;
		size -= whirlpool_block_size;
	}
	if (size)
		ft_memcpy(ctx->message, msg, size);
}

/**
 * Finalizes the Whirlpool hash computation.
 * This function processes any remaining message bytes, pads the message as required,
 * and produces the final hash value.
 *
 * @param ctx Pointer to the Whirlpool hashing context.
 * @param result Buffer where the final hash will be stored.
 */
static void	whirlpool_final(whirlpool_ctx* ctx, unsigned char* result)
{
	unsigned	index = (unsigned)ctx->length & 63;
	uint64_t*	msg64 = (uint64_t*)ctx->message;

	ctx->message[index++] = 0x80;

	if (index > 32)
	{
		while (index < 64)
		{
			ctx->message[index++] = 0;
		}
		whirlpool_process_block(ctx->hash, msg64);
		index = 0;
	}
	while (index < 56)
	{
		ctx->message[index++] = 0;
	}
	msg64[7] = bswap_64(ctx->length << 3);
	whirlpool_process_block(ctx->hash, msg64);

	swap_copy_str_to_u64(result, 0, ctx->hash, 64);
}

/**
 * Computes the Whirlpool hash of a given message.
 * This function initializes the hashing context, processes the message, and finalizes
 * the hash, returning the hexadecimal representation of the hash.
 *
 * @param original_msg Pointer to the message to be hashed.
 * @param size Size of the message in bytes.
 * @return A string representing the hexadecimal value of the computed hash.
 */
char	*my_WHIRLPOOL(uint8_t *original_msg, size_t size)
{
	uint8_t			hash[WHIRLPOOL_DIGEST_SIZE];
	whirlpool_ctx	ctx;

	whirlpool_init(&ctx);
	whirlpool_update(&ctx, (const unsigned char*)original_msg, size);
	whirlpool_final(&ctx, hash);

	char	*hex_representation = bytes_to_hex_string((uint8_t*)&hash, sizeof(hash));

	return (hex_representation);
}
