/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:02:55 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/05 14:15:00 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
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

struct s_options
{
	t_uint	long_format		: 1;
	t_uint	recursive		: 1;
	t_uint	all				: 1;
	t_uint	reverse			: 1;
	t_uint	sort_modtime	: 1;
};

int				parse_args(int argc, char *argv[], char ***p_names,
							struct s_options *options);
void			error_illegal_option(char *ft_ls_name, char option);

#endif
