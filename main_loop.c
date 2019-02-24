/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:35:40 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/24 01:55:56 by gmelisan         ###   ########.fr       */
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

static void	prepare(t_name *names, struct s_options options, int *fc, int *dc)
{
	int i;

	i = 0;
	*fc = 0;
	sort_lex(names);
	while (names[i].name)
	{
		if (options.long_format && lstat(names[i].name, &(names[i].st)) == -1)
			error_common(names[i].name);
		else if (stat(names[i].name, &(names[i].st)) == -1)
			error_common(names[i].name);
		if (is_link(names[i].st))
		{
			names[i].link = ft_memalloc(LINK_BUFSIZE);
			readlink(names[i].name, names[i].link, LINK_BUFSIZE - 1);
		}
		if (options.long_format)
			get_usergroup(&names[i]);
		if (!is_dir(names[i].st))
			(*fc)++;
		i++;
	}
	sort_names(names, options);
	*dc = i;
}

static t_name		*get_files(t_name *names, int len)
{
	t_name	*files;
	int		i;
	int		j;

	files = ft_memalloc(sizeof(*files) * (len + 1));
	i = -1;
	j = -1;
	while (names[++i].name)
		if (!is_dir(names[i].st))
			files[++j] = names[i];
	return (files);
}

void		main_loop(t_name *names, struct s_options options)
{
	int		i;
	int		filecount;
	int		dircount;
	t_name	*files;
	int		first;

	prepare(names, options, &filecount, &dircount);
	if (filecount)
	{
		files = get_files(names, filecount);
		show(files, options, 0);
		free(files);
	}
	i = -1;
	first = 1;
	while (names[++i].name)
		if (is_dir(names[i].st))
		{
			if (dircount > 1)
				ft_printf(first && !filecount ? "%s:\n" : "\n%s:\n", names[i].name);
			first = 0;
			dirwalk(names[i].name, names[i].name, options);
		}
}
