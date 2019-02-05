/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:03:41 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/05 14:16:52 by gmelisan         ###   ########.fr       */
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
*/

#include "ft_ls.h"

int		main(int argc, char *argv[])
{
	char				**names;
	struct s_options	options;
	int					i;
	int					e;

	e = parse_args(argc, argv, &names, &options);
	if (!e)
	{
		i = 0;
		while(names[i])
		{
			ft_printf("names[%d] = %s\n", i, names[i]); 
			i++;
		}
		ft_printf("options:\n");
		ft_printf("-l: %d\n", options.long_format);
		ft_printf("-R: %d\n", options.recursive);
		ft_printf("-a: %d\n", options.all);
		ft_printf("-r: %d\n", options.reverse);
		ft_printf("-t: %d\n", options.sort_modtime);
	}
	ft_strarrdel(&names);
	return (0);
}
