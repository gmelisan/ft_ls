/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_long.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 22:29:57 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/24 04:36:42 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**            1         2
**  012345678901234567890123456
** "Wed Jun 30 21:49:08 1993\n" ->
** year_flag ? "Jun 30 21:49" : "Jun 30  1993"
*/

static char		*convert_time(char *str, int year_flag)
{
	char *res;
	int i;
	int len;

	res = ft_strnew(20);
	ft_memcpy(res, str + 4, 6);
	res[6] = ' ';
	if (year_flag)
	{
		i = 19;
		while (str[i] == ' ')
			i++;
		len = 0;
		while (str[i + len] != '\n' && str[i + len])
			len++;
		ft_memcpy(res + 7, str + i - 1, len + 1);
	}
	else
		ft_memcpy(res + 7, str + 11, 5);
	return (res);
}

static int		is_device(struct stat st)
{
	return (((st.st_mode & S_IFMT) == S_IFBLK) ||
			((st.st_mode & S_IFMT) == S_IFCHR));
}

/*
** Major/minor numbers:
**
** https://stackoverflow.com/questions/4309882/
** device-number-in-stat-command-output
** 
** https://stackoverflow.com/questions/35392291/
** how-to-convert-between-a-dev-t-and-major-minor-device-numbers
*/

static int		get_major(struct stat st)
{
	return ((int)(((t_uint)(st.st_rdev) >> 8) & 0xFF));
}

static int		get_minor(struct stat st)
{
	return ((int)((st.st_rdev) & 0xff));
}

static void		update_longest(t_name *names, int i, struct s_longest *longest)
{
	int		len;
	time_t	curtime;

	if (names[i].st.st_nlink > (t_ulint)longest->link)
		longest->link = names[i].st.st_nlink;
	if (names[i].st.st_size > longest->bytes)
			longest->bytes = names[i].st.st_size;
	curtime = time(NULL);
	if (ft_abs(curtime - names[i].st.st_mtime) < YEAR_BORDER)
		names[i].timestr = convert_time(ctime(&names[i].st.st_mtime), 0);
	else
		names[i].timestr = convert_time(ctime(&names[i].st.st_mtime), 1);
	len = ft_strlen(names[i].pw_name);
	if (len > longest->owner)
			longest->owner = len;
	len = ft_strlen(names[i].gr_name);
	if (len > longest->group)
		longest->group = len;
	if (is_device(names[i].st) && (get_major(names[i].st) > longest->sp_major))
		longest->sp_major = get_major(names[i].st);
	if (is_device(names[i].st) && (get_minor(names[i].st) > longest->sp_minor))
		longest->sp_minor = get_minor(names[i].st);
}

static struct s_longest	get_longest(t_name *names, struct s_options options,
								int *total)
{
	int					i;
	struct s_longest	longest;

	bzero((void *)&longest, sizeof(longest));
	i = -1;
	*total = 0;
	while (names[++i].name)
	{
		if (!(options.all || names[i].name[0] != '.'))
			continue ;
		update_longest(names, i, &longest);
		*total += names[i].st.st_blocks;
	}
	longest.link = ft_cntdigits(longest.link, 10);
	longest.bytes = ft_cntdigits(longest.bytes, 10);
	longest.sp_major = ft_cntdigits(longest.sp_major, 10);
	longest.sp_minor = ft_cntdigits(longest.sp_minor, 10);
	return (longest);
}

static void			fill_type(struct s_modechars *mc, struct stat st)
{
	if ((st.st_mode & S_IFMT) == S_IFREG)
		mc->type = '-';
	else if ((st.st_mode & S_IFMT) == S_IFBLK)
		mc->type = 'b';
	else if ((st.st_mode & S_IFMT) == S_IFCHR)
		mc->type = 'c';
	else if ((st.st_mode & S_IFMT) == S_IFDIR)
		mc->type = 'd';
	else if ((st.st_mode & S_IFMT) == S_IFLNK)
		mc->type = 'l';
	else if ((st.st_mode & S_IFMT) == S_IFIFO)
		mc->type = 'p';
	else if ((st.st_mode & S_IFMT) == S_IFSOCK)
		mc->type = 's';
	/* else if ((st.st_mode & S_IFMT) == S_IFWHT) */
	/* 	mc->type = 'w'; */
}

static void			fill_modechars(struct s_modechars *mc, struct stat st)
{
	fill_type(mc, st);
	mc->ur = (st.st_mode & S_IRUSR ? 'r' : '-');
	mc->uw = (st.st_mode & S_IWUSR ? 'w' : '-');
	mc->ux = (st.st_mode & S_IXUSR ? 'x' : '-');
	mc->gr = (st.st_mode & S_IRGRP ? 'r' : '-');
	mc->gw = (st.st_mode & S_IWGRP ? 'w' : '-');
	mc->gx = (st.st_mode & S_IXGRP ? 'x' : '-');
	mc->or = (st.st_mode & S_IROTH ? 'r' : '-');
	mc->ow = (st.st_mode & S_IWOTH ? 'w' : '-');
	mc->ox = (st.st_mode & S_IXOTH ? 'x' : '-');
	mc->att = ' ';
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

static void			show_long_one(t_name *names, int i,
									struct s_longest longest)
{
	struct s_modechars	mc;

	bzero((void *)&mc, sizeof(mc));
	fill_modechars(&mc, names[i].st);
	ft_printf("%c%c%c%c%c%c%c%c%c%c%c", mc.type,
		mc.ur, mc.uw, mc.ux, mc.gr, mc.gw, mc.gx, mc.or, mc.ow, mc.ox, mc.att);
	ft_printf(" %*d", longest.link, names[i].st.st_nlink);
	ft_printf(" %*s", longest.owner, names[i].pw_name);
	ft_printf("  %-*s", longest.group, names[i].gr_name);
	if (is_device(names[i].st))
	{
		ft_printf("  %*d,", longest.sp_major, get_major(names[i].st));
		ft_printf(" %*d", longest.sp_minor, get_minor(names[i].st));
	}
	else
		ft_printf("  %*d", longest.bytes, names[i].st.st_size);
	ft_printf(" %s", names[i].timestr);
	ft_printf(" %s", names[i].name);
	if (names[i].link)
		ft_printf(" -> %s", names[i].link);
	ft_putchar('\n');
	/* ft_printf(" (%s)", ctime(&(names[i].st.st_mtime))); */
}

void				show_long(t_name *names, struct s_options options,
								int showtotal)
{
	int					i;
	struct s_longest	longest;
	int					total;
	
	longest = get_longest(names, options, &total);
	if (showtotal)
		ft_printf("total %d\n", total);
	i = -1;
	while (names[++i].name)
	{
		if (!names[i].st.st_ino)
			continue ;
		if (options.all || names[i].name[0] != '.')
			show_long_one(names, i, longest);
	}
}
