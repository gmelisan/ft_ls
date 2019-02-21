/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:16:48 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/21 17:27:39 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_lex(const void *a, const void *b)
{
	char *str_a;
	char *str_b;

	str_a = ((t_name *)a)->name;
	str_b = ((t_name *)b)->name;
	return (ft_strcmp(str_a, str_b));
}

int		cmp_rlex(const void *a, const void *b)
{
	char *str_a;
	char *str_b;

	str_a = ((t_name *)a)->name;
	str_b = ((t_name *)b)->name;
	return (-ft_strcmp(str_a, str_b));
}

int		cmp_modtime(const void *a, const void *b)
{
	time_t	time_a;
	time_t	time_b;
	long	res;

	time_a = ((t_name *)a)->st.st_mtime;
	time_b = ((t_name *)b)->st.st_mtime;
	res = time_b - time_a;
	if (res > INT_MAX)
		res = 1;
	else if (res < INT_MIN)
		res = -1;
	return (res);
}
