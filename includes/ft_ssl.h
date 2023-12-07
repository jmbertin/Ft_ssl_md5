#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <errno.h>
# include <fcntl.h>

# define MAX_STRINGS 100
# define MAX_FILES 100

/*
	Commands:
	- 0 = non valid command
	- 1 = md5
	- 2 = sha256
*/
typedef struct	args_s
{
	int		echo;
	int		quiet;
	int		reverse;
	int		command;
	char	*strings[MAX_STRINGS];
	int		num_strings;
	char	*files[MAX_FILES];
	int		num_files;
}				args_t;

/* Pointer to hash function */
typedef char *(*hash_function_t)(uint8_t *, size_t);

// MAIN
void	ft_hash(void);

// INTERACTIVE
void	ft_command_line(void);

// DISPLAY
void	print_error_and_exit(char *str);
void	display_hash(char *hash, char *filename, int type);
void	print_error(char *filename, char *error_msg);

// PARSE
void	parse_args(int ac, char **av);

// MD5
char	*my_MD5(uint8_t *original_msg, size_t len);

// SHA256
char	*my_SHA256(uint8_t *original_msg, size_t size);

// WHIRLPOOL
char	*my_WHIRLPOOL(uint8_t *original_msg, size_t size);

// TOOLS
char	*bytes_to_hex_string(uint8_t *bytes, size_t num_bytes);
uint8_t	*read_binary_file(const char *filename, size_t *size);
void	remove_return(char *str);

#endif
