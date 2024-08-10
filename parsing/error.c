
#include "cub3d.h"

void error_msg(t_data *game, char *mess, int num)
{
    ft_putstr_fd("cub3D: Error", 2);
    if (mess)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(mess, 2);
    }
    ft_putstr_fd("\n", 2);
    return (num);
}
