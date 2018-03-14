#include <lem_in.h>

t_pipe	*create_pipe(t_room *other_side)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->other_side = other_side;
	pipe->next = NULL;
	return (pipe);
}

int8_t	add_pipe(t_pipe **pipes, t_pipe *to_add)
{
	if (!to_add)
		return (0);
	to_add->next = *pipes;
	*pipes = to_add;
	return (1);
}

int8_t	add_pipe_to_rooms(t_room *r1, t_room *r2)
{
	if (!add_pipe(&(r1->pipes), create_pipe(r2)) || !add_pipe(&(r2->pipes), create_pipe(r1)))
		return (0);
	return (1);
}
