/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 10:43:16 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/18 20:12:15 by gmelisan         ###   ########.fr       */
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

/* del */

int		cmp_modtime(const void *a, const void *b)
{
	time_t time_a;
	time_t time_b;

	if (is_link(*((t_name *)a)))
		time_a = ((t_name *)a)->lst.st_mtime;
	else
		time_a = ((t_name *)a)->st.st_mtime;
	if (is_link(*((t_name *)b)))
		time_b = ((t_name *)b)->lst.st_mtime;
	else
		time_b = ((t_name *)b)->st.st_mtime;
	return (time_b - time_a);
}

void	sort_names(t_name *names, int (*f)(const void *, const void *))
{
	int len;

	len = 0;
	while (names[len].name)
		len++;
	ft_qsort(names, len, sizeof(*names), f);
}
