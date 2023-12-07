#include "./libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*dest;

	dest = (void *)malloc(elementCount * elementSize);
	if (dest == 0 || elementCount == SIZE_MAX || elementSize == SIZE_MAX)
		return (NULL);
	ft_bzero(dest, elementCount * elementSize);
	return (dest);
}
