/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:03:41 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/01 19:01:28 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		main(int argc, char *argv[])
{
	DIR				*dir;
	struct dirent	*dent;

	dir = opendir("./norightdir");
	if (!dir)
	{
		ft_fdprintf(2, "Opening directory");
		return (1);
	}
	while ((dent = readdir(dir)) != NULL)
		ft_printf("%s\n", dent->d_name);
	closedir(dir);
	return (0);
}
