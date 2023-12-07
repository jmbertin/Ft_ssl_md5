#include "../includes/ft_ssl.h"

args_t	args = {0, 0, 0, 0, {}, 0, {}, 0};

/**
 * Processes hashing for the given arguments.
 * This function reads data from stdin, files, or strings as specified in the arguments,
 * computes their hashes using the selected hash function, and displays the results.
 * It handles file and string inputs, as well as direct stdin data.
 */
void	ft_hash(void)
{
	int				i = 0;
	size_t			size = 0;
	uint8_t			*file_content;
	hash_function_t	hash_function;

	switch (args.command)
	{
		case 1: hash_function = my_MD5; break;
		case 2: hash_function = my_SHA256; break;
		case 3: hash_function = my_WHIRLPOOL; break;
	}
	if (args.echo || (!args.num_strings && !args.num_files))
	{
		file_content = read_binary_file(NULL, &size);
		if (file_content)
		{
			char	*representation = hash_function(file_content, size);
			display_hash(representation, (char *)file_content, 1);
			free(representation);
		}
	}

	while (args.strings[i])
	{
		char *representation = hash_function((uint8_t *)args.strings[i], strlen(args.strings[i]));
		display_hash(representation, args.strings[i], 2);
		free(representation);
		i++;
	}

	i = 0;
	while (args.files[i])
	{
		file_content = read_binary_file(args.files[i], &size);
		if (file_content)
		{
			char *representation = hash_function(file_content, size);
			display_hash(representation, args.files[i], 3);
			free(representation);
		}
		free(file_content);
		i++;
	}
}

/**
 * The main function of the ft_ssl program.
 * This function initializes the program, processes command line arguments if provided,
 * and invokes the appropriate functions to handle hashing or command line interaction.
 *
 * @param ac Argument count.
 * @param av Argument vector (array of strings).
 * @return Returns 0 upon successful execution.
 */
int	main(int ac, char **av)
{
	if (ac == 1)
		ft_command_line();
	else
	{
		parse_args(ac, av);
		ft_hash();
	}

	return (0);
}
