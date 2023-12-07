#include "../includes/ft_ssl.h"

extern args_t	args;

/**
 * Prints an error message to stderr and exits the program.
 * This function is used for displaying error messages related to program execution or argument parsing.
 * After displaying the error message, it terminates the program with an exit status of 1.
 *
 * @param str Pointer to the string containing the error message to be printed.
 */
void	print_error_and_exit(char *str)
{
	ft_printf("ft_ssl: Error: %s\n", str);
	exit(1);
}

/**
 * Prints an error message for a specific file operation.
 * The function formats and prints an error message based on the current command
 * (MD5, SHA256 or WHIRLPOOL) and the filename involved in the operation.
 *
 * @param filename The name of the file involved in the error.
 * @param error_msg The error message to be displayed.
 */
void print_error(char *filename, char *error_msg)
{
	switch (args.command)
	{
		case 1:
			ft_printf("ft_ssl: md5: %s: %s\n", filename, error_msg);
			break;
		case 2:
			ft_printf("ft_ssl: sha256: %s: %s\n", filename, error_msg);
			break;
		case 3:
			ft_printf("ft_ssl: whirlpool: %s: %s\n", filename, error_msg);
			break;
		default:
			ft_printf("ft_ssl: unknown algorithm: %s: %s\n", filename, error_msg);
			break;
	}
}

/**
 * Displays the hash result according to the specified format.
 * This function handles different output formats based on the program's flags
 * and the type of input (standard input, string, or file).
 * It supports standard, reverse, and quiet modes for displaying the hash.
 *
 * @param hash Pointer to the computed hash string.
 * @param filename Pointer to the filename or input string associated with the hash.
 * @param type Indicator of the input source type: 1 for stdin, 2 for string, 3 for file.
 */
void	display_hash(char *hash, char *filename, int type)
{
	remove_return(filename);
	if (args.quiet)
	{
		if (type == 1 && args.echo)
			ft_printf("%s\n", filename);
		ft_printf("%s\n", hash);
	}
	else if (args.reverse)
	{
		switch (type)
		{
			case 1: ft_printf("(\"%s\")= %s\n", filename, hash); break;
			case 2: ft_printf("%s \"%s\"\n", hash, filename); break;
			case 3: ft_printf("%s %s\n", hash, filename); break;
		}
	}
	else
	{
		if (type != 1)
		{
			const char*	algo_str;
			switch (args.command)
			{
				case 1: algo_str = "MD5 "; break;
				case 2: algo_str = "SHA256 "; break;
				case 3: algo_str = "WHIRLPOOL "; break;
			}
			ft_printf("%s", algo_str);
		}

		if (type == 1)
		{
			const char*	prefix = args.echo ? "(\"%s\")= " : "(stdin)= ";
			ft_printf(prefix, filename);
		}
		else if (type == 3)
			ft_printf("(%s) = ", filename);
		else
			ft_printf("(\"%s\") = ", filename);

		ft_printf("%s\n", hash);
	}
}
