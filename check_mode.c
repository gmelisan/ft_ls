/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:55:06 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/26 17:25:19 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			is_dir(struct stat st)
{
	if ((st.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

int			is_link(struct stat st)
{
	if ((st.st_mode & S_IFMT) == S_IFLNK)
		return (1);
	return (0);
}

int			is_linkdir(t_name name)
{
	struct stat lst;

	bzero(&lst, sizeof(lst));
	if (is_link(name.st))
	{
		stat(name.name, &lst);
		if (is_dir(lst))
			return (1);
	}
	return (0);
}

int			is_device(struct stat st)
{
	return (((st.st_mode & S_IFMT) == S_IFBLK) ||
			((st.st_mode & S_IFMT) == S_IFCHR));
}
