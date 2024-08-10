#include "cub3d.h"

void get_path_to_texture(t_data *game, char *line, t_identifier *direction)
{
    char *path;
    int i;
    int fd;

    if (is_already_loaded(game, dir))
        error_msg(game, "Texture is already loaded.\n", EXIT_FAILURE);
    if (!line[2] || !is_space(line[2]))
        error_msg(game, "Invalid texture line.\n", EXIT_FAILURE);
    i = 2;
    while (line[i] && is_space(line[i]))
        i++;
    path = ft_strdup(line + i);
    if (!path)
        error_msg(game, "Memory fail for path.\n", EXIT_FAILURE);
    if (is_xpm(path, game) != 0)
        error_msg(game, "Invalid filename.\n", EXIT_FAILURE);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        game->error = 7;
    close(fd);
    //
    set_player_direction(game, path, dir);
}
