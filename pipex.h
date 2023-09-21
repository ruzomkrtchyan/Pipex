/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:28:37 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/07/22 21:21:16 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "get_next_line.h"
# include <fcntl.h>

typedef struct s_pxpex
{
	int		argc;
	char	**argv;
	char	**env;
	char	**path;
	int		**fds;
	char	**cmds;
	int		infile;
	int		outfile;
}			t_pxpex;

char	**ft_pathchik(char **env);
char	**ft_split(char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char *s1, char *s2);
void	help(t_pxpex *sev, int argc, char **argv);
char	*ft_cmd(t_pxpex *sev, char **cmd);
void	ft_free(char **s);
void	ft_close(t_pxpex *sev);
void	ft_erro(t_pxpex *sev);
void	ft_pipe(t_pxpex *sev);
void	ft_pipex(t_pxpex *sev, char *argv, int j);
void	ft_heredoc(t_pxpex *sev);

#endif