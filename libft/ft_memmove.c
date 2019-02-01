/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:39:38 by gmelisan          #+#    #+#             */
/*   Updated: 2018/11/27 17:25:27 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** check_src_pos(void *dst, const void *src, size_t len)
** Checks dst for overlapping src
** Returns 1 if src on the left of dst and they're overlapped,
** else 0.
*/

static int	check_src_pos(void *dst, const void *src, size_t len)
{
	size_t	i;
	t_uchar	*cdst;
	t_uchar *csrc;

	cdst = (t_uchar *)dst;
	csrc = (t_uchar *)src;
	i = 0;
	while (i < len)
		if (&csrc[i++] == cdst)
			return (1);
	return (0);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	t_uchar	*cdst;
	t_uchar *csrc;

	cdst = (t_uchar *)dst;
	csrc = (t_uchar *)src;
	if (check_src_pos(dst, src, len))
	{
		i = len - 1;
		while (i >= 0)
		{
			cdst[i] = csrc[i];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
