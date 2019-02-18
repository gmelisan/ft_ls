/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:43:16 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/18 14:07:21 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		show_onecol(t_list *name)
{
	ft_printf("%s\n", ((t_name *)name->content)->name);
}

void		delname(void *content, size_t size)
{
	size = 0;
	free(((t_name *)content)->name);
	free(content);
}

int			is_dir_empty(t_list *name)
{
	if (ft_strequ(((t_name*)name->content)->name, ".") &&
		name->next == NULL)
		return (1);
	return (0);
}

t_list		*get_dir(char *path, struct s_options options)
{
	struct dirent	*ent;
	DIR				*dir;
	t_list			*name;
	t_list			*tmp;

	dir = opendir(path);
	if (!dir)
	{
		error_common(path, 0);
		return (NULL);
	}
	name = NULL;
	while ((ent = readdir(dir)))
	{
		tmp = ft_lstnew(NULL, 0);
		tmp->content = ft_memalloc(sizeof(t_name));
		((t_name *)tmp->content)->name = ft_strdup(ent->d_name);
		lstat(ent->d_name, &(((t_name *)tmp->content)->st));
		if (options.reverse)
			ft_lstadd(&name, tmp);
		else
			ft_lstaddback(&name, tmp);
	}
	closedir(dir);
	return (name);
}

char		*add_slash(char *path)
{
	int len;

	len = ft_strlen(path);
	ft_printf("adding slash to '%s', len = %d\n", path, len);
	ft_realloc((void **)&path, len + 1, len + 2);
	path[len] = '/';
	return (path);
}

int			is_dot_dotdot(t_name *name)
{
	if (ft_strequ(name->name, "."))
		return (1);
	if (ft_strequ(name->name, ".."))
		return (1);
	return (0);
}

void		show_dir(char *base, char *path, struct s_options options)
{
	t_list	*name;
	t_list	*cur;
	char	*new_path;
	static int a;

	a++;
	if (a == 100)
	{
		ft_printf("suuuuka\n");
		exit(1);
	}	
	new_path = ft_strjoin(base, path);
	name = get_dir(new_path, options);
	ft_printf("path = %s\n", new_path);
	if (name)
		ft_lstiter(name, show_onecol);
	if (options.recursive)
	{
		cur = name;
		while (cur)
		{
			if (is_dir(*((t_name *)cur->content)) && !is_dot_dotdot((t_name *)cur->content))
			{
				ft_printf("going to %s\n", new_path);
				show_dir(add_slash(new_path), ((t_name *)cur->content)->name, options);
			}
			cur = cur->next;
		}
	}
	ft_printf("end path = %s\n", new_path);
	ft_printf("\n");
	ft_memdel((void **)&new_path);
	ft_lstdel(&name, delname);
}
/*

1. Show dir's content;
2. Loop over dirs
	if -R, call itself

*/
