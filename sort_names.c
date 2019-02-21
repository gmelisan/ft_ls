/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 10:43:16 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/21 18:49:03 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	reverse(t_name *names, int len)
{
	int i;
	int j;

	i = 0;
	j = len - 1;
	while (i < len / 2)
	{
		ft_swap(&names[i], &names[j], sizeof(t_name));
		i++;
		j--;
	}
}

static void postsort_mtime(t_name *names, int len, struct s_options options)
{
	int i;
	int j;

	i = 0;
	while (i < len)
	{
		j = i;
		while (names[j + 1].name && (names[i].st.st_mtime == names[j + 1].st.st_mtime))
			j++;
		if (j > i)
		{
			ft_qsort(names + i, j - i + 1, sizeof(*names), cmp_lex);
			i = j + 1;
		}
		else
			i++;
	}
	if (options.reverse)
		reverse(names, len);
}

void		sort_names_len(t_name *names, int len, struct s_options options)
{
	if (options.sort_modtime)
	{
		ft_qsort(names, len, sizeof(*names), cmp_modtime);
		postsort_mtime(names, len, options);
	}
	else
		ft_qsort(names, len, sizeof(*names), options.reverse ? cmp_rlex : cmp_lex);
}

void		sort_lex(t_name *names)
{
	int len;

	len = 0;
	while(names[len].name)
		len++;
	ft_qsort(names, len, sizeof(*names), cmp_lex);
}

void		sort_names(t_name *names, struct s_options options)
{
	int len;

	len = 0;
	while(names[len].name)
		len++;
	sort_names_len(names, len, options);
}

/* sandbox_cmd("touch C && touch -t 201212101830.55 c && mkdir -p sbox sbox1"); */
/* 	sandbox_cmd("touch -t 201312101830.55 B"); */
/* 	sandbox_cmd("touch -t 201312101830.55 a"); */
/* 	// print_ls_debug(cmd); */
/* 	mt_assert(strcmp(ls(cmd), ft_ls(cmd)) == 0); */
