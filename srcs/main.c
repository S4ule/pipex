/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:19:38 by sbalesme          #+#    #+#             */
/*   Updated: 2022/06/30 14:58:18 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *str, int erc)
{
	write(2, str, ft_strlen(str));
	exit(erc);
}

void	ft_free_child(char **av, char *cmd)
{
	int	i;

	free(cmd);
	i = 0;
	while (av && av[i])
		free(av[i++]);
	free(av);
}

static void	ft_free_main(t_pip *info)
{
	int	i;

	close(info->pip[0]);
	close(info->pip[1]);
	close(info->in);
	close(info->out);
	i = 0;
	while (info->path[i] != 0)
		free(info->path[i++]);
	free(info->path);
	ft_free_child(info->av_child_one, info->cmd_one);
	ft_free_child(info->av_child_two, info->cmd_two);
}

int	main(int ac, char **av, char **env)
{
	t_pip	info;
	int		err;

	ft_init_pipex(ac, av, env, &info);
	err = ft_pipex(&info, av, env);
	ft_free_main(&info);
	if (err == 1)
		ft_perror("Fork fail!\n", 1);
	if (err == 0 || err == 2 || err == 3)
		wait(0);
	if (err == 0)
		wait(0);
	if (err == 3 || err == 5)
		ft_perror("Error in init child!\n", 127);
	if (err == 2)
		ft_perror("Error in init child!\n", 0);
	return (0);
}
