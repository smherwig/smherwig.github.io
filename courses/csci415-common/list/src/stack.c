#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"


#define mu_die(fmt, ...) \
    do { \
        fprintf(stderr, "[die] %s:%d " fmt "\n", \
                __func__, __LINE__,##__VA_ARGS__); \
        exit(1); \
    } while (0)


struct person {
    struct list_head list;
    char *name;
    int age;
};


struct stack {
    struct list_head head;
    size_t size;
    /* ... any other fields you might want ... */
};


static void *
mu_malloc(size_t n)
{
    void *p;

    p = malloc(n);
    if (p == NULL)
        mu_die("out of memory");

    return p;
}


static char *
mu_strdup(const char *s)
{
    char *p;

    p = strdup(s);
    if (p == NULL)
        mu_die("out of memory");

    return p;
}


static struct person *
person_new(const char *name, int age)
{
    struct person *person;

    person = mu_malloc(sizeof(*person));
    person->name = mu_strdup(name);
    person->age = age;

    return person;
}


static void
person_free(struct person *person)
{
    free(person->name);
    free(person);
}


static void
stack_init(struct stack *stack)
{
    INIT_LIST_HEAD(&stack->head);
    stack->size = 0;
}


static void
stack_print(const struct stack *stack)
{
    struct person *person;

    puts("top");
    list_for_each_entry(person, &stack->head, list) {
        printf("  %s, %d\n", person->name, person->age);
    }
    puts("bottom");
}


static void
stack_push(struct stack *stack, struct person *person)
{
    list_add(&person->list, &stack->head);
    stack->size += 1;
}


static struct person *
stack_pop(struct stack *stack)
{
    struct person *person;

    person = list_first_entry_or_null(&stack->head, struct person, list);
    if (person == NULL)
        mu_die("popping from an empty stack");

    list_del(&person->list);
    stack->size -= 1;

    return person;
}


static const struct person *
stack_peek(struct stack *stack)
{
    struct person *person;

    person = list_first_entry_or_null(&stack->head, struct person, list);
    if (person == NULL)
        mu_die("peeking from an empty stack");

    return person;
}


static size_t
stack_size(const struct stack *stack)
{
    return stack->size;
}


static void
stack_deinit(struct stack *stack)
{
    struct person *person, *tmp;

    list_for_each_entry_safe(person, tmp, &stack->head, list) {
        list_del(&person->list);
        person_free(person);
    }

    stack->size = 0;
}


int
main(void)
{
    struct stack stack;
    struct person *person;
    const struct person *tmp;

    stack_init(&stack);

    person = person_new("alice", 23);
    stack_push(&stack, person);

    person = person_new("bob", 31);
    stack_push(&stack, person);

    person = person_new("charles", 19);
    stack_push(&stack, person);

    person = person_new("dave", 40);
    stack_push(&stack, person);

    person = stack_pop(&stack);
    printf("pop'd person{\"%s\", %d}\n", person->name, person->age);
    printf("stack size: %zu\n", stack_size(&stack));
    person_free(person);

    tmp = stack_peek(&stack);
    printf("person{\"%s\", %d} is on top of stack\n", tmp->name, tmp->age);

    stack_print(&stack);

    stack_deinit(&stack);

    return 0;
}
