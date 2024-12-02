#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * \brief { function_description }
 *
 * \param a { parameter_description }
 * \param b { parameter_description }
 *
 * \return { description_of_the_return_value }
 */
#define OPPOSITE_SIGNS(a, b) (((a) ^ (b)) >> 31)

/**
 * \brief Determines if safe.
 *
 * \param report The report
 * \param ptr The pointer
 *
 * \return True if safe, False otherwise.
 */
int is_safe(const char *const report, char **const ptr)
{
        char *token;
        int val, prev;
        int delta;

        prev  = (int) strtol(report, &token, 10);
        delta = 0;

        while ((*token != '\n') && (*token != '\0')) {
                val = (int) strtol(token, &token, 10);

                if (ptr != NULL)
                        *ptr = token;

                if ((abs(prev - val) == 0) || (abs(prev - val) > 3))
                        return 0;

                if (delta == 0)
                        delta = prev - val;
                else if (OPPOSITE_SIGNS(delta, prev - val))
                        return 0;

                prev = val;

                for (; *token == ' '; ++token)
                        ;
        }

        return 1;
}

/**
 * \brief Removes a previous.
 *
 * \param[in] buf The buffer
 * \param token The token
 *
 * \return { description_of_the_return_value }
 */
char *remove_prev(const char *const buf, char *token)
{
        for (; *token == ' '; --token)
                ;

        for (; (token >= buf) && (*token != ' '); --token) {
                if (*token != '\n')
                        *token = ' ';
        }

        return token;
}

/**
 * \brief { function_description }
 *
 * \param report The report
 * \param endptr The endptr
 *
 * \return { description_of_the_return_value }
 */
int dampaner(char *const report, char *endptr)
{
        char buf[BUFSIZ];
        char *token;

        strncpy(buf, report, endptr - report);

        for (; endptr >= report; endptr = token) {
                token = remove_prev(report, endptr);

                if (is_safe(report, NULL))
                        return 1;

                strncpy(report, buf, endptr - report);
        }

        return 0;
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
        char buf[BUFSIZ];
        char *token;
        int count;

        if (argc < 2)
                input = stdin;
        else
                input = fopen(argv[1], "r");

        if (input == NULL) {
                perror("Input stream");
                fprintf(stderr, "Usage: %s [input]\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        count = 0;

        while (fgets(buf, BUFSIZ, input)) {
                if (is_safe(buf, &token))
                        ++count;
                else if (dampaner(buf, token))
                        ++count;
        }

        printf("%d\n", count);

        fclose(input);

        return EXIT_SUCCESS;
}
