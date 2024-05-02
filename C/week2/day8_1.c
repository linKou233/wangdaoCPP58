#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_STUDENTS 5
#define NUM_SUBJECTS 3

typedef struct Student {
    char id[20];
    char name[50];
    int scores[NUM_SUBJECTS];
    int total_score;
}Student;

void input_students(Student students[NUM_STUDENTS]) {
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("请输入学生 %d 学号: ", i + 1);
        scanf("%s", students[i].id);
        printf("请输入学生 %d 姓名: ", i + 1);
        scanf("%s", students[i].name);
        students[i].total_score = 0;
        
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            printf("请输入学生 %d 第 %d 门成绩: ", i + 1, j + 1);
            scanf("%d", &students[i].scores[j]);
            students[i].total_score += students[i].scores[j];
        }
        puts("--------------------------");
    }
}

void print_student(Student *student) {
    printf("学号: %s, 姓名: %s, 成绩: ", student->id, student->name);
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("%d ", student->scores[i]);
    }
    printf("\n");
}

void print_max_scores(Student students[NUM_STUDENTS]) {
    Student *max_students[NUM_SUBJECTS] = {&students[0], &students[0], &students[0]};
    for (int i = 1; i < NUM_STUDENTS; i++) {
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            if (students[i].scores[j] > max_students[j]->scores[j]) {
                max_students[j] = &students[i];
            }
        }
    }
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("第 %d 门课程最高成绩: ", i + 1);
        print_student(max_students[i]);
    }
}

void print_average_scores(Student students[NUM_STUDENTS]) {
    int total_scores[NUM_SUBJECTS] = {0, 0, 0};
    for (int i = 0; i < NUM_STUDENTS; i++) {
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            total_scores[j] += students[i].scores[j];
        }
    }
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("第 %d 门课程平均成绩: %.2f\n", i + 1, (double)total_scores[i] / NUM_STUDENTS);
    }
}

int compare_students(const void *a, const void *b) {
    Student *student_a = (Student *)a;
    Student *student_b = (Student *)b;
    return student_b->total_score - student_a->total_score;
}

void sort_students(Student students[NUM_STUDENTS]) {
    qsort(students, NUM_STUDENTS, sizeof(Student), compare_students);
}

int main() {
    Student students[NUM_STUDENTS];
    input_students(students);
    print_max_scores(students);
    print_average_scores(students);
    sort_students(students);
    printf("学生排名(按总分从高到低):\n");
    for (int i = 0; i < NUM_STUDENTS; i++) {
        print_student(&students[i]);
    }
    return 0;
}
