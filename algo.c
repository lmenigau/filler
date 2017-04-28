/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 01:27:11 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/29 01:36:24 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

int		dist_magic(t_piece *piece, t_vec enemy_pos, t_vec pos, int dist)
{
	int		tmp;

	tmp = ft_abs(pos.x - enemy_pos.x) + ft_abs(pos.y - enemy_pos.y);
	if (tmp > piece->size.x && pos.x < enemy_pos.x)
		tmp -= (piece->size.x);
	else if (enemy_pos.x - pos.x < piece->size.x && enemy_pos.x >= pos.x)
		tmp -= (enemy_pos.x - pos.x);
	if (tmp > piece->size.y && pos.y < enemy_pos.y)
		tmp -= (piece->size.y);
	else if (enemy_pos.y - pos.y < piece->size.y && enemy_pos.y >= pos.y)
		tmp -= (enemy_pos.y - pos.y);
	if (tmp < dist)
		return (tmp);
	return (dist);
}

t_vec	place(t_map *map, t_piece *piece)
{
	char	(*buff)[map->size.x + 5];
	t_vec	pos;
	t_vec	min;
	int		dist;
	t_vec	enemy_pos;

	min = (t_vec){0, 0};
	buff = (char (*)[])map->buff;
	pos.y = 0;
	dist = 30000;
	while (pos.y <= map->size.y)
	{
		pos.x = 0;
		while (pos.x <= map->size.x)
		{
			if (iter_piece(map, piece, pos))
			{
				enemy_pos = find_enemy(map, map->buff, pos);
				dist = dist_magic(piece, enemy_pos, pos, dist);
			}
			pos.x++;
		}
		pos.y++;
	}
	return (min);
}
