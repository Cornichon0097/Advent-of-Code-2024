#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INSTRUCTIONS "md"

#define MUL "mul("

#define DO "do"

#define DONT "don't"

/**
 * @brief      { function_description }
 *
 * @param      str     The string
 * @param      result  The result
 *
 * @return     { description_of_the_return_value }
 */
char *mul(char *str, long *const result)
{
        long a, b;
        char *c;

        if (strncmp(str, MUL, strlen(MUL)) != 0)
                return str + 1;

        str = str + strlen(MUL);
        a = strtol(str, &c, 10);

        if (*c == ',') {
                str = c + 1;
                b = strtol(str, &c, 10);

                if (*c == ')')
                        *result = *result + a * b;
        }

        return str;
}

/**
 * @brief      "Do, or do not, there is no try" - Ydoa
 *
 * @param      str       The string
 * @param      multiply  The multiply
 *
 * @return     { description_of_the_return_value }
 */
char *yoda(char *str, int *const multiply)
{
        if (strncmp(str, DO, strlen(DO)) == 0)
                *multiply = 1;

        if (strncmp(str, DONT, strlen(DONT)) == 0)
                *multiply = 0;

        return str + 1;
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
        char *substr;
        int multiply;
        long result;

        if (argc < 2)
                input = stdin;
        else
                input = fopen(argv[1], "r");

        if (input == NULL) {
                perror("Input stream");
                fprintf(stderr, "Usage: %s [input]\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        result   = 0;
        multiply = 1;

        while (fgets(buf, BUFSIZ, input)) {
                substr = buf;

                while ((substr = strpbrk(substr, INSTRUCTIONS)) != NULL) {
                        switch (*substr) {
                        case 'm':
                                if (multiply)
                                        substr = mul(substr, &result);
                                else
                                        ++substr;
                                break;

                        case 'd':
                                substr = yoda(substr, &multiply);
                                break;

                        default:
                                break;
                        }
                }
        }

        printf("%ld\n", result);

        fclose(input);

        return EXIT_SUCCESS;
}
