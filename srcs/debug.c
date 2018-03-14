#include <lem_in.h>

void	print_pipes_for_all_rooms(t_room *rooms, size_t nbr_rooms)
{
	size_t	i;

	i = 0;
	while (i < nbr_rooms)
	{
		print_pipes(rooms + i);
		i++;
	}

}

void	print_pipes(t_room *room)
{
	t_pipe *pipe;

	pipe = room->pipes;
	ft_printf("Pipes for room [%s] : \n", room->name);
	while (pipe)
	{
		ft_printf("\t[%s] -> [%s]\n", room->name, pipe->other_side->name);
		pipe = pipe->next;
	}
}
