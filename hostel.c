#include <stdio.h>
#include <stdlib.h>

struct student {
    int id;
    char name[30];
    int meals;
};

void addStudent() {
    struct student s;
    FILE *fp = fopen("mess.dat", "ab");

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Student Name: ");
    scanf("%s", s.name);
    s.meals = 0;

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void viewStudents() {
    struct student s;
    FILE *fp = fopen("mess.dat", "rb");

    if (fp == NULL) {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nID\tName\tMeals\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%s\t%d\n", s.id, s.name, s.meals);
    }
    fclose(fp);
}

void markMeal() {
    struct student s;
    int id, found = 0;
    FILE *fp = fopen("mess.dat", "rb+");

    printf("\nEnter Student ID: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            s.meals++;
            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
        printf("\nMeal Marked Successfully!\n");
    else
        printf("\nStudent Not Found!\n");
}

void calculateBill() {
    struct student s;
    int rate = 50;
    FILE *fp = fopen("mess.dat", "rb");

    printf("\nID\tName\tMeals\tBill\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%s\t%d\t%d\n", s.id, s.name, s.meals, s.meals * rate);
    }
    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Hostel Mess Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Mark Meal\n");
        printf("4. Calculate Bill\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: markMeal(); break;
            case 4: calculateBill(); break;
            case 5: exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }
}
