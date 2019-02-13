/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:41:30 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/13 18:08:13 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		show_onecol(t_list *name)
{
	ft_printf("%s\n", ((t_name *)name->content)->name);
}

void		delname(void *content, size_t size)
{
	free(((t_name *)content)->name);
	free(content);
}

void		get_dir(char *path, struct s_options options)
{
	struct dirent	*ent;
	DIR				*dir;
	t_list			*name;
	t_list			*tmp;

	dir = opendir(path);
	if (!dir)
	{
		error_common(path);
		return ;
	}
	name = NULL;
	while ((ent = readdir(dir)))
	{
		tmp = ft_lstnew(NULL, 0);
		tmp->content = ft_memalloc(sizeof(t_name));
		((t_name *)tmp->content)->name = ft_strdup(ent->d_name);
		if (options.reverse)
			ft_lstadd(&name, tmp);
		else
			ft_lstaddback(&name, tmp);
	}
	ft_lstiter(name, show_onecol);
	closedir(dir);
	return (name);
}

void		show_dir(char *path, struct s_options options)
{
	t_list	*name;
	t_list	*cur;

	name = get_dir(path, options);
	cur = name;
	while (cur)
	{
		ft_printf("%s\n", ((t_name *)cur->content)->name);
		if (options.recursive)
			show_dir(((t_name *)cur->content)->name, options);
		cur = cur->next;
	}
	ft_lstdel(&name, delname);
}
