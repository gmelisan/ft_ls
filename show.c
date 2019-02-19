/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:01:38 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/19 20:48:23 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	show_onecol(t_name *names, struct s_options options)
{
	int i;

	i = 0;
	while (names[i].name)
	{
		if (options.all || names[i].name[0] != '.')
			ft_printf("%s\n", names[i].name);
		i++;
	}
}

/*
** -rwxrwxrwx@ 24 root  wheel  23451 Jan 23 15:27 filename -> link
** (. stands for space)
** [10] filemode
** [1] xattr (@ or +)
** [.]
** [n] links
** [.]
** [n] owner (id if missing)
** [..]
** [n] group (id if missing)
** [..]
** [n] bytes, for s/b: [.a,.b]
** [.]
** [3] month
** [.]
** [2] day
** [.]
** [4/5] time/year
** [.]
** [n] filename -> link
*/

int		getmaxlen_links(t_name *names)
{
	int i;
	int max;

	i = 0;
	while (names[i].name)
}

void	show_longformat(t_name *names, struct s_options options)
{
	int i;

	i = 0;
	while (names[i].name)
	{
		if (options.all || names[i].name[0] != '.')
		{
			ft_printf("%-30s, time = %ld\n", names[i].name, names[i].st.st_mtime);
		}
		i++;
	}
}
