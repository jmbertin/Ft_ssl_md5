#include "./libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*s2;
	int		length;

	if (!s || !f)
		return (0);
	i = 0;
	length = ft_strlen(s);
	s2 = (char *)malloc(sizeof(char) * length + 1);
	if (s2 == 0)
		return (NULL);
	while (s[i])
	{
		s2[i] = f(i, s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
