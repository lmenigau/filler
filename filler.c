/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 02:34:22 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/19 23:16:01 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>
#include <fcntl.h>

int		read_input(char *buff, size_t max_read)
{
	ssize_t		ret;
	size_t		buff_end;

	buff_end = 0;

	while  ((ret = read(0, &buff[buff_end], max_read)) > 0)
	{
		buff_end += ret;
		max_read -= ret;
	}
	return (0);
}

char	read_player()
{
	char	buff[34];

	read(0, &buff, 34);
	if (buff[10] == '1')
			return ('O');
	return ('X');
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

t_psize		parse_header(size_t	offset)
{
	char		buff[32];
	size_t		index;
	t_psize		header_size;

	index = 0;
	while (read(0, &buff[index], 1) && index < 32)
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

int		read_piece(t_map *map, char *buff, size_t piece_length)
{
	char		piece_buff[piece_length];

	fprintf(stderr, "%zu\n", piece_length);
	read_input((char *)&piece_buff, piece_length);
	write(2, &piece_buff, piece_length);
	return (0);
}

int		play(t_map *map, size_t map_length)
{
	char		map_buff[map_length];
	t_psize		piece_size;

	read_input((char *)&map_buff, map_length);
	write(2, &map_buff, map_length);
	piece_size = parse_header(sizeof ("Piece"));
	read_piece(map, (char *)&map_buff, (piece_size.x + 1) * piece_size.y);
	return (0);
}

int		main(void)
{
	t_map		map;
	t_psize		map_size;
	size_t		map_length;
	size_t		i;

	i = 0;
	map.player_char = read_player();
	map_size = parse_header(sizeof ("Plateau"));
	map.size = map_size;
	map_length = map_size.header_length + (map_size.y + 1) * (map_size.x + 5);
	play(&map, (map_size.y + 1) * (map_size.x + 5));
	while (42)
	{
		play(&map, map_length);
	}
}
