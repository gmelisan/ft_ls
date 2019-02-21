/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_names.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:02:06 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/21 01:05:41 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	clear_names(t_name **p_names)
{
	t_name	*names;
	int		i;

	names = *p_names;
	i = 0;
	while (names[i].name)
	{
		free(names[i].name);
		ft_strdel(&(names[i].pw_name));
		ft_strdel(&(names[i].gr_name));
		ft_strdel(&(names[i].timestr));
		ft_strdel(&(names[i].link));
		i++;
	}
	free(names);
	*p_names = NULL;
}
