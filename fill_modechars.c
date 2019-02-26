/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_modechars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:19:23 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/26 17:26:51 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
}

static void			fill_modechars_stx(struct s_modechars *mc, struct stat st)
{
	if (!(st.st_mode & S_IXUSR) && (st.st_mode & S_ISUID))
		mc->ux = 'S';
	else if ((st.st_mode & S_IXUSR) && (st.st_mode & S_ISUID))
		mc->ux = 's';
	if (!(st.st_mode & S_IXGRP) && (st.st_mode & S_ISGID))
		mc->gx = 'S';
	else if ((st.st_mode & S_IXGRP) && (st.st_mode & S_ISGID))
		mc->gx = 's';
	if (!(st.st_mode & S_IXOTH) && (st.st_mode & S_ISVTX))
		mc->ox = 'T';
	else if ((st.st_mode & S_IXOTH) && (st.st_mode & S_ISVTX))
		mc->ox = 't';
}

void				fill_modechars(struct s_modechars *mc, struct stat st)
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
	fill_modechars_stx(mc, st);
}
