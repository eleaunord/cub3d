
#include "cub3d.h"

void free_map(t_data *game)
{
    int i;

    if (game->map)
    {
        i = 0;
        while (i < game->map_rows)
        {
            if (game->map[i])
                free(game->map[i]);
            i++;
        }
        free(game->map);
        game->map = NULL;
    }
}

void clean_up(t_data *game)
{
    if (!game)
        return;
    if (game->map)
        free_map(game);
    if (game->no)
        free(game->no);
    if (game->so)
        free(game->so);
    if (game->we)
        free(game->we);
    if (game->ea)
        free(game->ea);
}

int error_msg(t_data *game, char *mess, int status)
{
    clean_up(game);
    ft_putstr_fd("cub3D: Error", 2);
    if (mess)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(mess, 2);
    }
    exit(status);
}
