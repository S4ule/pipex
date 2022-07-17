/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:50:02 by sbalesme          #+#    #+#             */
/*   Updated: 2022/07/11 11:50:05 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_free_child(t_pip *info, char **av_child, char *cmd, int m)
{
	int	i;

	if (m == 1)
	{
		i = 0;
		while (av_child != 0 && av_child[i] != 0)
		{
			free(av_child[i]);
			i++;
		}
		free(av_child);
		free(cmd);
	}
	i = 0;
	while (info->path[i])
	{
		free(info->path[i]);
		i++;
	}
	free(info->path);
	close(info->in);
	close(info->out);
	close(info->pip[0]);
	close(info->pip[1]);
	return (1);
}

void	ft_child_one(t_pip info, char **env, char **av_child, char *cmd)
{
	if (dup2(info.pip[1], 1) == -1)
		ft_perror("Dup2 fail!\n", ft_free_child(&info, av_child, cmd, 1));
	if (dup2(info.in, 0) == -1)
		ft_perror("Dup2 fail!\n", ft_free_child(&info, av_child, cmd, 1));
	ft_free_child(&info, av_child, cmd, 0);
	execve(cmd, av_child, env);
	ft_free_child(&info, av_child, cmd, 1);
	ft_perror("Execve fail!\n", 1);
}

void	ft_child_two(t_pip info, char **env, char **av_child, char *cmd)
{
	if (dup2(info.pip[0], 0) == -1)
		ft_perror("Dup2 fail!\n", ft_free_child(&info, av_child, cmd, 1));
	if (dup2(info.out, 1) == -1)
		ft_perror("Dup2 fail!\n", ft_free_child(&info, av_child, cmd, 1));
	ft_free_child(&info, av_child, cmd, 0);
	execve(cmd, av_child, env);
	ft_free_child(&info, av_child, cmd, 1);
	ft_perror("Execve fail!\n", 1);
}
