/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 03:35:09 by lmenigau          #+#    #+#             */
/*   Updated: 2016/12/10 08:49:32 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memjoin(char *s1, char *s2, size_t size1, size_t size2)
{
	char	*joint;

	if ((joint = malloc(size1 + size2)) == NULL)
		return (NULL);
	ft_memcpy(joint, s1, size1);
	ft_memcpy(joint + size1, s2, size2);
	return (joint);
}
