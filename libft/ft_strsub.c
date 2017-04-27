/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:32:59 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/10 11:09:40 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*cpy;

	if ((cpy = malloc(len + 1)) == NULL)
		return (NULL);
	ft_memcpy(cpy, s + start, len);
	cpy[len] = '\0';
	return (cpy);
}
