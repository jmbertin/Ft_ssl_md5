#include "./libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	int	end;

	end = ft_strlen(string);
	searchedChar = (unsigned char) searchedChar;
	while (end >= 0)
	{
		if (string[end] == searchedChar)
			return ((char *)string + end);
		end--;
	}
	return (0);
}
