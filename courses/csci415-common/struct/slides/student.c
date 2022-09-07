#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int age;
    const char *name;
    double gpa;
    bool ugrad;
};

struct student_packed {
    int age;
    const char *name;
    double gpa;
    bool ugrad;
} __attribute__((packed));

static void
student_print(const struct student *s)
{
    printf("student{age=%d, name=\"%s\", gpa=%.2f, ugrad=%s}\n",
            s->age, s->name, s->gpa, s->ugrad ? "true" : "false");
}

static void
slide_4(void)
{
    struct student a = {23, "Alice", 3.9, false};

    puts("slide 4");
    student_print(&a);

}

static void
slide_5(void)
{
    struct student a = {23, "Alice"};

    puts("slide 5");
    student_print(&a);
}

static void
slide_6(void)
{
    struct student a = {
        .gpa = 3.9,
        .name = "Alice"};

    puts("slide 6");
    student_print(&a);
}

static void
slide_7(void)
{
    struct student a = { 0 };
    struct student b = { .age = 0 };

    puts("slide 7");
    student_print(&a);
    student_print(&b);
}

static void
slide_8(void)
{
    struct student a;

    memset(&a, 0x00, sizeof(a));

    puts("slide 7");
    student_print(&a);
}

static void
slide_11(void)
{
    puts("slide 11");
    printf("sizeof(struct student: %zu)\n", sizeof(struct student));
    printf("sizeof(struct student_packed: %zu)\n", sizeof(struct student_packed));
}

int
main(void)
{
    slide_4();
    slide_5();
    slide_6();
    slide_7();
    slide_8();
    slide_11();

    return 0;
}
