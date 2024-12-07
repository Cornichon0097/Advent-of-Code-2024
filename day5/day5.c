#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <aoc/util.h>

#define LIST_INIT NULL

struct node {
        int n;
        struct node *next;
};

typedef struct node *list_t;

int add(list_t *const list, int n)
{
        struct node *node = (struct node *) malloc(sizeof(struct node));

        if (node == NULL)
                return 0;

        node->n    = n;
        node->next = *list;
        *list      = node;

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

int parse(FILE *const stream, list_t **rules)
{
        char buf[BUFSIZ];
        char *token;
        int before, after;
        int maxsize, lsize;
        int i;

        *rules  = (list_t *) calloc(10, sizeof(list_t));
        maxsize = 10;
        lsize   = 0;

        while (fgets(buf, BUFSIZ, stream)) {
                before = (int) strtol(buf, &token, 10);

                if (*token != '|')
                        return lsize;

                after = (int) strtol(token + 1, NULL, 10);

                for (i = 0; i < maxsize; ++i) {
                        if (((*rules)[i] == NULL) || ((*rules)[i]->n == before))
                                break;
                }

                if (i >= maxsize) {
                        *rules = (list_t *)
                               realloc(*rules, (maxsize + 10) * sizeof(list_t));
                        memset((*rules) + maxsize, 0, 10);
                        maxsize = maxsize + 10;
                }

                if ((*rules)[i] == NULL) {
                        add((*rules) + i, before);
                        ++lsize;
                }

                add(&((*rules)[i]->next), after);
        }

        return lsize;
}

int check_order(const list_t *rules, int size, list_t update, const int page)
{
        list_t rule = NULL;
        int i;

        for (i = 0; i < size; ++i) {
                if (rules[i]->n == page)
                        rule = rules[i];
        }

        if (rule == NULL)
                return 1;

        for (; update != NULL; update = update->next) {
                for (; rule != NULL; rule = rule->next) {
                        if (rule->n == update->n)
                                return 0;
                }
        }

        return 1;
}

int middle_page(list_t list)
{
        struct node *middle;
        int next = 0;

        for (middle = list; list != NULL; list = list->next) {
                if (next)
                        middle = middle->next;

                next = !next;
        }

        return middle->n;
}

int correct_order(char *str, const list_t *const rules, const int size)
{
        list_t update = LIST_INIT;
        char *token;
        int page;
        int middle;

        do {
                page = (int) strtol(str, &token, 10);

                if (!check_order(rules, size, update, page))
                        return 0;

                add(&update, page);
                str = token + 1;
        } while (*token != '\n');

        middle = middle_page(update);
        clear(update);

        return middle;
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
        list_t *rules;
        int size;
        int result;
        int i;

        input  = input_stream(argc, argv);
        size   = parse(input, &rules);

        while (fgets(buf, BUFSIZ, input))
                result = result + correct_order(buf, rules, size);

        fclose(input);

        printf("%d\n", result);

        for (i = 0; i < size; ++i)
                clear(rules + i);

        free(rules);

        return EXIT_SUCCESS;
}
