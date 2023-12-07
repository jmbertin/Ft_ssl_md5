char	*ft_strchr(const char *string, int c)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	if ((char)c == string[i])
		return ((char *)string);
	while ((char)c != string[i])
	{
		if (!string[i])
			return (0);
		i++;
	}
	return ((char *)string + i);
}
