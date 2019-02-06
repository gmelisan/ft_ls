/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 12:49:13 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/06 18:51:12 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	partition(char *arr[], int index, int first, int last)
{
	int pivot;
	int i;
	int j;

	pivot = arr[last][index];
	i = first - 1;
	j = first;
	while (j <= last - 1)
	{
		if (arr[j][index] <= pivot)
		{
			i++;
			ft_swap(&arr[i], &arr[j], sizeof(*arr));
		}
		j++;
	}
	ft_swap(&arr[i + 1], &arr[last], sizeof(*arr));
	return (i + 1);
}

static void	quicksort_index(char *arr[], int index, int first, int last)
{
	int pivot;

	if (first < last)
	{
		pivot = partition(arr, index, first, last);
		quicksort_index(arr, index, first, pivot - 1);
		quicksort_index(arr, index, pivot + 1, last);
	}
}

void		strsort_index(char *arr[], int index, int first, int len)
{
	int i;
	int k;
	int next_first;
	int next_len;

	quicksort_index(arr, index, first, len - 1);
	i = first;
	while (i < len - 1)
	{
		k = i;
		next_first = i;
		while (arr[k][index] == arr[k + 1][index])
			k++;
		next_len = k;
		strsort_index(arr, index + 1, next_first, next_len);
		i++;
	}
}

void		ft_strsort(char *arr[])
{
	int len;

	len = 0;
	while (arr[len])
		len++;
	strsort_index(arr, 0, 0, len);
}
