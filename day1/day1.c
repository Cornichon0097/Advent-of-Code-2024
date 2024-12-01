#include <stdlib.h>
#include <stdio.h>

/**
 * \brief { function_description }
 *
 * \param stream The stream
 * \param left The left
 * \param right The right
 *
 * \return { description_of_the_return_value }
 */
int parse(FILE *const stream, int **const left, int **const right)
{
        char buf[BUFSIZ];
        int *l, *r;
        int nb_lines;
        int i;

        for (nb_lines = 0; fgets(buf, BUFSIZ, stream); ++nb_lines)
                ;

        *left = (int *) malloc(nb_lines * sizeof(int));
        *right = (int *) malloc(nb_lines * sizeof(int));

        l = *left;
        r = *right;

        fseek(stream, 0, SEEK_SET);

        for (i = 0; fgets(buf, BUFSIZ, stream); ++i)
                sscanf(buf, "%d %d\n", l++, r++);

        return nb_lines;
}

/**
 * \brief { function_description }
 *
 * \param[in] a { parameter_description }
 * \param[in] b { parameter_description }
 *
 * \return { description_of_the_return_value }
 */
int compare(const void *const a, const void *const b)
{
        return (*(int *) a - *(int *) b);
}

/**
 * \brief { function_description }
 *
 * \param[in] left The left
 * \param[in] right The right
 * \param[in] size The size
 *
 * \return { description_of_the_return_value }
 */
int count(const int *const left, const int *const right, const int size)
{
        int count = 0;
        int val, l, r;
        int i, j;

        val = left[0];

        for (r = 0; right[r] < val; ++r)
                ;

        for (i = 0; (i < size) && (r < size); i = l) {
                val = left[i];

                for (l = i; left[l] == val; ++l)
                        ;

                for (j = r; right[j] < val; ++j)
                        ;

                for (r = j; right[r] == val; ++r)
                        ;

                count = count + val * (l - i) * (r - j);
        }

        return count;
}

/**
 * \brief { function_description }
 *
 * \param[in] argc The count of arguments
 * \param argv The arguments array
 *
 * \return { description_of_the_return_value }
 */
int main(const int argc, const char *const argv[])
{
        FILE* input;
        int *left, *right;
        int size;

        if (argc < 2)
                input = stdin;
        else
                input = fopen(argv[1], "r");

        if (input == NULL) {
                perror("Input stream");
                fprintf(stderr, "Usage: %s [input]\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        size = parse(input, &left, &right);

        fclose(input);

        qsort(left, size, sizeof(int), &compare);
        qsort(right, size, sizeof(int), &compare);

        printf("%d\n", count(left, right, size));

        free(left);
        free(right);

        return EXIT_SUCCESS;
}
