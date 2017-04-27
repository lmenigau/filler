/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 02:34:22 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/27 10:59:11 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>
#include <fcntl.h>

int		read_input(char *buff, size_t max_read)
{
	int			ret;
	size_t		buff_end;

	buff_end = 0;
	ret = 0;
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
			if (piece_buff[y][x] == '*' && x > bound.size.x)
				bound.size.x = x;
			if (piece_buff[y][x] == '*')
				bound.size.y = y - bound.start.y + 1;
			x++;
		}
		y++;
	}
	bound.size.x = bound.size.x - bound.start.x + 1;
	return (bound);
}

int		check_placement(t_map *map, char *map_buff, char *piece_buff, t_pbound bound, t_psize piece_size, t_vec pos)
{
	char (*mbuff)[map->size.x + 5];
	char (*pbuff)[piece_size.x + 1];
	t_vec	curr;
	int		cover;
	char	mchar;

	cover = 0;
	mbuff = (char (*)[map->size.x + 5])map_buff;
	pbuff = (char (*)[])piece_buff;
	curr.y = 0;
	while (curr.y < bound.size.y && curr.y + pos.y <= map->size.y)
	{
		curr.x = 0;
		while (curr.x < bound.size.x && curr.x + pos.x <= map->size.x)
		{
			mchar = mbuff[pos.y + curr.y + 1][pos.x + curr.x + 4];
			if(pbuff[curr.y + bound.start.y][curr.x + bound.start.x] == '*' &&
					(mchar ==  map->player_char || mchar == map->player_char + 'a' - 'A') && !cover)
				cover = 1;
			else if (pbuff[curr.y + bound.start.y][curr.x + bound.start.x] == '*' && mchar != '.')
				return (0);
			curr.x++;
		}
		curr.y++;
	}
	if (cover != 1 || curr.x + pos.x > map->size.x || curr.y + pos.y > map->size.y)
		return (0);
	return (1);
}

int		ft_abs(int	nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

t_vec	find_enemy(t_map *map, char *map_buff, t_vec pos)
{
	char (*buff)[map->size.x + 5];
	int		x;
	int		y;

	buff = (char (*)[])map_buff;
	y = 0;
	while (y + pos.y <= map->size.y || pos.y - y >= 0)
	{
		x = 0;
		while (x + pos.x <= map->size.x || pos.x - x >= 0)
		{
			if(pos.x - x >= 0 &&  pos.y - y >= 0 && buff[pos.y - y + 1][pos.x - x + 4] == map->enemy_char)
				return ((t_vec){pos.x - x , pos.y - y});
			if(x + pos.x <= map->size.x && y + pos.y <= map->size.y
					&& buff[pos.y + y + 1][pos.x + x + 4] == map->enemy_char)
				return ((t_vec){x + pos.x, y + pos.y});
			x++;
		}
		y++;
	}
	return ((t_vec){0, 0});
}

t_vec		place(t_map *map, char *map_buff, char *piece_buff, t_pbound bound, t_psize piece_size)
{
	char (*buff)[map->size.x + 5];
	t_vec	pos;
	t_vec	min;
	int		dist;
	int		tmp;
	t_vec enemy_pos;

	min = (t_vec){0, 0};
	buff = (char (*)[])map_buff;
	pos.y = 0;
	dist = 30000;
	while (pos.y <= map->size.y)
	{
		pos.x = 0;
		while (pos.x <= map->size.x)
		{
			if (check_placement(map, map_buff, piece_buff, bound, piece_size,pos))
			{
				enemy_pos = find_enemy(map, map_buff, pos);
				tmp = ft_abs(pos.x - enemy_pos.x) + ft_abs(pos.y - enemy_pos.y);
				if (tmp > piece_size.x && pos.x < enemy_pos.x)
					tmp -= (piece_size.x);
				else if (enemy_pos.x - pos.x < piece_size.x && enemy_pos.x >= pos.x)
					tmp -= (enemy_pos.x - pos.x);
				if (tmp > piece_size.y && pos.y < enemy_pos.y)
					tmp -= (piece_size.y);
				else if (enemy_pos.y - pos.y < piece_size.y && enemy_pos.y >= pos.y)
					tmp -= (enemy_pos.y - pos.y);
				if (tmp < dist)
				{
					dist = tmp;
					min = pos;
				}
			}
			pos.x++;
		}
		pos.y++;
	}
	fprintf(stderr, "dist:%d, %d,%d\n", dist,enemy_pos.x, enemy_pos.y);
	return (min);
}

int		read_piece(t_map *map, char *buff, t_psize piece_size, size_t piece_length)
{
	char		piece_buff[piece_length];
	t_pbound	bound;
	//t_vec		enemy_pos;
	t_vec		answer;

	//write(2 buff, (map->size.y + 1) * (map->size.x + 5));
	//	fprintf(stderr, "(%zu)\n", piece_length);
	//	fprintf(stderr, "%d, %d\n", piece_size.x, piece_size.y);
	read_input((char *)&piece_buff, piece_length);
	//write(2, &piece_buff, piece_length);
	bound = normalise_piece(piece_buff, piece_size);
	//fprintf(stderr, "{%d, %d, %d, %d}\n",bound.start.x, bound.start.y, bound.size.x, bound.size.y);
	//enemy_pos = find_enemy(map, buff, (t_vec){0, 0});
	answer = place(map, buff, piece_buff, bound, piece_size);

	ft_putnbr(answer.y - bound.start.y);
	ft_putchar(' ');
	ft_putnbr(answer.x - bound.start.x);
	ft_putchar('\n');

	//	printf("%d %d\n", answer.x, answer.y);
	//	fflush(stdout);
	//fprintf(stderr, "%d %d\n", answer.x, answer.y);
	//fprintf(stderr, "%c\n", map->enemy_char);

//	if (map->enemy_char == 'O' || map->enemy_char == 'X')
//		map->enemy_char += 'a' - 'A';
	return (0);
}

int		play(t_map *map, size_t map_length, int firstround)
{
	char		map_buff[map_length];
	t_psize		piece_size;

	read_input((char *)&map_buff, map_length);
	bzero(map, map_length);
	//write(2, &map_buff, map_length);
	piece_size = parse_header(sizeof ("Piece"));
	if (firstround)
		read_piece(map, (char *)&map_buff , piece_size, (piece_size.x + 1) * piece_size.y);
	else
		read_piece(map, (char *)&map_buff + map->size.header_length, piece_size, (piece_size.x + 1) * piece_size.y);
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
	play(&map, (map_size.y + 1) * (map_size.x + 5), 1);
	while (42)
	{
//		fprintf(stderr,"\e[H\e[2J");
		play(&map, map_length, 0);
//		usleep(50000);
	}
}
