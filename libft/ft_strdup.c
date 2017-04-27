/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 13:44:59 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/08 13:56:47 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*buff;

	buff = malloc(ft_strlen(s1) + 1);
	if (buff == NULL)
		return (NULL);
	ft_strcpy(buff, s1);
	return (buff);
}
