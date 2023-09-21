/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:19:25 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/07/23 13:21:39 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	**ft_pathchik(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split((ft_strchr(env[i], '/')), ':'));
		i++;
	}
	return (NULL);
}

char	*ft_cmd(t_pxpex *sev, char **cmd)
{
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	tmp = ft_strjoin("/", cmd[i]);
	while (sev->path && sev->path[i] != NULL)
	{
		str = ft_strjoin(sev->path[i], tmp);
		if (access(str, X_OK) == 0)
		{
			free(*cmd);
			free(tmp);
			return (str);
		}
		free(str);
		i++;
	}
	free(tmp);
	return (cmd[0]);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
