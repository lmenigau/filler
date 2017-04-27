/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:57:32 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/09 18:15:51 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*st1;
	const unsigned char	*st2;
	size_t				i;

	if (n == 0)
		return (0);
	st1 = s1;
	st2 = s2;
	i = 0;
	while (i < n - 1 && st1[i] == st2[i])
		i++;
	return (st1[i] - st2[i]);
}
