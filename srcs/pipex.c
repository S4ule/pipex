/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 00:30:18 by sbalesme          #+#    #+#             */
/*   Updated: 2022/06/30 15:00:15 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_get_path(char **env)
{
	while (*env != 0 && ft_strncmp("PATH", *env, 4) != 0)
		env++;
	if (*env == 0)
		return (0);
	return ((*env) + 5);
}

static char	**ft_get_all_path(char **env)
{
	char	*path;
	char	**res;

	path = ft_get_path(env);
	if (path == 0)
		return (0);
	res = ft_split(path, ':');
	return (res);
}

static int	ft_pipex_close(t_pip *info)
{
	int	i;

	i = 0;
	while (info->path != 0 && info->path[i] != 0)
	{
		free(info->path[i]);
		i++;
	}
	free(info->path);
	close(info->in);
	close(info->out);
	return (1);
}

void	ft_init_pipex(int ac, char **av, char **env, t_pip *info)
{
	if (ac == 5)
	{
		info->out = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (info->out == -1)
			ft_perror("Impossible to open Outfile!\n", 1);
		info->in = open(av[1], O_RDONLY);
		if (info->in == -1)
		{
			close(info->out);
			if (access(av[1], F_OK))
				ft_perror("Impossible to open Infile!\n", 1);
			ft_perror("Impossible to open Infile!\n", 0);
		}
		info->path = ft_get_all_path(env);
		if (info->path == NULL)
			ft_perror("Impossible to get path in env!\n", ft_pipex_close(info));
		if (pipe(info->pip) == -1)
			ft_perror("Impossible to get pipe!\n", ft_pipex_close(info));
	}
	else
		ft_perror("Too manny or too less args\n", 1);
}

int	ft_pipex(t_pip *info, char **av, char **env)
{
	int	res_one;
	int	res_two;

	res_one = ft_child_one_init(info, av);
	res_two = ft_child_two_init(info, av);
	if (res_one == 0)
	{
		info->child_one = fork();
		if (info->child_one == -1)
			return (1);
		if (info->child_one == 0)
			ft_child_one(*info, env, info->av_child_one, info->cmd_one);
	}
	if (res_two == 0)
	{
		info->child_two = fork();
		if (info->child_two == -1)
			return (1);
		if (info->child_two == 0)
			ft_child_two(*info, env, info->av_child_two, info->cmd_two);
	}
	return (res_one + res_two);
}
