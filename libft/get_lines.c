/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:07:22 by gmelisan          #+#    #+#             */
/*   Updated: 2018/12/21 19:30:58 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		strarr_del(char ***tab, int n)
{
	int		i;
	char	**t;

	t = *tab;
	i = 0;
	while (i < n)
	{
		ft_strdel(&(t[i]));
		i++;
	}
	ft_memdel((void **)tab);
}

int				get_lines(int fd, char ***lines, int n)
{
	int	i;
	int	ret;

	if (n <= 0 || fd < 0 || !lines)
		return (0);
	*lines = ft_memalloc(sizeof(**lines) * (n + 1));
	i = 0;
	while (i < n)
	{
		if ((ret = get_next_line(fd, *lines + i)) == 0)
			return (i);
		if (ret == -1)
		{
			strarr_del(lines, i - 1);
			return (-1);
		}
		i++;
	}
	return (i);
}
