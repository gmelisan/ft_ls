/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirwalk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:53:21 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/19 18:24:20 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	show_onecol(t_name *names, struct s_options options)
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

static void	show_longformat(t_name *names, struct s_options options)
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
		free(fullpath);
		i++;
	}
	len = i;
	sort_names(names, len, options);
	/* if (options.reverse) */
	/* ft_qsort(names, len, sizeof(*names), options.reverse ? cmp_rlex : cmp_lex); */
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
	if (options.long_format)
		show_longformat(names, options);
	else if (options.one_column)
		show_onecol(names, options);
	else
		show_onecol(names, options);
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
			if (is_dir(names[i]))
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
