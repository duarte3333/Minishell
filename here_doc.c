/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:58:47 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/05 17:16:35 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Esta realiza o comportamento do comando << no bash */
int	ft_here_doc(char *str)
{
	char		*in;
	int			fd[2];

	if (pipe(fd) == -1)
		perror("");
	while (1)
	{
		write(0, ">", 1);
		in = get_next_line(0);
		if (!in)
		{
			write(2, "warning: here-document at line 1 delimited by end-of-file (wanted `", 67);
			write(2, str, ft_strlen(str));
			write(2, "')\n", 3);
			break ;
		}
		if ((ft_strncmp(in, str, ft_strlen(str)) == 0) && \
			(ft_strlen(in) - 1 == ft_strlen(str)))
			break ;
		write(fd[1], in, ft_strlen(in));
		free(in);
	}
	free(in);
	close(fd[1]);
	return (fd[0]);
}
