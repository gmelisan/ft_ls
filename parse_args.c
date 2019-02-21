/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 04:04:01 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/21 17:38:38 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ls -
**		file '-'
** ls ---
*n*		illegal option '-'
*/

#include "ft_ls.h"

static void		clear_1l(struct s_options *options)
{
	options->one_column = 0;
	options->long_format = 0;
}

static int		parse_option(char *s, struct s_options *options)
{
	s++;
	while (*s)
	{
		if (*s == 'l' || *s == '1')
			clear_1l(options);
		if (*s == 'l')
			options->long_format = 1;
		else if (*s == 'R')
			options->recursive = 1;
		else if (*s == 'a')
			options->all = 1;
		else if (*s == 'r')
			options->reverse = 1;
		else if (*s == 't')
			options->sort_modtime = 1;
		else if (*s == '1')
			options->one_column = 1;
		else
			return (*s);
		s++;
	}
	return (0);
}


static int		parse_options(int argc, char *argv[], struct s_options *options)
{
	int		i;
	char	opt;

	i = 0;
	while (++i < argc)
	{
		if (ft_strequ(argv[i], "--"))
			return (++i);
		if (argv[i][0] != '-')
			return (i);
		if (ft_strequ(argv[i], "-"))
			return (i);
		opt = parse_option(argv[i], options);
		if (opt != 0)
			error_illegal_option(argv[0], opt);
	}
	return (i);
}

static void		parse_names(int argc, char *argv[], t_name *names, int i)
{
	int j;

	j = 0;
	while (i < argc)
	{
		names[j++].name = ft_strdup(argv[i]);
		i++;
	}
}

void			parse_args(int argc, char *argv[], t_name **p_names,
												struct s_options *options)
{
	int		i;
	t_name *names;

	names = *p_names;
	ft_bzero(options, sizeof(*options));
	i = parse_options(argc, argv, options);
	names = ft_memalloc(sizeof(*names) * (argc + 1));
	parse_names(argc, argv, names, i);
	if (!names[0].name)
	{
		names[0].name = ft_memalloc(2);
		names[0].name[0] = '.';
	}
	*p_names = names;
}
