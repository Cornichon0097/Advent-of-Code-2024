#include <stdlib.h>
#include <stdio.h>

#include <aoc/util.h>

/**
 * \brief      Parses input stream.
 *
 * \param      stream  The input stream
 * \param      left    The left list
 * \param      right   The right list
 *
 * \return     The size of left and right lists.
 */
int parse(FILE *const stream, int **const left, int **const right)
{
        char buf[BUFSIZ];
        int *l, *r;
        int size = lines_count(stream);

        *left  = (int *) malloc(size * sizeof(int));
        *right = (int *) malloc(size * sizeof(int));

        l = *left;
        r = *right;

        while (fgets(buf, BUFSIZ, stream))
                sscanf(buf, "%d %d\n", l++, r++);

        return size;
}

/**
 * \brief      Compares two integers.
 *
 * \param[in]  a     The first integer
 * \param[in]  b     The second integer
 *
 * \return     The distance between left and right lists.
 */
int compare(const void *const a, const void *const b)
{
        return (*(int *) a - *(int *) b);
}

/**
 * \brief      Computes distance between two lists.
 *
 * \param      left   The left list
 * \param      right  The right list
 * \param[in]  size   The size of both lists
 *
 * \return     The distance between left and right lists.
 */
int distance(int *const left, int *const right, const int size)
{
        int distance = 0;
        int i;

        qsort(left, size, sizeof(int), &compare);
        qsort(right, size, sizeof(int), &compare);

        for (i = 0; i < size; ++i)
                distance = distance + left[i] + right[i];

        return distance;
}

/**
 * \brief      Computes similarity score between two lists.
 *
 * \param      left   The left list
 * \param      right  The right list
 * \param[in]  size   The size of both lists
 *
 * \return     The similarity score between left and right lists.
 */
int sim_score(int *const left, int *const right, const int size)
{
        int score = 0;
        int val, l, r;
        int i, j;

        qsort(left, size, sizeof(int), &compare);
        qsort(right, size, sizeof(int), &compare);

        for (i = 0, r = 0; (i < size) && (r < size); i = l) {
                val = left[i];

                for (l = i; left[l] == val; ++l)
                        ;

                for (j = r; right[j] < val; ++j)
                        ;

                for (r = j; right[r] == val; ++r)
                        ;

                score = score + val * (l - i) * (r - j);
        }

        return score;
}

/**
 * \brief      Main function.
 *
 * \param[in]  argc  The count of arguments
 * \param[in]  argv  The arguments array
 *
 * \return     The exit status.
 */
int main(const int argc, const char *const argv[])
{
        FILE *input;
        int *left, *right;
        int size;

        input = input_stream(argc, argv);
        size  = parse(input, &left, &right);
        fclose(input);

        /* printf("%d\n", distance(left, right, size)); */
        printf("%d\n", sim_score(left, right, size));

        free(left);
        free(right);

        return EXIT_SUCCESS;
}
