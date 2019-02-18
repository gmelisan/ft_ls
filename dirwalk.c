/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirwalk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:53:21 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/18 20:12:12 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* static void		delname(void *content, size_t size) */
/* { */
/* 	size = 0; */
/* 	free(((t_name *)content)->name); */
/* 	free(content); */
/* } */

/* void		show_onecolumn(t_list *dircontent, struct s_options options) */
/* { */
/* 	while (dircontent) */
/* 	{ */
/* 		if (options.all) */
/* 			ft_printf("%s\n", ((t_name *)dircontent->content)->name); */
/* 		else if (((t_name *)dircontent->content)->name[0] != '.') */
/* 			ft_printf("%s\n", ((t_name *)dircontent->content)->name); */
/* 		dircontent = dircontent->next; */
/* 	} */
/* } */

/* t_name		*to_array(t_list *dircontent) */
/* { */
/* 	int			size; */
/* 	t_name		*names; */
/* 	t_list		cur; */
/* 	int			i; */

/* 	size = ft_lstsize(dircontent); */
/* 	names = ft_memalloc(sizeof(*res) * (size + 1)); */
/* 	cur = dircontent; */
/* 	i = 0; */
/* 	while (cur) */
/* 	{ */
/* 		names[i] = *((t_name *)dircontent->content); */
/* 		cur = cur->next; */
/* 	} */
/* 	return (names); */
/* } */

/* t_list		*get_dircontent(char *path, struct s_options options) */
/* { */
/* 	struct dirent	*ent; */
/* 	DIR				*dir; */
/* 	t_list			*dircontent; */
/* 	t_list			*tmp; */

/* 	dir = opendir(path); */
/* 	if (!dir) */
/* 	{ */
/* 		error_common(path, 0); */
/* 		return (NULL); */
/* 	} */
/* 	dircontent = NULL; */
/* 	while ((ent = readdir(dir))) */
/* 	{ */
/* 		tmp = ft_lstnew(NULL, 0); */
/* 		tmp->content = ft_memalloc(sizeof(t_name)); */
/* 		((t_name *)tmp->content)->name = ft_strdup(ent->d_name); */
/* 		if (lstat(ent->d_name, &(((t_name *)tmp->content)->st)) == -1) */
/* 			error_common(path, 0); */
/* 		else */
/* 			ft_lstaddback(&dircontent, tmp); */
/* 	} */
/* 	closedir(dir); */
/* 	sort_dircontent(dircontent, options); */
/* 	return (dircontent); */
/* } */

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
		if (is_link(names[i]))
			stat(fullpath, &(names[i].lst)); /* not working */
		free(fullpath);
		i++;
	}
	len = i;
	ft_qsort(names, len, sizeof(*names), options.reverse ? cmp_rlex : cmp_lex);
	if (options.sort_modtime)
		ft_qsort(names, len, sizeof(*names), cmp_modtime);
}

void		dirwalk(char *path, struct s_options options)
{
	t_name		*names;
	DIR			*dir;

	if (!(dir = opendir(path)))
	{
		error_common(path, 0);
		return ;
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

	/* t_list	*dircontent; */
	/* t_name	*names; */

	/* if (!(dircontent = get_dircontent(path, options))) */
	/* 	return ; */
	/* names = to_array(dircontent); */
	/* ft_lstdel(&dircontent, delname); */
	/* show_onecolumn(dircontent, options); */
}
