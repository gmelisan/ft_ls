/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_long.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 22:29:57 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/26 17:29:00 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

static void			show_long_one(t_name *names, int i,
									struct s_longest longest)
{
	struct s_modechars	mc;

	bzero((void *)&mc, sizeof(mc));
	fill_modechars(&mc, names[i].st);
	mc.xattr = (names[i].xattr > 0 ? '@' : ' ');
	ft_printf("%c%c%c%c%c%c%c%c%c%c%c", mc.type,
		mc.ur, mc.uw, mc.ux, mc.gr, mc.gw, mc.gx, mc.or, mc.ow, mc.ox,
		mc.xattr);
	ft_printf(" %*d", longest.link, names[i].st.st_nlink);
	ft_printf(" %-*s", longest.owner, names[i].pw_name);
	ft_printf("  %-*s", longest.group, names[i].gr_name);
	if (is_device(names[i].st))
	{
		ft_printf(" %*d,", 4, get_major(names[i].st));
		ft_printf("%*d", 4, get_minor(names[i].st));
	}
	else
		ft_printf("  %*d", longest.bytes, names[i].st.st_size);
	ft_printf(" %s", names[i].timestr);
	ft_printf(" %s", names[i].name);
	if (names[i].link)
		ft_printf(" -> %s", names[i].link);
	ft_putchar('\n');
}

void				show_long(t_name *names, struct s_options options,
								int showtotal)
{
	int					i;
	struct s_longest	longest;
	int					total;

	longest = get_longest(names, options, &total);
	if (showtotal && names[0].name)
		ft_printf("total %d\n", total);
	i = -1;
	while (names[++i].name)
	{
		if (!names[i].st.st_ino)
			continue ;
		show_long_one(names, i, longest);
	}
}
