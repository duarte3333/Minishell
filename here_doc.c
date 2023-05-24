/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:58:47 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/24 21:25:40 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_doc(char *str)
{
	char		*in;
	int			fd[2];

	if (pipe(fd) == -1)
		perror("");
	write(0, ">", 1);
	in = get_next_line(0);
	while (1)
	{
		if ((ft_strncmp(in, str, ft_strlen(str)) == 0) && \
			(ft_strlen(in) - 1 == ft_strlen(str)))
			break ;
		write(0, ">", 1);
		write(fd[1], in, ft_strlen(in));
		free(in);
		in = get_next_line(0);
	}
	free(in);
	close(fd[1]);
	return (fd[0]);
}