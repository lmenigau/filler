/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 02:34:22 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/22 06:51:59 by lmenigau         ###   ########.fr       */
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

char	read_player(t_map	*map)
{
	char	buff[34];

	read(0, &buff, 34);
	if (buff[10] == '1')
	{
		map->enemy_char='X';
			return ('O');
	}
	else
	{
		map->enemy_char='O';
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

t_pbound	normalise_piece(char *buff , t_psize piece_size)
{
	char (*piece_buff)[piece_size.x + 1];
	t_pbound	bound;
	int		x;
	int		y;

	bound = (t_pbound){{-1,-1},{-1, -1}};
	piece_buff = (char (*)[])buff;
	y = 0;
	while (y < piece_size.y)
	{
		x = 0;
		while (x < piece_size.x)
		{
			if (piece_buff[y][x] == '*' && bound.start.y == -1)
				bound.start = (t_vec){x, y};
			if (piece_buff[y][x] == '*' && x < bound.start.x)
				bound.start.x = x;
			if (piece_buff[y][x] == '*')
				bound.size = (t_vec){x - bound.start.x + 1, y - bound.start.y + 1};
			x++;
		}
		y++;
	}
	return (bound);
}

int		check_placement(t_map *map, char *map_buff, char *piece_buff, t_psize piece_size, t_vec pos)
{
	char (*buff)[map->size.x + 1];
	int		x;
	int		y;


	buff = (char (*)[])map_buff;
	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			if(buff[y][x] == map->enemy_char)
				return ((t_vec){x, y});
			x++;
		}
		y++;
	}
	return ((t_vec){0, 0});

	return (1);
}

t_vec		place(t_map *map, char *map_buff, char *piece_buff, t_psize piece_size)
{
	char (*buff)[map->size.x + 1];
	t_vec	pos;
	t_vec	min;

	buff = (char (*)[])map_buff;
	pos.y = 0;
	while (pos.y < map->size.y)
	{
		pos.x = 0;
		while (pos.x < map->size.x)
		{
			if(check_placement(map, map_buff, piece_buff, piece_size,pos))
				min = pos;
			pos.x++;
		}
		pos.y++;
	}
	return (min);
}

t_vec	find_enemy(t_map *map, char *map_buff)
{
	char (*buff)[map->size.x + 1];
	int		x;
	int		y;


	buff = (char (*)[])map_buff;
	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			if(buff[y][x] == map->enemy_char)
				return ((t_vec){x, y});
			x++;
		}
		y++;
	}
	return ((t_vec){0, 0});
}

int		read_piece(t_map *map, char *buff, t_psize piece_size, size_t piece_length)
{
	char		piece_buff[piece_length];
	t_pbound	bound;
	t_vec		enemy_pos;

	fprintf(stderr, "%zu\n", piece_length);
	fprintf(stderr, "%d, %d\n", piece_size.x, piece_size.y);
	read_input((char *)&piece_buff, piece_length);
	write(2, &piece_buff, piece_length);
	bound = normalise_piece(piece_buff, piece_size);
	enemy_pos = find_enemy(map, buff);
	if (map->enemy_char == 'O' || map->enemy_char== 'X')
		map->enemy_char -= 'A' - 'a';
	return (0);
}

int		play(t_map *map, size_t map_length)
{
	char		map_buff[map_length];
	t_psize		piece_size;

	read_input((char *)&map_buff, map_length);
	write(2, &map_buff, map_length);
	piece_size = parse_header(sizeof ("Piece"));
	read_piece(map, (char *)&map_buff, piece_size, (piece_size.x + 1) * piece_size.y);
	return (0);
}

int		main(void)
{
	t_map		map;
	t_psize		map_size;
	size_t		map_length;
	size_t		i;

	i = 0;
	map.player_char = read_player(&map);
	map_size = parse_header(sizeof ("Plateau"));
	map.size = map_size;
	map_length = map_size.header_length + (map_size.y + 1) * (map_size.x + 5);
	play(&map, (map_size.y + 1) * (map_size.x + 5));
	while (42)
	{
		play(&map, map_length);
	}
}
