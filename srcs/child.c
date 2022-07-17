/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 00:27:51 by sbalesme          #+#    #+#             */
/*   Updated: 2022/06/30 14:55:32 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_find_cmd(char **path, char *name)
{
	char	*tmp;
	char	*cmd;

	if (access(name, F_OK | X_OK) == 0)
	{
		cmd = ft_strdup(name);
		return (cmd);
	}
	while (*path != 0)
	{
		tmp = ft_strjoin(*path, "/");
		if (tmp == NULL)
			return (NULL);
		cmd = ft_strjoin(tmp, name);
		free(tmp);
		if (cmd == NULL)
			return (NULL);
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		free(cmd);
		path++;
	}
	return (NULL);
}

int	ft_child_one_init(t_pip *info, char **av)
{
	info->cmd_one = NULL;
	info->av_child_one = ft_pars(av[2]);
	if (info->av_child_one == NULL)
		return (2);
	info->cmd_one = ft_find_cmd(info->path, info->av_child_one[0]);
	if (info->cmd_one == 0)
		return (2);
	return (0);
}

int	ft_child_two_init(t_pip *info, char **av)
{
	info->cmd_two = NULL;
	info->av_child_two = ft_pars(av[3]);
	if (info->av_child_two == NULL)
		return (3);
	info->cmd_two = ft_find_cmd(info->path, info->av_child_two[0]);
	if (info->cmd_two == 0)
		return (3);
	return (0);
}
