/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 19:27:15 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/09 23:58:11 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_split(char const *s, char c, char **arr, size_t tw)
{
	size_t	i;
	size_t	wc;
	size_t	wb;

	i = 0;
	wb = 0;
	wc = 0;
	while (wc < tw)
	{
		while (s[wb] != '\0' && s[wb] == c)
			wb++;
		i = wb;
		while (s[i] != '\0' && s[i] != c)
			i++;
		if ((arr[wc] = ft_strsub(s, wb, i - wb)) == NULL)
			return (0);
		wc++;
		wb = i;
	}
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	wc;
	char	**arr;

	i = 0;
	wc = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != '\0' && s[i] != c)
			i++;
		wc++;
	}
	if ((arr = malloc(((wc + 1) * sizeof(*arr)))) == NULL)
		return (NULL);
	if (fill_split(s, c, arr, wc))
		arr[wc] = NULL;
	else
		return (NULL);
	return (arr);
}
