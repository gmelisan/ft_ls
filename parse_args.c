/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 04:04:01 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/05 05:05:11 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		set_default_path(char **names)
{
	names[0] = ft_memalloc(2);
	names[0][0] = '.';
}

static void		parse_option(char *s, struct s_options *options)
{
	s++;
	while (*s)
	{
		if (*s == 'l')
			options->long_format = 1;
		else if (*s == 'R')
			options->recursive = 1;
		else if (*s == 'a')
			options->show_all = 1;
		else if (*s == 'r')
			options->reverse = 1;
		else if (*s == 't')
			options->sort_modtime = 1;
		s++;
	}
}

static void		parse_loop(int argc, char *argv[], char **names,
												struct s_options *options)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			parse_option(argv[i], options);
		else
			names[j++] = ft_strdup(argv[i]);
		i++;
	}
}

void			parse_args(int argc, char *argv[], char ***p_names,
												struct s_options *options)
{
	int		i;
	char	**names;

	names = *p_names;
	ft_bzero(options, sizeof(*options));
	names = ft_memalloc(sizeof(*names) * (argc + 1));
	i = 1;
	if (argc == 1)
		set_default_path(names);
	else
		parse_loop(argc, argv, names, options);
	*p_names = names;
}
