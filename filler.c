/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 02:34:22 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/29 01:34:54 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_vec	find_enemy(t_map *map, char *map_buff, t_vec pos)
{
	char	(*buff)[map->size.x + 5];
	int		x;
	int		y;

	buff = (char (*)[])map_buff;
	y = 0;
	while (y + pos.y <= map->size.y || pos.y - y >= 0)
	{
		x = 0;
		while (x + pos.x <= map->size.x || pos.x - x >= 0)
		{
			if (pos.x - x >= 0 && pos.y - y >= 0 &&
					buff[pos.y - y + 1][pos.x - x + 4] == map->enemy_char)
				return ((t_vec){pos.x - x, pos.y - y});
			if (x + pos.x <= map->size.x && y + pos.y <= map->size.y
					&& buff[pos.y + y + 1][pos.x + x + 4] == map->enemy_char)
				return ((t_vec){x + pos.x, y + pos.y});
			x++;
		}
		y++;
	}
	return ((t_vec){0, 0});
}

int		read_piece(t_map *map, t_psize piece_size, size_t piece_length)
{
	char		piece_buff[piece_length];
	t_bound		bound;
	t_vec		answer;
	t_piece		piece;

	read_input((char *)&piece_buff, piece_length);
	piece.buff = piece_buff;
	piece.bound = normalise_piece(piece_buff, piece_size);
	answer = place(map, &piece);
	ft_putnbr(answer.y - bound.start.y);
	ft_putchar(' ');
	ft_putnbr(answer.x - bound.start.x);
	ft_putchar('\n');
	return (0);
}

int		play(t_map *map, size_t map_length, int firstround)
{
	char		map_buff[map_length];
	t_psize		piece_size;

	read_input((char *)&map_buff, map_length);
	bzero(map, map_length);
	piece_size = parse_header(sizeof("Piece"));
	map->buff = map_buff;
	if (!firstround)
		map->buff = map_buff + map->size.header_length;
	read_piece(map, piece_size, (piece_size.x + 1) * piece_size.y);
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
	map_size = parse_header(sizeof("Plateau"));
	map.size = map_size;
	map_length = map_size.header_length + (map_size.y + 1) * (map_size.x + 5);
	play(&map, (map_size.y + 1) * (map_size.x + 5), 1);
	while (42)
	{
		play(&map, map_length, 0);
	}
}
