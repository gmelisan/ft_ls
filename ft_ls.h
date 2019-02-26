/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:02:55 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/26 17:25:44 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <limits.h>
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

/*
** 6 monthes: 60 * 60 * 24 * 30 * 6 = 15552000
*/

# define YEAR_BORDER	15552000
# define LINK_BUFSIZE	1024

struct				s_options
{
	t_uint			long_format		: 1;
	t_uint			recursive		: 1;
	t_uint			all				: 1;
	t_uint			reverse			: 1;
	t_uint			sort_modtime	: 1;
	t_uint			one_column		: 1;
};

typedef struct		s_name
{
	char			*name;
	struct stat		st;
	char			*pw_name;
	char			*gr_name;
	char			*timestr;
	char			*link;
	int				xattr;
}					t_name;

struct				s_longest
{
	int				link;
	int				owner;
	int				group;
	int				bytes;
	int				sp_major;
	int				sp_minor;
};

struct				s_modechars
{
	char			type;
	char			ur;
	char			uw;
	char			ux;
	char			gr;
	char			gw;
	char			gx;
	char			or;
	char			ow;
	char			ox;
	char			xattr;
};

void				parse_args(int argc, char *argv[], t_name **p_names,
							struct s_options *options);
void				error_illegal_option(char *ft_ls_name, char option);
void				error_common(char *fod);
void				sort_names(t_name *names, struct s_options options);
void				sort_names_len(t_name *names, int len,
										struct s_options options);
void				sort_lex(t_name *names);
void				main_loop(t_name *names, struct s_options options);
void				dirwalk(char *path, char *filename,
							struct s_options options);
int					is_dir(struct stat st);
int					is_link(struct stat st);
void				clear_names(t_name **names);
void				show(t_name *names, struct s_options options,
							int showtotal);
void				show_long(t_name *names, struct s_options options,
							int showtotal);
struct s_longest	get_longest(t_name *names, struct s_options options,
								int *total);
void				fill_modechars(struct s_modechars *mc, struct stat st);
void				get_usergroup(t_name *name);

int					cmp_lex(const void *a, const void *b);
int					cmp_rlex(const void *a, const void *b);
int					cmp_modtime(const void *a, const void *b);

int					is_dir(struct stat st);
int					is_link(struct stat st);
int					is_linkdir(t_name name);
int					is_device(struct stat st);

int					get_major(struct stat st);
int					get_minor(struct stat st);

#endif
