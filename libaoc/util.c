#include <stdlib.h>
#include <stdio.h>

#include <aoc/util.h>

/**
 * \brief      Determines the input stream.
 *
 * \param[in]  argc  The count of arguments
 * \param[in]  argv  The arguments array
 *
 * \return     The input stream.
 */
FILE *input_stream(const int argc, const char *const argv[])
{
        FILE *input;

        if (argc < 2)
                return stdin;

        input = fopen(argv[1], "r");

        if (input == NULL) {
                perror("Input stream");
                fprintf(stderr, "Usage: %s [input]\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        return input;
}

/**
 * \brief      Counts number of lines.
 *
 * \param      stream  The stream
 *
 * \return     The number of lines of stream.
 */
int lines_count(FILE *const stream)
{
        long offset = ftell(stream);
        int count = 0;
        int c;

        fseek(stream, 0L, SEEK_SET);

        for (c = getc(stream); c != EOF; c = getc(stream)) {
                if (c == '\n')
                        ++count;
        }

        fseek(stream, offset, SEEK_SET);

        return count;
}

/**
 * \brief      Return lines size.
 *
 * \param      stream  The stream
 *
 * \return     The lines size of stream.
 */
int lines_size(FILE *const stream)
{
        long offset = ftell(stream);
        int size = 0;
        int c;

        fseek(stream, 0L, SEEK_SET);

        for (c = getc(stream); (c != EOF) && (c != '\n'); c = getc(stream))
                ++size;

        fseek(stream, offset, SEEK_SET);

        return size;
}
