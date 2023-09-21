/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:15:19 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/07/23 12:47:54 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipe2(t_pxpex *sev)
{
	int	i;

	i = 0;
	sev->fds = malloc(sizeof(int *) * (sev->argc - 3));
	if (!sev->fds)
		ft_erro(sev);
	while (i < sev->argc - 4)
	{
		sev->fds[i] = malloc(sizeof(int) * 2);
		if (!sev->fds[i])
			ft_erro(sev);
		if (pipe(sev->fds[i]) == -1)
			ft_erro(sev);
		i++;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

void	ft_dupbon(t_pxpex *sev, int i)
{
	if (i == sev->argc - 2)
	{
		if (dup2(sev->fds[i - 3][0], STDIN_FILENO) == -1)
			ft_erro(sev);
		if (dup2(sev->outfile, STDOUT_FILENO) == -1)
			ft_erro(sev);
	}
	else
	{
		if (dup2(sev->fds[i - 3][0], STDIN_FILENO) == -1)
			ft_erro(sev);
		if (dup2(sev->fds[i - 2][1], STDOUT_FILENO) == -1)
			ft_erro(sev);
	}
	close(sev->outfile);
	ft_close(sev);
}

void	ft_pipebon(t_pxpex *sev, int i)
{
	int		f;
	char	**cmd;

	cmd = ft_split(sev->argv[i], ' ');
	if (!cmd)
		ft_erro(sev);
	if (cmd[0] && ft_strchr(cmd[0], '/') == NULL)
		cmd[0] = ft_cmd(sev, cmd);
	f = fork();
	if (f == 0)
	{
		ft_dupbon(sev, i);
		execve(cmd[0], cmd, sev->env);
	}
	ft_free(cmd);
}

void	ft_heredoc(t_pxpex *sev)
{
	char	*lim;
	char	*str;
	int		i;

	i = 2;
	ft_pipe2(sev);
	lim = ft_strjoin(sev->argv[2], "\n");
	while (1)
	{
		write(1, ">", 1);
		str = get_next_line(0);
		if (!str || ft_strcmp(str, lim) == 0)
			break ;
		ft_putstr_fd(str, sev->fds[0][1]);
		free(str);
	}
	free(str);
	while (++i < sev->argc - 1)
		ft_pipebon(sev, i);
	free(lim);
}
