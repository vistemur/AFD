int		ft_putchar(char c);

void	putstr(char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0')
	{
		ft_putchar(str[len]);
		len++;
	}
}
