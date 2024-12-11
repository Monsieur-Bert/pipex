/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:59:37 by antauber          #+#    #+#             */
/*   Updated: 2024/12/10 11:57:08 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


/*	FORK		*/

// int	main(void)
// {
// 	pid_t	pid;
	
// 	printf("Fork Here\n\n");
// 	pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	printf("Sucess fork\n");
// 	if (pid == 0)
// 	{
// 		printf("I'm your son, pid = %d\n\n", pid);
// 	}
// 	else if (pid > 0)
// 	{
// 		printf("I'm the father of all = %d\n\n", pid);
// 		while(1)
// 			usleep(1);
// 	}
// 	return (0);
// }

/*	EXECVVE		*/
int main(int argc, char **argv, char **envp)
{
	execve(argv[1], &argv[1], envp);
	return 0;
}