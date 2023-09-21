/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:18:08 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/07/22 21:23:53 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	help(t_pxpex *sev, int argc, char **argv)
{
	int	j;

	j = 1;
	sev->infile = open(argv[1], O_RDONLY);
	sev->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_pipe(sev);
	while (++j < argc - 1)
		ft_pipex(sev, sev->argv[j], j);
}

void	ft_close(t_pxpex *sev)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < sev->argc - 4)
	{
		close(sev->fds[i][0]);
		close(sev->fds[i][1]);
		free(sev->fds[i]);
		i++;
	}
	free(sev->fds);
}
