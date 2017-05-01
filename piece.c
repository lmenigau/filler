/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 01:24:18 by lmenigau          #+#    #+#             */
/*   Updated: 2017/05/02 01:12:22 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_bound	normalise_piece(char *buff, t_psize piece_size)
{
	char		(*piece_buff)[piece_size.x + 1];
	t_bound		bound;
	int			x;
	int			y;

	bound = (t_bound){{-1, -1}, {-1, -1}};
	piece_buff = (char (*)[])buff;
	y = -1;
	while (++y < piece_size.y)
	{
		x = -1;
		while (++x < piece_size.x)
		{
			if (piece_buff[y][x] == '*' && bound.start.y == -1)
				bound.start = (t_vec){x, y};
			if (piece_buff[y][x] == '*' && x < bound.start.x)
				bound.start.x = x;
			if (piece_buff[y][x] == '*' && x > bound.size.x)
				bound.size.x = x;
			if (piece_buff[y][x] == '*')
				bound.size.y = y - bound.start.y + 1;
		}
	}
	bound.size.x = bound.size.x - bound.start.x + 1;
	return (bound);
}

int		check_placement(t_map *map, t_piece *piece, t_bound info, int *cover)
{
	char	(*mbuff)[map->size.x + 5];
	char	(*pbuff)[piece->size.x + 1];
	t_vec	start;
	char	mchar;
	char	pchar;

	start = piece->bound.start;
	mbuff = (char (*)[])map->buff;
	pbuff = (char (*)[])piece->buff;
	mchar = mbuff[info.size.y + info.start.y + 1]
		[info.size.x + info.start.x + 4];
	pchar = pbuff[info.start.y + start.y][info.start.x + start.x];
	if (pchar == '*' && mchar == map->player_char && (*cover) == 0)
		(*cover)++;
	else if (pchar == '*' && mchar != '.')
		return (0);
	return (1);
}

int		iter_piece(t_map *map, t_piece *piece, t_vec pos)
{
	t_vec	curr;
	int		cover;
	t_bound	info;

	cover = 0;
	curr.y = 0;
	info.size = pos;
	while (curr.y < piece->bound.size.y && curr.y + pos.y <= map->size.y)
	{
		curr.x = 0;
		while (curr.x < piece->bound.size.x && curr.x + pos.x <= map->size.x)
		{
			info.start = curr;
			if (check_placement(map, piece, info, &cover) == 0)
				return (0);
			curr.x++;
		}
		curr.y++;
	}
	if (cover != 1
			|| curr.x + pos.x > map->size.x || curr.y + pos.y > map->size.y)
		return (0);
	return (1);
}
