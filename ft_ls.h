/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:02:55 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/12 05:42:35 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
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
};

enum	e_type		{TYPE_NONE, TYPE_FILE, TYPE_DIR};

typedef struct		s_name
{
	char			*d_name;
	enum e_type		type;
	struct stat		*st;
	char			*pw_name;
	char			*gr_name;
	struct s_name	*next;
}					t_name;
stat
void				parse_args(int argc, char *argv[], char ***p_names,
							struct s_options *options);
void				error_illegal_option(char *ft_ls_name, char option);

#endif
