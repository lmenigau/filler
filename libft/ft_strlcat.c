/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 19:33:14 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/08 20:19:46 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t	len;

	len = ft_strlen(s1);
	if (size > len + 1)
	{
		ft_memccpy(ft_memchr(s1, '\0', size), s2, '\0', size - len - 1);
		s1[size - 1] = '\0';
		return (len + ft_strlen(s2));
	}
	return (size + ft_strlen(s2));
}
