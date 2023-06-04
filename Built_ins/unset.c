/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:37:13 by duarte33          #+#    #+#             */
/*   Updated: 2023/06/04 23:37:18 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	both_prev_next(t_env **lst)
{
	(*lst)->prev->next = (*lst)->next;
	(*lst)->next->prev = (*lst)->prev;
	*lst = (*lst)->prev;
}

void	env_delete_element(t_env **lst)
{
	t_env	*temp;

	temp = (*lst);
	if (lst && *lst)
	{
		if (!(*lst)->prev && !(*lst)->next)
			*lst = NULL;
		else if (!(*lst)->prev && (*lst)->next)
		{
			(*lst)->next->prev = NULL;
			*lst = (*lst)->next;
		}
		else if ((*lst)->prev && !(*lst)->next)
		{
			(*lst)->prev->next = NULL;
			*lst = (*lst)->prev;
		}
		else if ((*lst)->prev && (*lst)->next)
			both_prev_next(lst);
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}

/* Esta funcao replica o comportamento do unset, um comando built in
do bash. Para realizar foi eliminado o node do env da variavel que
escolhida no prompt para eliminar*/
void	__exec_unset(t_list **lst)
{
	t_env	*lst_env_export;
	int		i;

	i = 1;
	if (!(*lst)->content[1])
		return ;
	while ((*lst)->content[i])
	{
		lst_env_export = env_lst_search((*lst)->content[i]);
		if (lst_env_export)
			env_delete_element(&lst_env_export);
		i++;
	}
	g_data.status = 0;
}
