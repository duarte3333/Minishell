/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:13:42 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/16 15:18:46 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (1);
	else if(!ft_strncmp(str, ">>", 2))
		return (2);
	else if(!ft_strncmp(str, "<", 1))
		return (3);
	else if(!ft_strncmp(str, ">", 1))
		return (4);
	return (0);
}

int	redirect(char **division, int *i, t_list *pre_list)
{
	if (!ft_strncmp(division[*i], ">>", 2))
	{
		if (pre_list->fd_master[1] > 2)
			close(pre_list->fd_master[1]);
		free(division[*i]);
		pre_list->fd_master[1] = open(division[++(*i)], O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	else if (!ft_strncmp(division[*i], "<<", 2))
	{
		if (pre_list->fd_master[0] > 2)
			close(pre_list->fd_master[0]);
		pre_list->fd_master[0] = ft_here_doc(division[++(*i)]);
	}
	else if (!ft_strncmp(division[*i], "<", 1))
	{
		if (pre_list->fd_master[0] > 2)
			close(pre_list->fd_master[0]);
		free(division[*i]);
		pre_list->fd_master[0] = open(division[++(*i)], O_RDONLY, 0644);
	}
	else if (!ft_strncmp(division[*i], ">", 1))
	{
		if (pre_list->fd_master[1] > 2)
			close(pre_list->fd_master[1]);
		free(division[*i]);
		pre_list->fd_master[1] = open(division[++(*i)], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
}

int	redirection(t_list	*pre_list, char **division, char **env)
{
	int		i;
	int		j;
	t_list	*temp;

	i = -1;
	j = 0;
	temp = pre_list;
	while (division[++i])
	{
		if (division[i][0] == 3 && pre_list->content[0])
		{
			ft_lstadd_back(&pre_list, ft_lstnew(ft_matrixlen(&division[i + 1]), env));
			if (temp->next)
				temp = temp->next;
			j = 0;
		}
		else if (check_token(division[i]))
			redirect(division, &i, temp);
		else if (division[i] && division[i][0] != 3)
		{
			temp->content[j] = ft_strdup(division[i]);
			j++;
		}
		free(division[i]);
	}
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
