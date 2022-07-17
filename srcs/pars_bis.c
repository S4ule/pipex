/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:50:13 by sbalesme          #+#    #+#             */
/*   Updated: 2022/07/11 11:50:14 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_look_acc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (i);
		i++;
	}
	return (-1);
}

size_t	get_world_size(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != ' ')
		i++;
	if (str[i] == '\'' && i == 0)
	{
		i++;
		if (ft_look_acc(str + 1) != -1)
		{
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
		}
		else
			while (str[i] && str[i] != ' ')
				i++;
	}
	return (i);
}

static unsigned int	number_of_arg_bis(char *str, unsigned int *res)
{
	int	i;

	i = 0;
	if (str[i] != '\'')
		(*res)++;
	else if (ft_look_acc(str + i + 1) == -1)
		(*res)++;
	while (str[i] && str[i] != ' ' && str[i] != '\'')
		i++;
	if (str[i] && str[i] == '\'' && ft_look_acc(str + i + 1) != -1)
	{
		(*res)++;
		i += ft_look_acc(str + i + 1) + 2;
	}
	else
	{
		if (str[i] == '\'')
			i++;
		while (str[i] && str[i] != ' ' && str[i] != '\'')
			i++;
	}
	return (i);
}

unsigned int	number_of_arg(char *str)
{
	unsigned int	res;

	res = 0;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		while (*str && *str != ' ')
		{
			str += number_of_arg_bis(str, &res);
		}
	}
	return (res);
}
