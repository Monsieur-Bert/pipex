/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:14:54 by antauber          #+#    #+#             */
/*   Updated: 2024/12/11 17:47:44 by antauber         ###   ########.fr       */
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
	only_cmd = ft_substr(cmd, start, (end - start));
	return (only_cmd);
}

// ! securiser les putians de mallocs
int	valid_path(char *cmd, char **paths, int count)
{
	int		i;
	char	*only_cmd;
	char	*buff1;
	char	*buff2;

	i = 0;
	only_cmd = rm_option_n_spaces(cmd);
	while (i < count)
	{
		buff1 = ft_strjoin(paths[i], "/"); // ! coder un strjoin a arg-multiples
		buff2 = ft_strjoin(buff1, only_cmd);
		free(buff1);
		if (access(buff2, X_OK) != -1 && only_cmd[0] != ' '
			&& only_cmd[0] != '\0')
		{
			free(buff2);
			free(only_cmd);
			return (1);
		}
		free(buff2);
		i++;
	}
	free(only_cmd);
	return (0);
}

void	get_paths(char *cmd, char **env)
{
	int		i;
	int		count;
	char	*envp;
	char	**paths;
	(void)cmd;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	envp = ft_strtrim(env[i], "PATH=");
	count = ft_count_words(envp, ':');
	paths = ft_split(envp, ':');
	free(envp);
	if (!valid_path(cmd, paths, count))
	{
		ft_free_tabstr(paths, count);
		ft_error();
	}
	ft_free_tabstr(paths, count);
}

void	parsing(int argc, char **argv, char **env)
{
	int	n_cmd;

	n_cmd  = 2;
	if (argc != 5) // ! change it for pipeline_bonus
	{
		ft_printf(2, "Error : Wrong number of arguments\n");
		exit (EXIT_FAILURE);
	}
	if (access(argv[1], F_OK) == -1) // ! pas necessaire car entree standard sera remplacee ?
		ft_error();
	while (n_cmd < argc -1)
	{
		if (access(argv[n_cmd], X_OK) == -1)
			get_paths(argv[n_cmd], env);
		n_cmd++;
	}
}

//casser la fucntion parsing et mettre ça a la place