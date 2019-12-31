int		ft_putchar(char c);

void	putnbr(int nb)
{
	int nbr;

	if (nb < 0)
	{
		ft_putchar('-');
		if (nb < -2000000000)
		{
			ft_putchar('2');
			nb = nb + 2000000000;
		}
		nb = nb * -1;
	}
	if (nb >= 10)
	{
		putnbr(nb / 10);
	}
	nbr = nb % 10;
	ft_putchar(nbr + '0');
}
