/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:35:40 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/18 20:06:42 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			is_dir(t_name name)
{
	if ((name.st.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

int			is_link(t_name name)
{
	if ((name.st.st_mode & S_IFMT) == S_IFLNK)
		return (1);
	return (0);
}

static int	prepare(t_name *names)
{
	int i;
	int dir_count;

	dir_count = 0;
	i = 0;
	while (names[i].name)
	{
		if (names[i].st.st_dev && !is_dir(names[i]))
			ft_printf("%s\n", names[i].name);
		else
			dir_count++;		
		i++;
	}
	return (dir_count);
}

void		main_loop(t_name *names, struct s_options options)
{
	int i;
	int dir_count;

	i = 0;
	dir_count = prepare(names);
	while (names[i].name)
	{
		if (is_dir(names[i]))
		{
			/* if (dir_count > 1) */
			/* 	ft_printf("%s:\n", names[i].name); */
			/* show_dir("", names[i].name, options); */
			/* if (dir_count > 1 && names[i + 1].name) */
			/* 	ft_printf("\n"); */
			dirwalk(names[i].name, options);
		}
		i++;
	}
}
