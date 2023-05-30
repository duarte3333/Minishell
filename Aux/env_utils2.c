#include "../minishell.h"

int	number_to_search(char *s1, char *s2) // caso o input seja $P ele nao retornar ATH=blahblahblah
{
	int	res;
	int	i;

	res = ft_strlen(s2);
	i = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	if (i > res)
		return (i);
	return (res);
}

char	*search_env(char **env, char *str)
{
	int	i;
	char	*temp;

	i = 0;
	while (env && env[i] && ft_strncmp(env[i], str, number_to_search(env[i], str)))
		i++;
	if (*str == '?')
		return (ft_itoa(g_data.status));
	if (!env[i] || !str || !*str)
		return ("");
	temp = (env[i] + ft_strlen(str));
	if (*temp == '=')
		temp++;
	return (temp);
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