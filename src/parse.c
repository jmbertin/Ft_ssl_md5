#include "../includes/ft_ssl.h"

extern args_t	args;

/**
 * Parses individual flag arguments for the command.
 * Validates the flag and sets the corresponding option in the global 'args' structure.
 * Supported flags are -p (echo), -q (quiet), and -r (reverse).
 * Exits the program if an invalid flag is encountered or if a flag is incorrectly formatted.
 *
 * @param arg The flag argument to parse.
 */
static void	parse_flags(char *arg)
{
	if (strlen(arg) != 2)
	{
		fprintf(stderr, "ft_ssl: Error: '%s' is an invalid flag.\n", arg);
		exit(1);
	}
	switch (arg[1])
	{
		case 'p':
			args.echo = 1;
			break;
		case 'q':
			args.quiet = 1;
			break;
		case 'r':
			args.reverse = 1;
			break;
		case 's':
			fprintf(stderr, "ft_ssl: Error: '-s' expect a string after it.\n");
			exit(1);
		default:
			fprintf(stderr, "ft_ssl: Error: '%s' is an invalid flag.\n", arg);
			exit(1);
	}
}

/**
 * Parses the command (either 'md5' or 'sha256') and sets the corresponding mode in the global 'args' structure.
 * Validates the command and exits the program if an invalid command is provided.
 *
 * @param str The command string to parse.
 */
static void	parse_command(char *str)
{
	if (strlen(str) == 3 || strlen(str) == 6 || strlen(str) == 9)
	{
		if (strncmp(str, "md5", 4) == 0)
			args.command = 1;
		else if (strncmp(str, "sha256", 7) == 0)
			args.command = 2;
		else if (strncmp(str, "whirlpool", 10) == 0)
			args.command = 3;
		else
		{
			fprintf(stderr, "ft_ssl: Error: '%s' is an invalid command.\n", str);
			exit(1);
		}
	}
	else
	{
		fprintf(stderr, "ft_ssl: Error: '%s' is an invalid command.\n", str);
		exit(1);
	}
}

/**
 * Parses the command line arguments provided to the program.
 * This function handles the overall argument parsing logic, including parsing the command,
 * flags, and any additional arguments like file names or strings for hashing.
 * Sets the global 'args' structure with parsed data.
 * Exits the program if invalid arguments are provided or if argument limits are exceeded.
 *
 * @param ac The argument count.
 * @param av The argument vector (array of strings).
 */
void	parse_args(int ac, char **av)
{
	int	i = 2;
	int	expect_string = 0;

	if (ac < 2)
		print_error_and_exit("usage: ft_ssl command [flags] [file/string]");
	else
	{
		parse_command(av[1]);
		while (i < ac)
		{
			if (av[i][0] == '-' && args.files[0] == NULL)
			{
				if (av[i][1] == 's' && i + 1 < ac)
					expect_string = 1;
				else
					parse_flags(av[i]);
			}
			else if (expect_string)
			{
				args.strings[args.num_strings++] = av[i];
				if (args.num_strings >= MAX_STRINGS)
					print_error_and_exit("too many strings.");
				expect_string = 0;
			}
			else
			{
				args.files[args.num_files++] = av[i];
				if (args.num_files >= MAX_FILES)
					print_error_and_exit("too many files.");
			}
			i++;
		}
		if (expect_string)
			print_error_and_exit("'-s' expect a string after it.");
	}
}
