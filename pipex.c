/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:47:29 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/07/23 13:20:15 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_erro(t_pxpex *sev)
{
	if (sev->argc > 5)
		close(sev->outfile);
	else
	{
		close(sev->infile);
		close(sev->outfile);
	}
	ft_close(sev);
	ft_free(sev->path);
	perror("Error");
	exit(1);
}

void	ft_dup(t_pxpex *sev, int i)
{
	if (i == 2)
	{
		if (dup2(sev->infile, STDIN_FILENO) == -1)
			ft_erro(sev);
		if (dup2(sev->fds[0][1], STDOUT_FILENO) == -1)
			ft_erro(sev);
	}
	else if (i == sev->argc - 2)
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
	close(sev->infile);
	close(sev->outfile);
	ft_close(sev);
}

void	ft_pipe(t_pxpex *sev)
{
	int	i;

	i = 0;
	sev->fds = malloc(sizeof(int *) * (sev->argc - 4));
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

void	ft_pipex(t_pxpex *sev, char *argv, int j)
{
	int		f;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_erro(sev);
	if (cmd[0] && ft_strchr(cmd[0], '/') == NULL)
		cmd[0] = ft_cmd(sev, cmd);
	f = fork();
	if (f == 0)
	{
		ft_dup(sev, j);
		execve(cmd[0], cmd, sev->env);
		perror("Error");
		exit(1);
	}
	ft_free(cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_pxpex	sev;
	int		i;

	sev.argc = argc;
	sev.argv = argv;
	sev.env = env;
	sev.path = ft_pathchik(sev.env);
	i = 0;
	if (argc < 5)
		return (1);
	if (argc > 5 && !ft_strcmp(argv[1], "here_doc"))
	{
		sev.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_heredoc(&sev);
	}
	else
		help(&sev, argc, argv);
	ft_free(sev.path);
	ft_close(&sev);
	while (wait(NULL) != -1)
		;
}
