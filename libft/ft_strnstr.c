/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 21:00:38 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/08 21:02:42 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	if (*big == '\0')
		return (NULL);
	while (big[i] != '\0' && i < len)
	{
		while (big[i] && little[j] == big[i] && i < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i - j]);
			i++;
			j++;
		}
		i -= j;
		i++;
		j = 0;
	}
	return (NULL);
}
