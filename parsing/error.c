
#include "cub3d.h"

int error_msg(t_data *game, char *mess, int status)
{
    (void)game; // free everything later
    ft_putstr_fd("cub3D: Error", 2);
    if (mess)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(mess, 2);
    }
    exit(status);
}
