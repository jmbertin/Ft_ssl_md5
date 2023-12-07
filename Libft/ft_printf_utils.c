#include "./libft.h"

int	print_str(char *s, int fd)
{
	int		i;

	if (!s)
	{
		write (1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	print_char(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
