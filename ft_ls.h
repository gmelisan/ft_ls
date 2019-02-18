/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:02:55 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/18 20:08:04 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"

/*
** Allowed functions:
**
** write malloc free exit
** opendir readdir closedir
** stat	lstat
** getpwuid getgrgid
** listxattr getxattr
** time ctime
** readlink perror strerror
*/

struct				s_options
{
	t_uint			long_format		: 1;
	t_uint			recursive		: 1;
	t_uint			all				: 1;
	t_uint			reverse			: 1;
	t_uint			sort_modtime	: 1;
	t_uint			one_column		: 1;
};

/* enum	e_type		{TYPE_NONE, TYPE_FILE, TYPE_DIR}; */

typedef struct		s_name
{
	char			*name;
	struct stat		st;
	struct stat		lst;
	char			*pw_name;
	char			*gr_name;
	/* struct s_name	*next; */
}					t_name;

void				parse_args(int argc, char *argv[], t_name **p_names,
							struct s_options *options);
void				error_illegal_option(char *ft_ls_name, char option);
void				error_common(char *fod, int die);
void				sort_names(t_name *names,
								int (*f)(const void *, const void *));
void				get_stats(t_name *names);
void				main_loop(t_name *names, struct s_options options);
void				show_dir(char *base, char *path, struct s_options options);
void				dirwalk(char *path, struct s_options options);
int					is_dir(t_name name);
int					is_link(t_name name);

int					cmp_lex(const void *a, const void *b);
int					cmp_rlex(const void *a, const void *b);
int					cmp_modtime(const void *a, const void *b);

#endif
