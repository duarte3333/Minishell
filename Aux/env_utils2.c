#include "../minishell.h"

char	*search_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env && ft_strncmp(env[i], str, ft_strlen(str)))
		i++;
	return (env[i]);
}

int	ft_env_lstsize(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}