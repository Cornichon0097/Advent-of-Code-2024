#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <aoc/util.h>

#define OPPOSITE_SIGNS(a, b) (((a) ^ (b)) >> 31)

/**
 * \brief      Determines whether the specified report is safe.
 *
 * \param[in]  report  The report
 *
 * \return     True if the specified report is safe, False otherwise.
 */
int is_safe(const char *const report)
{
        char *token;
        int val, prev;
        int delta;

        prev  = (int) strtol(report, &token, 10);
        delta = 0;

        while ((*token != '\n') && (*token != '\0')) {
                val = (int) strtol(token, &token, 10);

                if ((abs(prev - val) == 0) || (abs(prev - val) > 3))
                        return 0;

                if (delta == 0)
                        delta = prev - val;
                else if (OPPOSITE_SIGNS(delta, prev - val))
                        return 0;

                for (; *token == ' '; ++token)
                        ;

                prev = val;
        }

        return 1;
}

/**
 * \brief      Removes the next element pointed to by token in a report.
 *
 * \param      token  The report token
 *
 * \return     The next token.
 */
char *remove_next(char *token)
{
        for (; *token == ' '; ++token)
                ;

        for (; (*token != ' ') && (*token != '\n'); ++token)
                *token = ' ';

        return token;
}

/**
 * \brief      Determines whether the specified report is safe.
 *
 * The function dampaner() determines whether the specified report is safe,
 * accordirng to the Dampaner Problem. If removing a single level from an unsafe
 * report would make it safe, the report instead counts as safe.
 *
 * \param[in]  report  The report
 *
 * \return     True if the specified report is safe, False otherwise.
 */
int dampaner(const char *const report)
{
        char buf[BUFSIZ];
        char *token;

        token = strcpy(buf, report);

        while (*token != '\n') {
                token = remove_next(token);

                if (is_safe(buf))
                        return 1;

                memcpy(buf, report, token - buf);
        }

        return 0;
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
        char buf[BUFSIZ];
        int count;

        input = input_stream(argc, argv);
        count = 0;

        while (fgets(buf, BUFSIZ, input)) {
                /* if (is_safe(buf)) */
                if (dampaner(buf))
                        ++count;
        }

        printf("%d\n", count);

        fclose(input);

        return EXIT_SUCCESS;
}
