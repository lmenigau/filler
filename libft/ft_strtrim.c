/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:00:06 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/09 19:26:10 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	i;
	size_t	start;

	i = 0;
	len = ft_strlen(s);
	while (i < len && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	start = i;
	i = len - 1;
	while (i > start && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i--;
	return (ft_strsub(s, start, len - start - (len - 1 - i)));
}
