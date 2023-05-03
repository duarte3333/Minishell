#include "../lexer.h"

//Esta funcao aloca memoria para n bytes com o malloc
//e depois coloca zeros em todos os bytes que alocou
void	*ft_calloc(size_t nelem, size_t elsize)
{
	char	*arr;
	size_t	i;

	i = -1;
	arr = malloc(elsize * nelem);
	if (!arr)
		return (NULL);
	if (nelem != 0)
	{
		while (++i < nelem)
			arr[i] = 0;
		return ((void *)arr);
	}
	return ((void *)arr);
}