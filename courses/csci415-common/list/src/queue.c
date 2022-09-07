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


struct queue {
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
queue_init(struct queue *queue)
{
    INIT_LIST_HEAD(&queue->head);
    queue->size = 0;
}


static void
queue_print(const struct queue *queue)
{
    struct person *person;

    puts("front");
    list_for_each_entry(person, &queue->head, list) {
        printf("  %s, %d\n", person->name, person->age);
    }
    puts("back");
}


static void
queue_insert(struct queue *queue, struct person *person)
{
    list_add_tail(&person->list, &queue->head);
    queue->size += 1;
}


static struct person *
queue_remove(struct queue *queue)
{
    struct person *person;

    person = list_first_entry_or_null(&queue->head, struct person, list);
    if (person == NULL)
        mu_die("queue_remove: empty queue");

    list_del(&person->list);
    queue->size -= 1;

    return person;
}


static const struct person *
queue_first(struct queue *queue)
{
    struct person *person;

    person = list_first_entry_or_null(&queue->head, struct person, list);
    if (person == NULL)
        mu_die("queue_first: empty queue");

    return person;
}


static const struct person *
queue_last(struct queue *queue)
{
    if (list_empty(&queue->head))
        mu_die("queue_last: empty queue");

    return list_last_entry(&queue->head, struct person, list);
}


static size_t
queue_size(const struct queue *queue)
{
    return queue->size;
}


static void
queue_deinit(struct queue *queue)
{
    struct person *person, *tmp;

    list_for_each_entry_safe(person, tmp, &queue->head, list) {
        list_del(&person->list);
        person_free(person);
    }

    queue->size = 0;
}


int
main(void)
{
    struct queue queue;
    struct person *person;
    const struct person *tmp;

    queue_init(&queue);

    person = person_new("alice", 23);
    queue_insert(&queue, person);

    person = person_new("bob", 31);
    queue_insert(&queue, person);

    person = person_new("charles", 19);
    queue_insert(&queue, person);

    person = person_new("dave", 40);
    queue_insert(&queue, person);

    printf("There are %zu people in the queue\n", queue_size(&queue));

    queue_print(&queue);

    tmp = queue_first(&queue);
    printf("person{\"%s\", %d} is at the front of the queue\n", tmp->name, tmp->age);

    tmp = queue_last(&queue);
    printf("person{\"%s\", %d} is at the back of the queue\n", tmp->name, tmp->age);

    person = queue_remove(&queue);
    printf("dequeued person{\"%s\", %d}\n", person->name, person->age);
    person_free(person);

    queue_deinit(&queue);

    return 0;
}
