/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:03:41 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/26 16:48:45 by gmelisan         ###   ########.fr       */
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
** -1 (one column, default)
** -- (cancel option parsing)
*/

#include "ft_ls.h"

int		main(int argc, char *argv[])
{
	struct s_options	options;
	t_name				*names;

	parse_args(argc, argv, &names, &options);
	main_loop(names, options);
	clear_names(&names);
	return (0);
}
