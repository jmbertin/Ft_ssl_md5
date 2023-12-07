#include "./libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp_list;

	if (new && alst)
	{
		if (!*alst)
		{
			*alst = new;
			return ;
		}
		tmp_list = ft_lstlast(*alst);
		tmp_list->next = new;
	}
}
