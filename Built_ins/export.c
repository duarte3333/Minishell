/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:36:36 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/06 17:25:26 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_modify_print_matrix(char **array)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
	{
		printf("declare -x ");
		j = 0;
		flag = 0;
		while (array[i][j])
		{
			printf("%c", array[i][j]);
			if (array[i][j] == '=' && !flag)
			{
				printf("\"");
				flag = 1;
			}
			j++;
		}
		printf("\"\n");
	}
}

void	export_error(t_list **lst, char **str, int i)
{
	write(2, "minishell: export: \'", 21);
	write(2, ((*lst)->content[i]), ft_strlen((*lst)->content[i]));
	write(2, "\' not a valid identifier\n", 26);
	ft_free_matrix(&str);
	g_data.status = 1;
}

void	core_export(t_list **lst, char **str, int i)
{
	t_env	*lst_env_export;

	lst_env_export = NULL;
	if (!str || !str[0])
	{
		export_error(lst, str, i);
		return ;
	}
	lst_env_export = env_lst_search(str[0]);
	if (!lst_env_export)
		ft_envadd_back(&(g_data.env), \
		ft_envnew(ft_strdup((*lst)->content[i])));
	if (lst_env_export)
	{
		if (str[1])
		{
			free(lst_env_export->content);
			lst_env_export->content = ft_strdup((*lst)->content[i]);
		}
	}
	g_data.status = 0;
	ft_free_matrix(&str);
}

void	export_only(void)
{
	char	**char_env;

	char_env = ft_env_lst_to_arr(g_data.env);
	ft_bubble_sort(char_env, ft_matrixlen(char_env));
	ft_modify_print_matrix(char_env);
	ft_free_matrix(&char_env);
	return ;
}

void	__exec_export(t_list **lst)
{
	char	**str;
	int		i;

	if (!(*lst)->content[1])
		export_only();
	i = 1;
	while ((*lst)->content[i])
	{
		str = ft_split((*lst)->content[i], '=');
		if ((*lst)->content[i][0] == '=' || (str && !ft_str_islanum(str[0])) \
		|| ft_isdigit((*lst)->content[i][0]))
			export_error(lst, str, i);
		else
			core_export(lst, str, i);
		i++;
	}
}
