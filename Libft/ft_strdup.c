#include "./libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;

	i = ft_strlen(src);
	dest = (char *)malloc(sizeof(*dest) * (i + 1));
	if (dest == 0)
		return (0);
	ft_strlcpy(dest, src, i + 1);
	return (dest);
}
