#include "../includes/header.h"

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        clock_t start_time;
        clock_t end_time;
        double execution_time;
        int dimension = atoi(argv[1]);
        int density = atoi(argv[2]);
        t_var var;
    
        start_time = clock();
        dimension = (dimension < 0) ? -dimension : dimension; //args error check
        if (getReadURL(dimension, &var, density) == 1) //writes in the terminal & in the maze_file
            return (0);
        printf("\n%s\n", var.maze_string);
        splitting(&var);
        tr_map(&var);
        resolve(&var);
        print_solution(&var);
        end_time = clock();
        execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("\nExecution time: %.4f seconds\n", execution_time);
    }
    else
        printf("Please write the dimension(positive integer) and density(float between 0 and 1) of the maze such as: ./a.out X X\n");
    return (0);
}
