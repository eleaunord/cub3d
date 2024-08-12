#include "cub3d.h"

static void set_direction(t_data *game, char *path, t_identifier direction)
{
    if (direction == N)
        game->no = path;
    else if (direction == S)
        game->so = path;
    else if (direction == W)
        game->we = path;
    else if (direction == E)
        game->ea = path;
}
void get_path_to_texture(t_identifier direction, char *line, t_data *game)
{
    char *path;
    int i;
    int fd;

    if (is_already_loaded(game, direction))
        error_msg(game, "Texture is already loaded.\n", EXIT_FAILURE);
    if (!line[2] || !is_space(line[2]))
        error_msg(game, "Invalid texture line.\n", EXIT_FAILURE);
    i = 2;
    while (line[i] && is_space(line[i]))
        i++;
    path = ft_strdup(line + i);
    if (!path)
        error_msg(game, "Memory fail for path.\n", EXIT_FAILURE);
    if (is_xpm(path) != 0)
        error_msg(game, "Invalid filename.\n", EXIT_FAILURE);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        error_msg(game, "Invalid texture file.\n", EXIT_FAILURE);
    close(fd);
    set_direction(game, path, direction);
}
