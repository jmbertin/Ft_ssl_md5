#include "../includes/ft_ssl.h"
#include "../includes/ft_md5.h"
#include "../includes/libft.h"

/**
 * Initializes the MD5 state variables (A, B, C, D) to their default values.
 * These values are part of the MD5 algorithm's standard and are used as the starting point
 * for the MD5 hashing process.
 *
 * @param ctx Pointer to the md5_group_t structure that will hold the MD5 state.
 */
static void	md5_init_blocks(md5_group_t *ctx)
{
	ctx->A = 0x67452301;
	ctx->B = 0xefcdab89;
	ctx->C = 0x98badcfe;
	ctx->D = 0x10325476;
}

/**
 * Performs the padding step of the MD5 algorithm.
 * It pads the input message to ensure that its length is congruent to 448 modulo 512.
 * The padding involves adding a single bit '1' followed by as many zeros as needed to meet the length requirement,
 * and finally appending the length of the original message in bits at the end of the padded message.
 *
 * @param initial_msg Pointer to the input message.
 * @param initial_len Length of the input message in bytes.
 * @param padded_msg Pointer to the pointer where the padded message will be stored.
 * @param padded_len Pointer to the size of the padded message. This value will be set by the function.
 */
static void	md5_pad(const uint8_t *initial_msg, size_t initial_len, uint8_t **padded_msg, size_t *padded_len)
{
	const size_t	block_size = 64;

	*padded_len = ((((initial_len + 8) / block_size) + 1) * block_size) - 8;
	*padded_msg = calloc(*padded_len + 64, 1);
	if (*padded_msg == NULL)
	{
		fprintf(stderr, "Error: calloc() failed\n");
		return;
	}

	memcpy(*padded_msg, initial_msg, initial_len);
	(*padded_msg)[initial_len] = 0x80;

	uint64_t	bit_len = initial_len * 8;
	memcpy(*padded_msg + *padded_len, &bit_len, 4);
}

/**
 * Processes a single 512-bit block of the message as part of the MD5 hashing algorithm.
 * It modifies the MD5 state (A, B, C, D) based on the contents of the given block.
 *
 * @param blocks Pointer to the MD5 state (A, B, C, D).
 * @param msg Pointer to the message (or a part of the message) to be processed.
 * @param offset The offset in the message where the 512-bit block starts.
 */
static void	md5_process_block(md5_group_t *blocks, uint8_t *msg, size_t offset)
{
	uint32_t *w = (uint32_t *) (msg + offset);

	uint32_t	a = blocks->A;
	uint32_t	b = blocks->B;
	uint32_t	c = blocks->C;
	uint32_t	d = blocks->D;

	uint32_t	i;
	for(i = 0; i < 64; i++)
	{
		uint32_t	f, g;

		if (i < 16)
		{
			f = (b & c) | ((~b) & d);
			g = i;
		}
		else if (i < 32)
		{
			f = (d & b) | ((~d) & c);
			g = (5*i + 1) % 16;
		}
		else if (i < 48)
		{
			f = b ^ c ^ d;
			g = (3*i + 5) % 16;
		}
		else
		{
			f = c ^ (b | (~d));
			g = (7*i) % 16;
		}
		uint32_t	temp = d;
		d = c;
		c = b;
		b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
		a = temp;
	}
	blocks->A += a;
	blocks->B += b;
	blocks->C += c;
	blocks->D += d;
}

/**
 * Computes the MD5 hash of the given message.
 * It first pads the message, then processes each 512-bit block, and finally returns the MD5 hash as a hexadecimal string.
 *
 * @param original_msg Pointer to the original message to be hashed.
 * @param len Length of the original message in bytes.
 * @return Pointer to a string containing the hexadecimal representation of the MD5 hash. Memory for this string is dynamically allocated and should be freed by the caller.
 */
char	*my_MD5(uint8_t *original_msg, size_t len)
{
	uint8_t	*padded_msg = NULL;
	size_t	padded_len = 0;

	md5_pad(original_msg, len, &padded_msg, &padded_len);

	md5_group_t	blocks;
	md5_init_blocks(&blocks);

	for(size_t offset = 0; offset < padded_len; offset += 64)
		md5_process_block(&blocks, padded_msg, offset);

	free(padded_msg);

	char	*hex_representation = bytes_to_hex_string((uint8_t*)&blocks, sizeof(blocks));

	return (hex_representation);
}
