#include "./libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	unsigned char	*src;
	size_t			i;

	i = 0;
	src = (unsigned char *)memoryBlock;
	while (size--)
	{
		if (src[i] == (unsigned char)searchedChar)
			return (src + i);
		i++;
	}
	return (NULL);
}
