#include "../minishell.h"


void	env_go_head(t_env **lst)
{
	while ((lst) && (*lst) && (*lst)->prev)
		(*lst) = (*lst)->prev;
}

t_env	*lst_search(char *name_var)
{
	t_env	*lst_env;
	
	lst_env = g_data.env;
	while (lst_env && lst_env->content)
	{
		lst_env = lst_env->next;
		if (!lst_env)
			break ;
		if (!ft_strncmp(lst_env->content, name_var, ft_strlen(name_var)))
		{
			printf("%s [no search]\n", lst_env->content);
			return (lst_env);
		}
	}
	return (NULL);
}

void	__exec_export(char **env, t_list **lst)
{
	char	**str;
	t_env	*lst_env_export;
	
	(void)env;
	if (!(*lst)->content[1])
		;//sort(g_data.env);
	str = ft_split((*lst)->content[1], '=');	
	lst_env_export = lst_search(str[0]);
	if (!lst_env_export)
		ft_envadd_back(&(g_data.env), ft_envnew(ft_strdup((*lst)->content[1])));
	//printf("%s [antes_str]\n", lst_env_export->content);
	if (lst_env_export)
	{
		free(lst_env_export->content);
		lst_env_export->content = ft_strdup((*lst)->content[1]);
		printf("%s [str_pos_head]\n", lst_env_export->content);
	}
	ft_free_matrix(&str);

	//printf("%s [str]\n", lst_env_export->content);
	//env_go_head(&lst_env_export);
	//g_data.env = lst_env_export;
	// while (g_data.env && g_data.env->content)
	// {
	// 	printf("%s\n", g_data.env->content);
	// 	if (!g_data.env->next)
	// 		break ;
	// 	g_data.env = g_data.env->next;
	// }
	// env_go_head(&lst_env_export);
}