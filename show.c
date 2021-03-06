/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:01:38 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/26 16:49:27 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		show_onecol(t_name *names)
{
	int i;

	i = -1;
	while (names[++i].name)
	{
		if (!names[i].st.st_ino)
			continue ;
		ft_printf("%s\n", names[i].name);
	}
}

void			show(t_name *names, struct s_options options, int showtotal)
{
	if (options.long_format)
		show_long(names, options, showtotal);
	else if (options.one_column)
		show_onecol(names);
	else
		show_onecol(names);
}
