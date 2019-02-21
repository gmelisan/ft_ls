/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:35:40 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/21 01:03:14 by gmelisan         ###   ########.fr       */
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

static void	prepare(t_name *names, struct s_options options, int *fc, int *dc)
{
	int i;
	int len;

	i = 0;
	*fc = 0;
	while (names[i].name)
	{
		if (lstat(names[i].name, &(names[i].st)) == -1)
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
	len = i;
	sort_names(names, len, options);
	*dc = len;
}

t_name		*get_files(t_name *names, int len)
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

	prepare(names, options, &filecount, &dircount);
	if (filecount)
	{
		files = get_files(names, filecount);
		show(files, options, 0);
		clear_names(&files);
	}
	i = -1;
	while (names[++i].name)
		if (is_dir(names[i].st))
		{
			if (dircount > 1)
				ft_printf("%s:\n", names[i].name);
			dirwalk(names[i].name, names[i].name, options);
			if (names[i + 1].name)
				ft_putchar('\n');
		}
}
