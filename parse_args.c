/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 04:04:01 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/05 15:56:54 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Some annoying cases:
**
** ls -
**		file '-'
** ls -- a
**		'--' ignores, file 'a'
** ls ---
** ls ------ a
**		illegal option '-'
**
** ls a -
**		file '-', file 'a'
** ls a --
**		file '--', file 'a'
** ls a ---
**		file '---', file 'a'
**
** ls - - -
**		3 files '-'
** ls -- --
**		first '--' ignores, second file '--'
*/

#include "ft_ls.h"

static void		set_default_path(char **names)
{
	names[0] = ft_memalloc(2);
	names[0][0] = '.';
}

static int		parse_options(char *s, struct s_options *options)
{
	s++;
	while (*s)
	{
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
		else
			return (1);
		s++;
	}
	return (0);
}

static int		parse_loop(int argc, char *argv[], char **names,
												struct s_options *options)
{
	int		i;
	int		j;
	int		e;

	e = 0;
	i = 0;
	j = 0;

	while (++i < argc)
	{
		if (i == 1 && ft_strequ(argv[i], "--"))
			continue ;
		if (i == 1 && argv[i][0] == '-' && argv[i][1] == '-' &&
			argv[i][2] == '-')
			e = 1;
		else if (argv[i][0] == '-' && argv[i][1] != '-' && argv[i][1] != '\0')
			e = parse_options(argv[i], options);
		else
			names[j++] = ft_strdup(argv[i]);
		if (e)
		{
			error_illegal_option(argv[0], argv[i][1]);
			return (1);
		}
	}
	return (0);
}

int				parse_args(int argc, char *argv[], char ***p_names,
												struct s_options *options)
{
	int		i;
	int		e;
	char	**names;

	e = 0;
	names = *p_names;
	ft_bzero(options, sizeof(*options));
	names = ft_memalloc(sizeof(*names) * (argc + 1));
	i = 1;
	if (argc == 1)
		set_default_path(names);
	else if (argc == 2 && ft_strequ(argv[1], "--"))
		set_default_path(names);
	else
		e = parse_loop(argc, argv, names, options);
	*p_names = names;
	return (e);
}
