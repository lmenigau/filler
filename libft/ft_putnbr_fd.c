/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 23:03:23 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/09 23:05:24 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		pow;
	int		neg;

	pow = 1;
	neg = 1;
	while (n / pow >= 10 || n / pow <= -10)
		pow *= 10;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		neg = -1;
	}
	while (pow)
	{
		ft_putchar_fd((neg * (n / pow)) + '0', fd);
		n %= pow;
		pow /= 10;
	}
}
