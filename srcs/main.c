#include <lem_in.h>

int main()
{
	t_parse infos = parsing();

	if (infos.error)
	{
		ft_printf("ERROR\n");
		return (2);
	}
	return (0);
}
