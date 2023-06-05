/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:34:53 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/05 17:16:00 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_default(void)
{
	signal(SIGINT, handle_sign);
	signal(SIGQUIT, handle_quit);
}

void	signals_here_doc(void)
{
	
}

void	handle_quit(int sign)
{
	pid_t pid;
	int	status;

	(void)sign;
	pid = waitpid(-1,  &status, 0);
	if (pid == -1)
		SIG_IGN ;	
	else
	{
		write(1, "Quit (core dumped)\n", 20);
		return ;
	}
}

void	handle_sign(int sign)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (sign == SIGINT)
	{
		if (pid == -1)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
}
