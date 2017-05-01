/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 01:19:49 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/29 03:57:25 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		read_input(char *buff, size_t max_read)
{
	int			ret;
	size_t		buff_end;

	buff_end = 0;
	ret = 0;
	while ((ret = read(0, &buff[buff_end], max_read)) > 0)
	{
		buff_end += ret;
		max_read -= ret;
	}
	return (0);
}

char	read_player(t_map *map)
{
	char		buff[1024];
	size_t		index;

	index = 0;
	while (index < 1024 && read(0, &buff[index], 1))
	{
		if (buff[index] == '\n')
			break ;
		index++;
	}
	if (buff[10] == '1')
	{
		map->enemy_char = 'X';
		return ('O');
	}
	else
	{
		map->enemy_char = 'O';
		return ('X');
	}
}

int		parse_number(const char *str, size_t *index)
{
	int		i;
	int		neg;
	int		nb;

	neg = 1;
	nb = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (neg == -1)
			nb = nb * 10 - (str[i] - '0');
		else
			nb = nb * 10 + (str[i] - '0');
		i++;
	}
	*index += i - 1;
	return (nb);
}

t_psize	parse_header(size_t offset)
{
	char		buff[32];
	size_t		index;
	t_psize		header_size;

	index = 0;
	while (index < 32 && read(0, &buff[index], 1))
	{
		if (buff[index] == '\n')
			break ;
		index++;
	}
	header_size.header_length = index + 1;
	header_size.y = parse_number(&buff[offset], &offset);
	header_size.x = parse_number(&buff[offset + 1], &offset);
	return (header_size);
}
