#include "cub3d.h"

void get_textures_and_colors(char *line, t_data *game)
{
    if (line && line[0] == 'N' && line[1] == 'O')
        get_path_to_texture(N, line, game);
    else if (line && line[0] == 'S' && line[1] == 'O')
        get_path_to_texture(S, line, game);
    else if (line && line[0] == 'E' && line[1] == 'A')
        get_path_to_texture(E, line, game);
    else if (line && line[0] == 'W' && line[1] == 'E')
        get_path_to_texture(W, line, game);
    else if (line && line[0] == 'F')
        get_color_code(F, line, game);
    else if (line && line[0] == 'C')
        get_color_code(C, line, game);
    else if (line && line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W' && line[0] != 'F' && line[0] != 'C')
        error_msg(game, "Invalid identifier format.\n", EXIT_FAILURE);
}

static void route_lines(t_game *game, char *line)
{
    game->line = NULL;
    if (ft_strchr(line, '.') || ft_strchr(line, ','))
        game->line = ft_strtrim(line, " \t\r");
    game->line_tmp = line;
    parse_textures_and_colors(game, game->line);
    game->line_tmp = NULL;
    if (game->line)
        free(game->line);
    else if ((line[0] == '1' || line[0] == ' ') &&
             (all_textures_and_colors_set(game)))
        get_map_size(game, line);
    else if (!is_empty_line(line))
    {
        free(line);
        close(game->fd);
        error_msg(game, "Invalid line in input file.\n", EXIT_FAILURE);
    }
    free(line);
}

void parse_file(t_game *game, char *file)
{
    char *line;
    char *tmp_line;

    game->fd = open(file, O_RDONLY);
    if (game->fd < 0)
        error_msg(game, "Could not open map file.\n", EXIT_FAILURE);
    line = get_next_line(game->fd);
    while (line != NULL)
    {
        tmp_line = ft_strtrim(line, "\r\n");
        free(line);
        route_lines(game, tmp_line);
        free(tmp_line);
        line = get_next_line(game->fd);
    }
    close(game->fd);
    // if (!all_textures_and_colors_set(game))
    //     error_msg(game, "Missing textures or colors in map file.\n", EXIT_FAILURE);
    // parse_map(game, file);
}
