int	ft_isalpha(int arg)
{
	if (arg < 65 || (arg > 90 && arg < 97) || arg > 122)
		return (0);
	return (1);
}
