/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 15:11:00 by lmenigau          #+#    #+#             */
/*   Updated: 2016/11/10 15:11:00 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;

	if ((node = malloc(sizeof(*node))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		node->content_size = 0;
		node->content = NULL;
	}
	else
	{
		if ((node->content = malloc(content_size)) == NULL)
			return (NULL);
		ft_memcpy(node->content, content, content_size);
		node->content_size = content_size;
	}
	node->next = NULL;
	return (node);
}
