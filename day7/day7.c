#include <stdlib.h>
#include <stdio.h>

#include <aoc/util.h>

#define LIST_INIT NULL

struct node {
        long n;
        struct node *next;
};

typedef struct node *list_t;

int add(list_t *const list, long n)
{
        struct node *node = (struct node *) malloc(sizeof(struct node));
        struct node *iter;

        if (node == NULL)
                return 0;

        node->n    = n;
        node->next = NULL;

        if (*list == NULL)
                *list = node;
        else {
                for (iter = *list; iter->next != NULL; iter = iter->next)
                        ;

                iter->next = node;
        }

        return 1;
}

void clear(list_t *const list)
{
        struct node *iter;
        struct node node;

        for (iter = *list; iter != NULL; iter = node.next) {
                node = *iter;
                free(iter);
        }

        *list = NULL;
}

long concat(const long a, const long b)
{
        long pow = 10L;

        while(pow <= b)
                pow = pow * 10L;

        return a * pow + b;
}

int solve(const long expected, long cur, const list_t val, const char op)
{
        if (op == '+')
                cur = cur + val->n;
        else if (op == '*')
                cur = cur * val->n;
        else /* if (op == '|') */
                cur = concat(cur, val->n);

        if (val->next == NULL)
                return cur == expected;

        return (solve(expected, cur, val->next, '+')
                || solve(expected, cur, val->next, '*')
                || solve(expected, cur, val->next, '|'));
}

long equation(const long expected, const list_t val)
{
        if ((solve(expected, val->n, val->next, '+'))
            || (solve(expected, val->n, val->next, '*'))
            || (solve(expected, val->n, val->next, '|')))
                return expected;

        return 0L;
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
        char *str, *token;
        list_t val;
        long expected;
        long result;

        input = input_stream(argc, argv);
        val   = LIST_INIT;

        while (fgets(buf, BUFSIZ, input)) {
                expected = strtol(buf, &token, 10);
                ++token;

                while (*token != '\n') {
                        str = token;
                        add(&val, strtol(str, &token, 10));
                }

                result = result + equation(expected, val);
                clear(&val);
        }

        fclose(input);

        printf("%ld\n", result);

        return EXIT_SUCCESS;
}
