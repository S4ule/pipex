/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:50:20 by sbalesme          #+#    #+#             */
/*   Updated: 2022/07/11 11:50:21 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free_all(char **av_res, int n)
{
	while (--n >= 0)
		free(av_res[n]);
	free(av_res);
	av_res = 0;
}

static int	ft_put_in_bis(char **av_res, char *str, int *i, int l)
{
	int	j;
	int	type;

	j = 0;
	type = 0;
	if (str[l - 1] == '\'' && str[0] == '\'' && l != 1)
	{
		type = 1;
		j = 1;
	}
	while (j < l - type)
	{
		av_res[*i][j - type] = str[j];
		j++;
	}
	av_res[*i][j - type] = '\0';
	(*i)++;
	return (l);
}

static char	**ft_put_in(char **av_res, char *str)
{
	int	i;
	int	l;

	i = 0;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		if (*str)
		{
			l = get_world_size(str);
			if (str[l - 1] == '\'' && str[0] == '\'' && l != 1)
				av_res[i] = malloc(sizeof(char) * (l - 2 + 1));
			else
				av_res[i] = malloc(sizeof(char) * (l + 1));
			if (av_res[i] == 0)
			{
				ft_free_all(av_res, i);
				return (0);
			}
			str += ft_put_in_bis(av_res, str, &i, l);
		}
	}
	av_res[i] = 0;
	return (av_res);
}

char	**ft_pars(char *str)
{
	char	**av_res;

	av_res = malloc(sizeof(char *) * (number_of_arg(str) + 1));
	if (av_res == 0)
		return (0);
	ft_put_in(av_res, str);
	if (av_res == 0)
		return (0);
	return (av_res);
}
