/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 10:43:16 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/13 13:58:26 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	cmp_lex(const void *a, const void *b)
{
	char *str_a;
	char *str_b;

	str_a = ((t_name *)a)->name;
	str_b = ((t_name *)b)->name;
	return (ft_strcmp(str_a, str_b));
}

void	sort_names(t_name *names)
{
	int len;

	len = 0;
	while (names[len].name)
		len++;
	ft_qsort(names, len, sizeof(*names), cmp_lex);
}
