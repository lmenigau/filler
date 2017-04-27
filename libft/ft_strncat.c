/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:32:10 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/10 11:13:13 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*end;

	end = ft_strchr(s1, '\0');
	if (ft_memccpy(end, s2, '\0', n) == NULL)
		*(end + n) = '\0';
	return (s1);
}
