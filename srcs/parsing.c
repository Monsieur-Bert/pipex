/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:14:54 by antauber          #+#    #+#             */
/*   Updated: 2024/12/13 15:56:12 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*rm_option_n_spaces(char *cmd)
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
	only_cmd = ft_substr(cmd, start, (end - start)); // ! security
	return (only_cmd);
}

char	*get_pathname(char *cmd, char *path)
{
	char	*buffer;
	char	*pathname;

	buffer = ft_strjoin(path, "/");
	pathname = ft_strjoin(buffer, cmd); // ! code a multiple arg join + secu
	free(buffer);
	return (pathname);
}

int	valid_path(t_data *data, int n_cmd)
{
	int		i;
	char	*buffer;
	
	i = 0;
	while (i < data->n_paths)
	{
		buffer = get_pathname(data->only_cmd, data->paths[i]); // ! security
		if (access(buffer, X_OK) != -1)
		{
			data->cmdp[n_cmd] = ft_strdup(buffer);
			free(buffer);
			return (1);
		}
		free(buffer);
		i++;
	}
	return (0);
}

void	get_paths(char **env, t_data *data)
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
	data->paths = ft_split(envp, ':'); // ! security
	free(envp);
}

void	check_arg(int argc)
{
	if (argc != 5) // ! change it for pipeline_bonus
	{
		ft_printf(2, "Error : Wrong number of arguments\n");
		exit (EXIT_FAILURE);
	}
}

void	parsing(int argc, char **argv, char **env, t_data *data)
{
	int		i_cmd;

	i_cmd  = 2;
	check_arg(argc);
	if (access(argv[1], F_OK) == -1)
		ft_error(1, ERR_INFILE);
	while (i_cmd < argc -1)
	{
		data->only_cmd = rm_option_n_spaces(argv[i_cmd]);
		if (access(data->only_cmd, X_OK) == -1)
		{
			if (data->paths == NULL)
				get_paths(env, data);
			if (!valid_path(data, i_cmd - 2))
				clean_data(data, 1, ERR_CMD);
		}
		else
			data->cmdp[i_cmd - 2] = ft_strdup(data->only_cmd); // ! security
		i_cmd++;
		free(data->only_cmd);
		data->only_cmd = NULL;
	}
	data->cmdp[i_cmd - 2] = NULL;
}
