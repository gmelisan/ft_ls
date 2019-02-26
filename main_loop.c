/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:35:40 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/26 16:58:35 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		getstat(t_name *names, int i, struct s_options options)
{
	int ret;

	if (options.long_format)
	{
		ret = lstat(names[i].name, &(names[i].st));
		if (ret == -1)
			error_common(names[i].name);
	}
	else
	{
		ret = stat(names[i].name, &(names[i].st));
		if (ret == -1)
		{
			ret = lstat(names[i].name, &(names[i].st));
			if (ret == -1)
				error_common(names[i].name);
		}
	}
}

static void		prepare(t_name *names, struct s_options options,
						int *fc, int *dc)
{
	int i;

	i = 0;
	*fc = 0;
	sort_lex(names);
	while (names[i].name)
	{
		getstat(names, i, options);
		if (is_link(names[i].st))
		{
			names[i].link = ft_memalloc(LINK_BUFSIZE);
			readlink(names[i].name, names[i].link, LINK_BUFSIZE - 1);
		}
		names[i].xattr = listxattr(names[i].name, NULL, 0, XATTR_NOFOLLOW);
		if (options.long_format)
			get_usergroup(&names[i]);
		if (!is_dir(names[i].st))
			(*fc)++;
		i++;
	}
	sort_names(names, options);
	*dc = i;
}

static t_name	*get_files(t_name *names, int len)
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

void			main_loop(t_name *names, struct s_options options)
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
				ft_printf(first && !filecount ?
							"%s:\n" : "\n%s:\n", names[i].name);
			first = 0;
			dirwalk(names[i].name, names[i].name, options);
		}
}
