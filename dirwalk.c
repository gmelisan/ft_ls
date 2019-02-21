/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirwalk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:53:21 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/21 01:08:09 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_name		*get_names(DIR *dir)
{
	struct dirent	*ent;
	t_name			*names;
	int				i;
	int				size;

	size = 100;
	names = ft_memalloc(sizeof(*names) * size);
	i = 0;
	while ((ent = readdir(dir)))
	{
		if (i == size - 2)
		{
			size *= 2;
			ft_realloc((void **)&names, sizeof(*names) * i,
										sizeof(*names) * size);
		}
		names[i].name = ft_strdup(ent->d_name);
		i++;
	}
	return (names);
}

void		get_usergroup(t_name *name)
{
	struct passwd	*pw;
	struct group	*gr;

	pw = getpwuid(name->st.st_uid);
	if (!pw->pw_name)
		name->pw_name = ft_itoa(name->st.st_uid);
	else
		name->pw_name = ft_strdup(pw->pw_name);
	gr = getgrgid(name->st.st_gid);
	if (!gr->gr_name)
		name->gr_name = ft_itoa(name->st.st_gid);
	else
		name->gr_name = ft_strdup(gr->gr_name);
}

static void	prepare(char *path, t_name *names, struct s_options options)
{
	int i;
	int len;
	char *fullpath;

	i = 0;
	while (names[i].name)
	{
		fullpath = ft_strnjoin(3, path, "/", names[i].name);
		lstat(fullpath, &(names[i].st));
		if (is_link(names[i].st))
		{
			names[i].link = ft_memalloc(LINK_BUFSIZE);
			readlink(fullpath, names[i].link, LINK_BUFSIZE - 1);
		}
		free(fullpath);
		if (options.long_format)
			get_usergroup(&names[i]);
		i++;
	}
	len = i;
	sort_names(names, len, options);
}

static t_name	*get_and_show(char *path, char *filename, struct s_options options)
{
	t_name		*names;
	DIR			*dir;

	if (!(dir = opendir(path)))
	{
		error_common(filename);
		return (NULL);
	}
	names = get_names(dir);
	closedir(dir);
	prepare(path, names, options);
	show(names, options, 1);
	return (names);
}

void		dirwalk(char *path, char *filename, struct s_options options)
{
	t_name	*names;
	char	*newpath;
	int		i;

	names = get_and_show(path, filename, options);
	if (!names)
		return ;
	i = -1;
	if (options.recursive)
		while (names[++i].name)
		{
			if (is_dir(names[i].st))
			{
				if (ft_strequ(names[i].name, ".") || ft_strequ(names[i].name, "..") ||
					!(options.all || names[i].name[0] != '.'))
					continue ;
				newpath = ft_strnjoin(3, path, "/", names[i].name);
				ft_printf("\n%s:\n", newpath);
				dirwalk(newpath, names[i].name, options);
				free(newpath);
			}
		}
	clear_names(&names);
}
