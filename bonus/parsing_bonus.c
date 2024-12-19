/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:14:54 by antauber          #+#    #+#             */
/*   Updated: 2024/12/19 08:36:53 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*rm_option_n_spaces(t_data *data, char *cmd)
{
	char	*only_cmd;
	int		start;
	int		end;

	start = 0;
	while (cmd[start] && cmd[start] == ' ')
		start++;
	end = start;
	while (cmd[end] && cmd[end] != ' ')
		end++;
	only_cmd = ft_substr(cmd, start, (end - start));
	if (only_cmd == NULL)
		clean_data(data, 2, ERR_MALL, NULL);
	return (only_cmd);
}

int	valid_path(t_data *data, int n_cmd)
{
	int		i;
	char	*pathname;

	i = 0;
	while (i < data->n_paths)
	{
		pathname = ft_strjoinvar(3, data->paths[i], "/", data->only_cmd);
		if (pathname == NULL)
			clean_data(data, 2, ERR_MALL, NULL);
		if (access(pathname, X_OK) != -1)
		{
			data->cmdp[n_cmd] = ft_strdup(pathname);
			free(pathname);
			return (1);
		}
		free(pathname);
		i++;
	}
	return (0);
}

void	get_paths(t_data *data, char **env)
{
	int		i;
	char	*envp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	envp = ft_strtrim(env[i], "PATH=");
	data->n_paths = ft_count_words(envp, ':');
	data->paths = ft_split(envp, ':');
	if (data->paths == NULL)
		clean_data(data, 2, ERR_MALL, NULL);
	free(envp);
}

void	parsing(t_data *data, int argc, char **argv, char **env)
{
	int		i_cmd;

	i_cmd = 2;
	while (i_cmd < argc -1)
	{
		data->only_cmd = rm_option_n_spaces(data, argv[i_cmd]);
		if (access(data->only_cmd, X_OK) == -1)
		{
			if (data->paths == NULL)
				get_paths(data, env);
			if (!valid_path(data, i_cmd - 2))
				data->cmdp[i_cmd - 2] = ft_strdup(data->only_cmd);
		}
		else
		{
			data->cmdp[i_cmd - 2] = ft_strdup(data->only_cmd);
			if (data->cmdp[i_cmd - 2] == NULL)
				clean_data(data, 2, ERR_MALL, NULL);
		}
		i_cmd++;
		free(data->only_cmd);
		data->only_cmd = NULL;
	}
	data->cmdp[i_cmd - 2] = NULL;
}
