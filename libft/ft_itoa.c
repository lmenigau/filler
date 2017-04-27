/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 21:10:39 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/10 12:10:17 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		pow;
	int		len;
	char	*str;

	len = 1;
	pow = n;
	while (pow /= 10)
		len++;
	if (n < 0)
		len++;
	else
		n = -n;
	if ((str = malloc(len + 1)) == NULL)
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len] = -(n % 10) + '0';
		n /= 10;
		if (n == 0 && len == 1)
			str[--len] = '-';
		len--;
	}
	return (str);
}
