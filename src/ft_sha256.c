#include "../includes/ft_ssl.h"
#include "../includes/ft_sha256.h"
#include "../includes/libft.h"

/**
 * Initializes the SHA256 state structure with predefined constants.
 * These constants are part of the SHA256 algorithm's standard and are used
 * as the starting point for the SHA256 hashing process.
 *
 * @param p Pointer to the sha256_group_t structure that will hold the SHA256 state.
 */
void	sha256_init_blocks(sha256_group_t *p)
{
	p->state[0] = 0x6a09e667;
	p->state[1] = 0xbb67ae85;
	p->state[2] = 0x3c6ef372;
	p->state[3] = 0xa54ff53a;
	p->state[4] = 0x510e527f;
	p->state[5] = 0x9b05688c;
	p->state[6] = 0x1f83d9ab;
	p->state[7] = 0x5be0cd19;
	p->count = 0;
}

/**
 * Transforms the SHA256 state based on the given data block.
 * This function processes the data in 512-bit blocks, applying the SHA256
 * algorithm's compression function to modify the state.
 *
 * @param state The current state of the SHA256 hash computation.
 * @param data A 512-bit block of data to be processed.
 */
static void	sha256_transform(uint32_t *state, const uint32_t *data)
{
	uint32_t	W[16];
	unsigned	j;
	uint32_t	T[8];
	for (j = 0; j < 8; j++)
		T[j] = state[j];

	for (j = 0; j < 64; j += 16)
	{
		unsigned i;
		for (i = 0; i < 16; i++) { R(i); }
	}

	for (j = 0; j < 8; j++)
		state[j] += T[j];
}

/**
 * Writes a 512-bit block of data into the SHA256 buffer, preparing it for transformation.
 * This function converts the 64-byte buffer into a 512-bit block and calls sha256_transform
 * to process this block.
 *
 * @param p The SHA256 state structure containing the current hash computation state.
 */
static void	sha256_write_byte_block(sha256_group_t *p)
{
	uint32_t	data32[16];
	for (unsigned i = 0; i < 16; i++)
		data32[i] =
		((uint32_t)(p->buffer[i * 4    ]) << 24) +
		((uint32_t)(p->buffer[i * 4 + 1]) << 16) +
		((uint32_t)(p->buffer[i * 4 + 2]) <<  8) +
		((uint32_t)(p->buffer[i * 4 + 3]));
	sha256_transform(p->state, data32);
}

/**
 * Updates the SHA256 state with a new message block.
 * This function is called for each part of the message to be hashed,
 * updating the SHA256 state accordingly.
 *
 * @param p The SHA256 state structure to update.
 * @param original_msg Pointer to the message block to be hashed.
 * @param size Size of the message block in bytes.
 */
static void	sha256_update(sha256_group_t *p, uint8_t *original_msg, size_t size)
{
	uint32_t	curBufferPos = (uint32_t)p->count & 0x3F;
	while (size > 0)
	{
		p->buffer[curBufferPos++] = *original_msg++;
		p->count++;
		size--;
		if (curBufferPos == 64)
		{
			curBufferPos = 0;
			sha256_write_byte_block(p);
		}
	}
}

/**
 * Finalizes the SHA256 hashing process.
 * This function pads the message as required by the SHA256 standard,
 * processes any remaining data in the buffer, and produces the final hash value.
 *
 * @param p The SHA256 state structure to finalize.
 * @param hashed Pointer to the buffer where the final hash will be stored.
 */
static void	sha256_final(sha256_group_t *p, uint8_t *hashed)
{
	uint64_t	lenInBits = (p->count << 3);
	uint32_t	curBufferPos = (uint32_t)p->count & 0x3F;

	p->buffer[curBufferPos++] = 0x80;
	while (curBufferPos != (64 - 8))
	{
		curBufferPos &= 0x3F;
		if (curBufferPos == 0)
			sha256_write_byte_block(p);
		p->buffer[curBufferPos++] = 0;
	}
	for (unsigned i = 0; i < 8; i++)
	{
		p->buffer[curBufferPos++] = (unsigned char)(lenInBits >> 56);
		lenInBits <<= 8;
	}
	sha256_write_byte_block(p);

	for (unsigned i = 0; i < 8; i++)
	{
		*hashed++ = (unsigned char)(p->state[i] >> 24);
		*hashed++ = (unsigned char)(p->state[i] >> 16);
		*hashed++ = (unsigned char)(p->state[i] >> 8);
		*hashed++ = (unsigned char)(p->state[i]);
	}
	sha256_init_blocks(p);
}

/**
 * Computes the SHA256 hash of the given message.
 * This function initializes the SHA256 state, processes the message in blocks,
 * and then finalizes the computation to produce the hash.
 *
 * @param original_msg Pointer to the original message to be hashed.
 * @param size Length of the original message in bytes.
 * @return Pointer to a string containing the hexadecimal representation of the SHA256 hash.
 *         Memory for this string is dynamically allocated and should be freed by the caller.
 */
char	*my_SHA256(uint8_t *original_msg, size_t size)
{
	uint8_t			hashed[64];
	sha256_group_t	hash;

	sha256_init_blocks(&hash);
	sha256_update(&hash, original_msg, size);
	sha256_final(&hash, hashed);

	char	*representation = bytes_to_hex_string(hashed, 32);

	return (representation);
}
