/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:50:40 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/09 17:59:31 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joint;

	if ((joint = malloc(ft_strlen(s1) + ft_strlen(s2))) == NULL)
		return (NULL);
	return (ft_strcat(ft_strcpy(joint, s1), s2));
}
