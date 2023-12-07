#include "../includes/ft_ssl.h"

extern args_t	args;

/**
 * Converts a single byte to its hexadecimal string representation.
 * The function maps each half-byte (nibble) of the input byte to its hexadecimal character
 * and stores the two resulting characters in the provided string.
 *
 * @param byte The byte to convert to hexadecimal.
 * @param hex_str Pointer to a char array where the hexadecimal representation will be stored.
 */
static void	byte_to_hex(uint8_t byte, char *hex_str)
{
	const char	hex_chars[] = "0123456789abcdef";
	hex_str[0] = hex_chars[(byte >> 4) & 0x0F];
	hex_str[1] = hex_chars[byte & 0x0F];
}

/**
 * Converts an array of bytes to a hexadecimal string representation.
 * This function allocates memory for the resulting string, which needs to be freed by the caller.
 * Each byte in the array is converted to its hexadecimal representation.
 *
 * @param bytes Pointer to the array of bytes to be converted.
 * @param num_bytes Number of bytes in the array.
 * @return Pointer to a string containing the hexadecimal representation of the bytes.
 */
char	*bytes_to_hex_string(uint8_t *bytes, size_t num_bytes)
{
	char	*hex_str = malloc(num_bytes * 2 + 1);
	if (!hex_str)
	{
		ft_putstr_fd("Error: malloc() failed\n", STDERR_FILENO);
		return (NULL);
	}
	for (size_t i = 0; i < num_bytes; i++)
		byte_to_hex(bytes[i], &hex_str[i * 2]);

	hex_str[num_bytes * 2] = '\0';
	return (hex_str);
}

/**
 * Reads the contents of a binary file or stdin into a dynamically allocated buffer.
 * The function attempts to open and read the entire content of a specified file, or stdin if no filename is provided.
 * It handles errors gracefully and prints relevant error messages. The buffer size grows dynamically as more data is read.
 *
 * @param filename The name of the file to read, or NULL to read from stdin.
 * @param size Pointer to a variable where the size of the read content will be stored.
 * @return Pointer to a dynamically allocated buffer containing the file's contents.
 */
uint8_t	*read_binary_file(const char *filename, size_t *size)
{
	const size_t	buffer_size = 1024;
	int				fd;

	if (!filename)
		fd = STDIN_FILENO;
	else
		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error((char *)filename, strerror(errno));
		return (NULL);
	}

	uint8_t	*buffer = ft_calloc(buffer_size, sizeof(uint8_t));
	if (!buffer)
	{
		perror("ft_ssl: malloc() failed");
		close(fd);
		return (NULL);
	}

	size_t	total_read = 0;
	ssize_t	bytes_read;

	while ((bytes_read = read(fd, buffer + total_read, buffer_size)) > 0)
	{
		total_read += bytes_read;
		uint8_t *new_buffer = realloc(buffer, total_read + buffer_size);
		if (!new_buffer)
		{
			ft_printf("ft_ssl: malloc() failed");
			free(buffer);
			close(fd);
			return (NULL);
		}
		buffer = new_buffer;
	}

	if (bytes_read == -1)
	{
		print_error((char *)filename, strerror(errno));
		free(buffer);
		close(fd);
		return (NULL);
	}

	close(fd);
	*size = total_read;
	return (buffer);
}

/**
 * Removes the trailing newline character from a string, if present.
 * This function checks the last character of the string and replaces it with
 * a null terminator if it's a newline character.
 *
 * @param str Pointer to the string from which the newline should be removed.
 */
void	remove_return(char *str)
{
	size_t	len = strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
}
