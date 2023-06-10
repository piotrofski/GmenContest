#include "../includes/header.h"

void    splitting(t_var *var)
{
    int i;

    i = 0;
    var->num_lines = 0;
    while (var->maze_string[i] != '\0')
    {
        if (var->maze_string[i] == '\n')
            var->num_lines++;
        i++;
    }
    var->num_lines++;
    printf("\nnum_lines = %d", var->num_lines);
    var->maze_map = ft_split(var->maze_string, '\n');
    printf("\n");
    return ;
}

void update_map(t_var *var, int i, int j)
{
    int count_obs;

    count_obs = 0;
    if (var->maze_map[i][j] == '5')
        return ;
    if (j != var->num_lines)
    {
        if (var->maze_map[i][j + 1] == '#')
            count_obs++;
    }
    if (j != 0)
    {
        if (var->maze_map[i][j - 1] == '#' && j != 0)
            count_obs++;
    }
    if (i != var->num_lines)
    {
        if (var->maze_map[i + 1][j] == '#' && i != var->num_lines)
            count_obs++;
    }
    if (i != 0)
    {
        if (var->maze_map[i - 1][j] == '#'&& i != 0)
            count_obs++;
    }
    var->maze_map[i][j] = (4 - count_obs) + '0';
    return ;
}

void tr_map(t_var *var)
{
    int i;
    int j;

    i = 1;
    j = 1;
    while (i < var->num_lines - 1)
    {
        j = 1;
        while (j < var->num_lines - 1)
        {
            if (var->maze_map[i][j] != '#')
                update_map(var, i, j);
            j++;
        }
        i++;
    }
    var->maze_map[var->num_lines - 2][1] = '5';
    var->maze_map[1][var->num_lines - 2] = '5';
    return ;
}

void    print_solution(t_var *var)
{
    int i;
    int j;
    int index;
    
    j = 0;
    index = 0;
    i = 0;
    while (i < var->num_lines)
    {
        j = 0;
        while (j < var->num_lines)
        {
            if (var->maze_map[i][j] == '2' || var->maze_map[i][j] == '5')
            {
                index = (i * (var->num_lines + 1)) + j;
                var->maze_string[index] = 'O';
            }                
            j++;
        }
        i++;
    }
    printf("\n%s\n", var->maze_string);
    return ;
}

void check_cell(t_var *var, int i, int j)
{
    var->maze_map[i][j] = '#';
    if (var->maze_map[i][j + 1] != '#') 
        update_map(var, i, j + 1);
    else if (var->maze_map[i][j - 1] != '#') 
        update_map(var, i, j - 1);
    else if (var->maze_map[i + 1][j] != '#') 
        update_map(var, i + 1, j);
    else if (var->maze_map[i - 1][j] != '#') 
        update_map(var, i - 1, j);
    
}

void    resolve(t_var *var)
{
    int i;
    int j;
    int flag;

    i = 1;
    j = 1;
    flag = 0;
    while (flag != 1)
    {
        flag = 1;
        i = 1;
        while (i < var->num_lines - 1)
        {
            j = 1;
            while (j < var->num_lines - 1)
            {
                if ((var->maze_map[i][j] != '#') && (var->maze_map[i][j] != '5'))
                {
                    if (var->maze_map[i][j] == '1')
                        check_cell(var, i, j);
                    if (var->maze_map[i][j] != '2' && var->maze_map[i][j] != '5')
                        flag = 0;
                }
                j++;
            }
            i++;
        }
    }
    return ;
}