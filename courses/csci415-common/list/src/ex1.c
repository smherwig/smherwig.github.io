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


struct group {
    struct list_head head;
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
group_init(struct group *group)
{
    INIT_LIST_HEAD(&group->head);
}


static void
group_print(const struct group *group)
{
    struct person *person;

    list_for_each_entry(person, &group->head, list) {
        printf("%s, %d\n", person->name, person->age);
    }
}


static void
group_deinit(struct group *group)
{
    struct person *person, *tmp;

    list_for_each_entry_safe(person, tmp, &group->head, list) {
        list_del(&person->list);
        person_free(person);
    }
}


int
main(void)
{
    struct group group;
    struct person *person;

    group_init(&group);

    person = person_new("alice", 23);
    list_add(&person->list, &group.head);

    person = person_new("bob", 31);
    list_add(&person->list, &group.head);

    person = person_new("charles", 19);
    list_add(&person->list, &group.head);

    group_print(&group);

    group_deinit(&group);

    return 0;
}
