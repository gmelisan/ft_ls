/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:03:48 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/13 17:05:26 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_stats(t_name *names)
{
	int i;
	int ret;

	i = 0;
	while (names[i].name)
	{
		ret = lstat(names[i].name, &(names[i].st));
		if (ret == -1)
			error_common(names[i].name);
		i++;
	}
}
