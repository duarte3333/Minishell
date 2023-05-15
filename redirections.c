/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:13:42 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/15 19:51:09 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token(char **str)
{
	if (!strcmp(str[0], "<<"))
		return (1);
	else if(!strcmp(str[0], ">>"))
		return (2);
	else if(!strcmp(str[0], "<"))
		return (3);
	else if(!strcmp(str[0], ">"))
		return (4);
	return (0);
}

// int	redirection(char *word)
// {
// 	int	i;

// 	i = 0;
// 	while ((*lst)->content[i])
// 	{
// 		if (!strcmp((*lst)->content[i], "<<"))
// 		{
// 			close((*lst)->fd[0]);
// 			(*lst)->fd[0] = ft_here_doc(*lst, i);
// 		}
// 		else if(!strcmp((*lst)->content[i], ">>"))
// 		{
// 			close((*lst)->fd[1]);
// 			(*lst)->prev->fd[1] = open((*lst)->content[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
// 		}
// 		else if(!strcmp((*lst)->content[i], "<"))
// 		{
// 			close((*lst)->fd[0]);
// 			(*lst)->fd[0] = open((*lst)->content[i + 1], O_RDONLY, 0644);
// 		}
// 		else if(!strcmp((*lst)->content[i], ">"))
// 		{
// 			close((*lst)->fd[1]);
// 			(*lst)->fd[1] = open((*lst)->content[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);	
// 		}
// 		// if ((*lst)->prev->fd[1] == -1 || (*lst)->fd[0] == -1)
// 		// {
// 		// 	perror("");
// 		// 	exit(0);
// 		// }
// 		i++;
// 	}
// 	return (0);
//}
