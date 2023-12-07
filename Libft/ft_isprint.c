int	ft_isprint(int character)
{
	if (character < 32 || character > 126)
		return (0);
	return (1);
}
