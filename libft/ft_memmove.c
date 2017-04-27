/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:00:34 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/08 13:40:36 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*b;

	b = malloc(len);
	if (b == NULL)
		return (dst);
	ft_memcpy(b, src, len);
	ft_memcpy(dst, b, len);
	free(b);
	return (dst);
}
