/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:01:38 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/20 23:31:15 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		show_onecol(t_name *names, struct s_options options)
{
	int i;

	i = -1;
	while (names[++i].name)
		if (options.all || names[i].name[0] != '.')
		{
			ft_putstr(names[i].name);
			ft_putchar('\n');
		}
}

void			show(t_name *names, struct s_options options, int showtotal)
{
	if (options.long_format)
		show_long(names, options, showtotal);
	else if (options.one_column)
		show_onecol(names, options);
	else
		show_onecol(names, options);
}
