#include "./libft.h"

int	ft_isalnum(int arg)
{
	if (ft_isalpha(arg) || ft_isdigit(arg))
		return (1);
	return (0);
}
