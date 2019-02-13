/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:03:41 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/12 07:52:06 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Options:
**
** -l (long format)
** -R (recursive)
** -a (show all)
** -r (reverse order)
** -t (sort by modified time)
** -- (cancel option parsing)
*/

#include "ft_ls.h"

int		main(int argc, char *argv[])
{
	char				*str_names[];
	struct s_options	options;
	t_name				*name;

	parse_args(argc, argv, &names, &options);
	sort_names(str_names);
	init_list(name, str_names);
	ft_ls(names, options);
	ft_strarrdel(&names);
	return (0);
}
