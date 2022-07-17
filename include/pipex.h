/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:18:51 by sbalesme          #+#    #+#             */
/*   Updated: 2022/06/30 14:47:35 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_pip
{
	int		pip[2];
	int		in;
	int		out;
	char	**path;
	char	**av_child_one;
	char	*cmd_one;
	char	**av_child_two;
	char	*cmd_two;

	pid_t	child_one;
	pid_t	child_two;
}	t_pip;

//main
void			ft_perror(char *str, int erc);

//pipex
int				ft_pipex(t_pip *info, char **av, char **env);

void			ft_init_pipex(int ac, char **av, char **env, t_pip *info);

//child

int				ft_child_one_init(t_pip *info, char **av);

int				ft_child_two_init(t_pip *info, char **av);

//child start

void			ft_child_one(t_pip info, char **env, char **av_child, \
					char *cmd);

void			ft_child_two(t_pip info, char **env, char **av_child, \
					char *cmd);

//pars

char			**ft_pars(char *str);

//pars_bis

size_t			get_world_size(char *str);

unsigned int	number_of_arg(char *str);

#endif
