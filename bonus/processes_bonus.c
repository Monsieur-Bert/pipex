/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:09:03 by antauber          #+#    #+#             */
/*   Updated: 2024/12/19 08:57:28 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	exec_process(t_data *data, char *argv, char **env, int i_cmd)
{
	char	**params;
	int		size;

	data->only_cmd = rm_option_n_spaces(data, data->cmdp[i_cmd]);
	if (data->only_cmd == NULL)
		clean_data(data, 2, ERR_MALL, NULL);
	params = ft_split(argv, ' ');
	if (params == NULL)
		clean_data(data, 2, ERR_MALL, NULL);
	size = ft_count_words(argv, ' ');
	close_files(data);
	if (execve(data->only_cmd, params, env) == -1)
	{
		ft_free_tabstr(params, size);
		clean_data(data, 1, ERR_CMD, argv);
	}
}

void	child_process(t_data *data, char *argv, char **env, int i_cmd)
{
	if (i_cmd == data->n_cmdp - 1)
	{
		close(data->pipefd[0]);
		close (data->pipefd[1]);
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2, NULL);
		exec_process(data, argv, env, i_cmd);
	}
	else
	{
		close(data->pipefd[0]);
		if (dup2(data->pipefd[1], STDOUT_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2, NULL);
		close (data->pipefd[1]);
		exec_process(data, argv, env, i_cmd);
	}
}

void	processes(t_data *data, char *argv, char **env, int i_cmd)
{
	pid_t	pid;

	if (pipe(data->pipefd) == -1)
		clean_data(data, 1, ERR_PIPE, NULL);
	pid = fork();
	if (pid == -1)
		clean_data(data, 1, ERR_FORK, NULL);
	else if (pid == 0)
		child_process(data, argv, env, i_cmd);
	else
	{
		close(data->pipefd[1]);
		if (dup2(data->pipefd[0], STDIN_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2, NULL);
		close (data->pipefd[0]);
	}
}
