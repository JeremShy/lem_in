#include <lem_in.h>

int main()
{
	t_parse parse_structure;

	parsing(&parse_structure);
	if (parse_structure.error)
	{
		ft_printf("ERROR\n");
		return (2);
	}
	algorithm(&parse_structure);
	return (0);
}
