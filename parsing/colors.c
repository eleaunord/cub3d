#include "cub3d.h"

static void check_commas(t_data *game, char *line, int *i)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (line[*i] != '\0')
    {
        if (line[*i] == ',')
            count++;
    }
    if (count != 2)
        error_msg(game, "Invalid color format.\n", EXIT_FAILURE);
    return (count);
}
static void check_color_value(t_data *game, char *line, int *i, int *rgb)
{
    int j;

    check_commas(game, line, &i);
    j = 0;
    while (line[*i] != '\0')
    {
        while (line[*i] != '\0' && is_space(line[*i]))
            (*i)++;
        if (!ft_isdigit(line[*i]))
            error_msg(game, "Invalid color value.\n", EXIT_FAILURE);
        while (line[*i] != '\0' && ft_isdigit(line[*i]))
        {
            rgb[j] = rgb[j] * 10 + (rgb[*i] - '0');
            (*i)++;
        }
        if (rgb[j] > 255 || rgb[j] < 0)
            error_msg(game, "Invalid color value.\n", EXIT_FAILURE);
        j++;
        if (j == 3 && line[*i] != '\0')
            error_msg(game, "Invalid color format.\n", EXIT_FAILURE);
    }
    if (j != 3)
        error_msg(game, "Invalid color format.\n", EXIT_FAILURE);
}

void get_color_code(t_game *game, char *line, t_identifier *color)
{
    int i;
    int rgb[3];
    int color_hex;
    char *substring;

    i = 1;
    rgb[0] = 0;
    rgb[1] = 0;
    rgb[2] = 0;
    if (is_already_loaded(game, color))
        error_msg(game, "Color is already loaded.\n", EXIT_FAILURE);
    while (line[i] != '\0' && is_space(line[i]))
        i++;
    check_color_format(game, line, &i, rgb);
    color_hex = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    if (color == F)
        game->floor_color = color_hex;
    else if (color_type == C)
        game->ceiling_color = color_hex;
}