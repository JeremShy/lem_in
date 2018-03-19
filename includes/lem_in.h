#ifndef LEM_IN_H
# define LEM_IN_H

# include <ft_printf.h>
# include <libft.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <stdio.h>
# define BUFF_SIZE_LEM 2

typedef enum e_state
{
	STATE_ANTS,
	STATE_ROOMS,
	STATE_PIPES,
	STATE_END
}	t_state;

typedef struct	s_room
{
	int64_t				id;
	int8_t				used;
	size_t				precedent_id;
	char				*name;
	int32_t				x;
	int32_t				y;
	size_t				distance;
	struct s_pipe		*pipes;
}				t_room;

typedef struct	s_pipe
{
	t_room			*other_side;
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_parse
{
	int8_t		error;
	t_room		*rooms;
	size_t		nbr_ants;
	size_t		nbr_rooms;
	size_t		nbr_rooms_max; // Nbr of \n in the file, size of  rooms[]
	int64_t		start_room_id;
	int64_t		end_room_id;
	size_t		nbr_ants_start;
	size_t		nbr_ants_end;
	char		*input;
} 				t_parse;

typedef struct s_path {
	size_t	size;
	t_room	**path; // array of rooms from end to start
}				t_path;

typedef struct s_path_container {
	t_path	*path;
	struct s_path_container	*next;
}				t_path_container;

void	free_dtab(char	**tab);
size_t	count_dtab_len(char **tab);
void	set_error(t_parse *parse_structure);
void	set_error_and_free(char **split, t_parse *parse_structure);
void	print_dtab(char **tab);
size_t		count_char(char c, const char *str);

typedef void (*t_state_function)(t_state *, t_parse *, char **);

void	parsing(t_parse *infos);
void	print_error_and_exit(int	nbr);
void	print_and_exit(int	nbr);
void	parse_ants(t_state *, t_parse *, char **);
void	parse_rooms(t_state *state, t_parse *parse_structure, char **ptr);
void	parse_pipes(t_state *state, t_parse *parse_structure, char **ptr);

int8_t	is_command(char *ptr);
int8_t	is_nombre_entier(char *str);
char	**ft_strsplit_lem_in(char const *s, char c);

int8_t	coords_already_exist(int x, int y, t_room const *rooms, size_t nbr_rooms);
int8_t	name_already_exists(const char *name, t_room const *rooms, size_t nbr_rooms);
t_room	*find_room(const char *name, t_room *rooms, size_t nbr_rooms);

t_pipe	*create_pipe(t_room *other_side);
int8_t	add_pipe(t_pipe **pipes, t_pipe *to_add);
int8_t	add_pipe_to_rooms(t_room *r1, t_room *r2);

void	print_pipes_for_all_rooms(t_room *rooms, size_t nbr_rooms);
void	print_pipes(t_room *room);
void	print_room(t_room *room);
void	print_all_rooms(t_room *rooms, size_t nbr_rooms);

void	algorithm(t_parse *parse_structure);

#endif
