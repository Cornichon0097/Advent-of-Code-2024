#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <aoc/util.h>

#define XMAS "XMAS"

#define X_MAS "MS"

/**
 * \brief      Determines if there is an XMAS.
 *
 * \param      grid    The grid
 * \param[in]  width   The width
 * \param[in]  height  The height
 * \param[in]  x       The x position
 * \param[in]  y       The y position
 * \param[in]  dx      The x delta
 * \param[in]  dy      The y delta
 *
 * \return     True if there is an XMAS at (x, y), in (dx, dy) direction.
 */
int xmas(char **const grid, const int width, const int height,
         int x, int y, const int dx, const int dy)
{
        size_t i;

        for (i = 1; i < strlen(XMAS); ++i) {
                x = x + dx;
                y = y + dy;

                if ((x < 0) || (x >= width))
                        return 0;

                if ((y < 0) || (y >= height))
                        return 0;

                if (grid[y][x] != XMAS[i])
                        return 0;
        }

        return 1;
}

/**
 * \brief      Counts XMAS
 *
 * \param      grid    The grid
 * \param[in]  width   The width
 * \param[in]  height  The height
 * \param[in]  x       The x position
 * \param[in]  y       The y position
 *
 * \return     The number of XMAS in grid at (x, y).
 */
int count(char **const grid, const int width, const int height,
          const int x, const int y)
{
        return xmas(grid, width, height, x, y, 0, 1)
               + xmas(grid, width, height, x, y, 1, 0)
               + xmas(grid, width, height, x, y, 1, 1)
               + xmas(grid, width, height, x, y, 0, -1)
               + xmas(grid, width, height, x, y, -1, 0)
               + xmas(grid, width, height, x, y, -1, -1)
               + xmas(grid, width, height, x, y, 1, -1)
               + xmas(grid, width, height, x, y, -1, 1);
}

/**
 * \brief      Determines if there is an X-MAS
 *
 * \param      grid    The grid
 * \param[in]  width   The width
 * \param[in]  height  The height
 * \param[in]  x       The x position
 * \param[in]  y       The y position
 *
 * \return     True if there is an X-MAS at (x, y), False otherwise.
 */
int x_mas(char **const grid, const int width, const int height,
          const int x, const int y)
{
        if ((x - 1) < 0)
                return 0;

        if ((x + 1) >= width)
                return 0;

        if ((y - 1) < 0)
                return 0;

        if ((y + 1) >= height)
                return 0;

        switch (grid[x - 1][y - 1]) {
        case 'M':
                if (grid[x + 1][y + 1] != 'S')
                        return 0;
                break;

        case 'S':
                if (grid[x + 1][y + 1] != 'M')
                        return 0;
                break;

        default:
                return 0;
                break;
        }

        switch (grid[x + 1][y - 1]) {
        case 'M':
                if (grid[x - 1][y + 1] != 'S')
                        return 0;
                break;

        case 'S':
                if (grid[x - 1][y + 1] != 'M')
                        return 0;
                break;

        default:
                return 0;
                break;
        }

        return 1;
}

/**
 * \brief      Main function.
 *
 * \param[in]  argc  The count of arguments
 * \param[in]  argv  The arguments array
 *
 * \return     Exit status.
 */
int main(const int argc, const char *const argv[])
{
        FILE *input;
        char **grid;
        int width, height;
        int result;
        int i, j;

        input  = input_stream(argc, argv);
        height = lines_count(input);
        width  = lines_size(input);

        grid = (char **) malloc(height * sizeof(char *));

        for (i = 0; i < height; ++i) {
                grid[i] = (char *) malloc((width + 1) * sizeof(char));
                fread(grid[i], (width + 1), sizeof(char), input);
        }

        fclose(input);

        result = 0;

        for (i = 0; i < height; ++i) {
                for (j = 0; j < width; ++j) {
                        /* if (grid[i][j] == 'X')
                                result += count(grid, width, height, j, i); */
                        if (grid[i][j] == 'A')
                                result += x_mas(grid, width, height, j, i);
                }
        }

        printf("%d\n", result);

        for (i = 0; i < height; ++i)
                free(grid[i]);

        free(grid);

        return EXIT_SUCCESS;
}
