#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char* name;
    int marks[10];
} student;

int no_fails(student s, int k) {
    for(int i = 0; i<k; i++) {
        if(s.marks[i] <= 2) return 0;
    }
    return 1;
}

float student_value(student s, int k) {
    float sum = 0;
    for(int i = 0; i<k; i++) {
        sum += s.marks[i];
    }
    return sum/k;
}

void best_student(student students[], int k, int n) {
    student bestie;
    float max = 0;
    int flag = 0;
    for(int i = 0; i<n; i++) {
        student s = students[i];
        float value = student_value(s, k);
        if(no_fails(s, k) && value > max) {
            flag = 1;
            max = value;
            bestie = s;
        }
    }
    if(flag) {
        printf("%s, %d лет, средний балл: %f\n", bestie.name, bestie.age, max);
    }
    else {
        printf("No best students.\n");
    }
}

int main() {
    int n, k;
    
    student students[30];
    scanf("%d %d", &n, &k);
    for(int i = 0; i<n; i++) {
        scanf("%s", students[i].name);
        scanf("%d", &students[i].age);
        for(int j = 0; j<k; j++) {
            scanf("%d", students[i].marks + j);
        }
    }
    for(int i = 0; i<n; i++) {
        printf("%s", students[i].name);
        printf("%d", students[i].age);
        for(int j = 0; j<k; j++) {
            printf("%d", students[i].marks[j]);
        }
    }

    //best_student(students, k, n);
}