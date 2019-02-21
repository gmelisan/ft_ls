/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:03:41 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/20 19:54:26 by gmelisan         ###   ########.fr       */
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

/* static void	show(t_name *names, struct s_options options, int showopt) */
/* { */
/* 	int i; */

/* 	i = 0; */
/* 	while(names[i].name) */
/* 	{ */
/* 		ft_printf("names[%d] = %s\n", i, names[i].name); */
/* 		i++; */
/* 	} */
/* 	if (showopt) */
/* 	{ */
/* 		ft_printf("options:\n"); */
/* 		ft_printf("-l: %d\n", options.long_format); */
/* 		ft_printf("-R: %d\n", options.recursive); */
/* 		ft_printf("-a: %d\n", options.all); */
/* 		ft_printf("-r: %d\n", options.reverse); */
/* 		ft_printf("-t: %d\n", options.sort_modtime); */
/* 	} */
/* } */

int		main(int argc, char *argv[])
{
	struct s_options	options;
	t_name				*names;

	parse_args(argc, argv, &names, &options);
	main_loop(names, options);
	clear_names(&names);
	return (0);
}
