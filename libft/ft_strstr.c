/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 20:34:36 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/08 20:58:51 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	if (*big == '\0')
		return (NULL);
	while (big[i] != '\0')
	{
		while (big[i] && little[j] == big[i])
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
