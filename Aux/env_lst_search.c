/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:17:47 by duarte33          #+#    #+#             */
/*   Updated: 2023/06/04 23:26:47 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	var_size(char *env_str)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	return (i);
}

/* Esta funcao procura na linked list do nosso minishell
se existe um node com um dado nome de variavel */
t_env	*env_lst_search(char *input_var)
{
	t_env	*lst_env;

	lst_env = g_data.env;
	env_go_head(&lst_env);
	while (lst_env && lst_env->content)
	{
		lst_env = lst_env->next;
		if (!lst_env)
			break ;
		if (!ft_strncmp(lst_env->content, input_var, ft_strlen(input_var)) \
			&& var_size(lst_env->content) == ft_strlen(input_var))
			return (lst_env);
	}
	return (NULL);
}
