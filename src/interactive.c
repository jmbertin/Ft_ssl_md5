#include "../includes/ft_ssl.h"

extern args_t	args;

/**
 * Frees allocated memory and exits if necessary.
 * This function is used to free the memory allocated for the line and args_cli,
 * and exits the program if the 'must_exit' flag is set.
 *
 * @param line Pointer to the line that needs to be freed.
 * @param args_cli Pointer to the array of arguments that needs to be freed.
 * @param must_exit Flag indicating whether to exit the program (1) or not (0).
 */
static void	free_interactive(char *line, char **args_cli, int must_exit)
{
	int	i = 0;
	while (args_cli[i])
	{
		free(args_cli[i]);
		i++;
	}
	free(args_cli);
	free(line);
	if (must_exit)
		exit(0);
}

/**
 * Counts the number of arguments and removes the return character.
 * This function iterates through the args_cli array, processes each argument
 * to remove the return character, and counts the total number of arguments.
 *
 * @param args_cli Pointer to the array of arguments.
 * @return The count of arguments in the args_cli array.
 */
static int	count_args_and_remove_return(char **args_cli)
{
	int	i = 0;
	while (args_cli[i])
	{
		remove_return(args_cli[i]);
		i++;
	}
	return (i);
}

/**
 * Checks if the given algorithm is authorized.
 * This function compares the provided algorithm name with the allowed
 * algorithm names (md5, sha256, whirlpool) and returns a status.
 *
 * @param algo Pointer to the string representing the algorithm name.
 * @return 1 if the algorithm is authorized, 0 otherwise.
 */
static int	check_autorised_algo(char *algo)
{
	if (ft_strlen(algo) == 3 && ft_strncmp(algo, "md5", 3) == 0)
		return (1);
	else if (ft_strlen(algo) == 6 && ft_strncmp(algo, "sha256", 6) == 0)
		return (1);
	else if (ft_strlen(algo) == 9 && ft_strncmp(algo, "whirlpool", 9) == 0)
		return (1);
	return (0);
}

/**
 * Handles the execution of the 'execute' command.
 * This function checks if the specified algorithm is authorized and processes the command
 * arguments. It calls ft_hash to perform hashing if valid input is provided.
 *
 * @param args_cli Array of command-line arguments.
 * @param nb_args Number of arguments in args_cli.
 */
static void	handle_execute_command(char **args_cli, int nb_args)
{
	if (!check_autorised_algo(args_cli[1]))
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid algorithm (use md5, sha256 or whirlpool).\n", args_cli[1]);
		return;
	}

	parse_args(nb_args, args_cli);
	if (args.num_strings == 0 && args.num_files == 0)
		ft_printf("ft_ssl: Error: no input specified. In interactive mode you must specify a file or a string.\n");
	else
		ft_hash();
}

/**
 * Processes a single command line input.
 * This function splits the input line into arguments, counts them, and determines
 * the appropriate action based on the command (exit, execute, etc.). It handles
 * the execution of commands and the printing of relevant error messages.
 *
 * @param line The command line input to be processed.
 */
static void	process_command(char *line)
{
	char	**args_cli = ft_split(line, ' ');
	int		nb_args = count_args_and_remove_return(args_cli);

	if (ft_strncmp(args_cli[0], "exit", 5) == 0)
		free_interactive(line, args_cli, 1);
	else if (ft_strncmp(args_cli[0], "execute", 8) == 0)
	{
		if (nb_args > 1)
			handle_execute_command(args_cli, nb_args);
		else
			ft_printf("ft_ssl: Error: no algorithm specified.\n");
	}
	else
		ft_printf("ft_ssl: Error: '%s' is an invalid command (use execute or exit).\n", args_cli[0]);

	free_interactive(line, args_cli, 0);
}

/**
 * Main command line interface for the ft_ssl program.
 * This function provides an interactive command line interface, continuously
 * reading user input and processing commands until an exit command is received.
 */
void	ft_command_line(void)
{
	char *line;

	ft_printf("Usage: [command] [algo] [options]\n");
	ft_printf("Commands: exit, execute\n");
	while (1)
	{
		ft_printf("ft_ssl> ");
		line = get_next_line(0);
		if (!line)
			break;

		process_command(line);
	}
}
