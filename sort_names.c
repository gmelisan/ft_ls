/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 10:43:16 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/12 05:39:15 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#inclue "ft_ls.h"

static int	strcmp_lex(const void *a, const void *b)
{
	return (ft_strcmp(*((char **)a), *((char **)b)));
}

static void	show(char *names[], struct s_options options, int showopt)
{
	int i;

	i = 0;
	while(names[i])
	{
		ft_printf("names[%d] = %s\n", i, names[i]);
		i++;
	}
	if (showopt)
	{
		ft_printf("options:\n");
		ft_printf("-l: %d\n", options.long_format);
		ft_printf("-R: %d\n", options.recursive);
		ft_printf("-a: %d\n", options.all);
		ft_printf("-r: %d\n", options.reverse);
		ft_printf("-t: %d\n", options.sort_modtime);
	}
	ft_printf("\n");
}

void	sort_names(char *names[])
{
	int len;

	len = 0;
	while (names[len])
		len++;
	ft_qsort(names, len, sizeof(*names), strcmp_lex);
	ft_printf("str_names (after sort):\n");
	show(names, options, 0)
}
