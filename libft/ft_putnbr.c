/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 23:00:56 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/09 23:04:53 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int		pow;
	int		neg;

	pow = 1;
	neg = 1;
	while (n / pow >= 10 || n / pow <= -10)
		pow *= 10;
	if (n < 0)
	{
		ft_putchar('-');
		neg = -1;
	}
	while (pow)
	{
		ft_putchar((neg * (n / pow)) + '0');
		n %= pow;
		pow /= 10;
	}
}
