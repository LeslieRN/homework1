/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** funtion
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef FUNTION_H_
#define FUNTION_H_

/**
 * Analysing
 * n evaluations -> description and percentage +
 * m students -> id, name, grades +
 * add a evaluation structure  +
 * add a students structure whose is goin to have the grades +
 * add a grade structure which is going to have the grades according to the evaluation +
 * have a function that calculates the total grade (needs evaluation and grades)
 * have a function that display everything
 * 
 * funtionalities:
 * have a function that adds the evaluations +
 * have a function that adds a student +
 * have a function that adds a grade +
 * 
 * check:
 * have printf staments to check if everything is working +
 * 
 * Restrictions /rules (explicit)
 * the maximum amount of studnets is 20
 * the maximum amount of evaluations is 10
 * char values hav a maximum value of 100
 * you can't register students without any evaluation
 * 
 * Implicit rules
 * check if the evalution is 100%, if not keep asking the user
 * check if the values is more than the 100% evaluation, if yes keep asking
 * check if the grade of the studnets is 100 per each evaluation, if not keep asking +
 * make sure the califications and id are numbers
 * make sure that the name is char
*/
typedef struct
{
    /* data */
    char description[100];
    int percentage;
} Evaluation;

typedef struct
{
    int grade;
    Evaluation eval;
} Grades;

typedef struct
{
    int id;
    char name[100];
    Grades *grades;
    char letter;
} Student;

/*Evaluation functions*/
Evaluation *insert_evaluction_values(int *, char *);
Evaluation get_evaluation(int *, int, int);
void printf_evaluation(Evaluation *, int);

/*Grades functions*/
Grades *insert_grades(int);
Grades get_grades();
void printf_grades(Student, int);

/*Student functions*/
Student *insert_student_values(int *, int, char *, char *);
Student get_student(int, char *);
void printf_students(Student, int);
int quantity_of_students(char *);

/*Checking functions*/
int is_Digit();

/*File functions*/
FILE *open_file(char *, char *);
void close_file(FILE *);

/*File functions for student*/
void insert_student_file(char *, Student *, int);
void show_student_file(char *, int);

/*File functions for evaluation*/
void insert_evaluation_file(char *, Evaluation *, int);
//void insert_evaluation_file(char*, Evaluation*, int);

/*File functions for grades*/
char calculate_letters(char *, Grades *, int);

Evaluation *insert_evaluction_values(int *number_eval, char *file_name)
{
    int counter = 0, total_percentage = 0;
    Evaluation *evaluation_values;
    printf("Insert the quantity of evaluations:\n");
    //checks if the number_eval is a number
    scanf("%d", number_eval); //= is_Digit();
    // printf("This is number %d", &number_eval);
    evaluation_values = (Evaluation *)malloc(sizeof(Evaluation) * (*number_eval));
    //printf("This is number %d", number_eval);
    do
    {
        *(evaluation_values + counter) = get_evaluation(&total_percentage, *number_eval, counter); //printf("Insert the description:");
        counter++;
    } while (counter < *(number_eval));
    insert_evaluation_file(file_name, evaluation_values, *(number_eval));
    return evaluation_values;
}

Evaluation get_evaluation(int *total_percentage, int number_eval, int counter)
{
    int true = 1;
    Evaluation inf_eval;
    fflush(stdin);
    printf("Insert the description of the evaluation:\n");
    //check if char
    gets(inf_eval.description);
    //fflush(stdin);
    //printf("Insert the percentage of the evaluation %s\n", inf_eval.description);
    //if integer
    //check if the inserted value is allowed
    do
    {
        /* code */
        printf("Insert the percentage of the evaluation %s\n", inf_eval.description);
        scanf("%d", &inf_eval.percentage);
        if (number_eval == 1 && inf_eval.percentage == 100)
        {
            //scanf("%d", &inf_eval.percentage);
            (*total_percentage) += inf_eval.percentage;
            true = 0;
        }
        else if ((number_eval > 1) && (inf_eval.percentage < 100) && (*total_percentage + inf_eval.percentage <= 100))
        {
            (*total_percentage) += inf_eval.percentage;
            true = 0;
        }
        else
        {
            printf("Error! Invalid Value. Try Again\n");
            printf("Maybe you don't have enough space!!\n");
        }
    } while (true);

    //scanf("%d", &inf_eval.percentage);
    /*(*total_percentage) += inf_eval.percentage;
    if (*(total_percentage) > 100)
    {

    }*/
    return inf_eval;
}

void printf_evaluation(Evaluation *evaluation_inf, int quantity_eval)
{
    for (int i = 0; i < quantity_eval; i++)
    {
        printf("Values : %d %s \n", (evaluation_inf + i)->percentage, (evaluation_inf + i)->description);
    }
}

Student *insert_student_values(int *quantity_students, int quantity_eval, char *file_name, char *file_name_eval)
{
    int counter = 0;
    Student *student_value;
    printf("Insert the number of students: \n");
    //chek if the quantity is a number
    scanf("%d", quantity_students);
    student_value = (Student *)malloc(sizeof(Student) * (*quantity_students));
    do
    {
        /* code */
        *(student_value + counter) = get_student(quantity_eval, file_name_eval);
        //printf("Here i'm in the first function\n");
        //insert_student_file(file_name, student_value);
        counter++;
    } while (counter < (*quantity_students));
    insert_student_file(file_name, student_value, (*quantity_students));
    return student_value;
}

Student get_student(int quantity_eval, char *file_name_eval)
{
    //printf("tHis is the quantity od values %d\n", quantity_eval);
    fflush(stdin);
    Student inf_student;
    printf("Insert the student's ID: \n");
    scanf("%d", &inf_student.id);
    fflush(stdin);
    printf("Insert the student's name: \n");
    gets(inf_student.name);
    inf_student.grades = insert_grades(quantity_eval);
    //calculate the students grades based on the percentage
    //take the a pointer of grades students.. open the evaluation file and calculate based on the percentaje
    //pass quantity evaluation

    //printf("Here i'm\n");
    //insert_student_file(file_name, inf_student);
    inf_student.letter = calculate_letters(file_name_eval, inf_student.grades, quantity_eval);
    return inf_student;
}
Grades *insert_grades(int quantity_eval)
{
    fflush(stdin);
    int counter = 0, total = 0;
    //Evaluation *inf_eval;
    Grades *grade_values;

    //printf("Insert the grade of ")
    //printf("tHis is the quantity od values %d\n", quantity_eval);s
    grade_values = (Grades *)malloc(sizeof(Grades) * quantity_eval);

    do
    {
        *(grade_values + counter) = get_grades();
        counter++;
        //printf("Here i'm grade function\n");
    } while (counter < quantity_eval);
    printf("Here i'm grade function\n");
    return grade_values;
}

Grades get_grades()
{
    Grades inf_grade;
    //open evaluation
    do
    {
        /* code */
        printf("Insert the grade\n"); //for %s evaluation \n", (inf_eval + counter)->description);
        //check if the values inserted is an integer
        scanf("%d", &inf_grade.grade);
        //check if percentage is less or equal to 100%
        if (inf_grade.grade < 0 && inf_grade.grade > 100)
        {
            printf("Invalid Value. Please, try again!!\n");
        }
    } while (inf_grade.grade < 0 && inf_grade.grade > 100);

    //printf("Insert the grade\n"); //for %s evaluation \n", (inf_eval + counter)->description);
    //check if percentage is less or equal to 100%
    //check if the values inserted is an integer
    //scanf("%d", &inf_grade.grade);
    //strcpy((grade_values + counter)->eval.description, inf_eval->description);
    //scanf("%d", (grade_values + counter)->grade);
    strcpy(inf_grade.eval.description, "Try");
    //close evaluation

    return inf_grade;
}

void printf_students(Student student_inf, int quantity_eval)
{
    // for (int i = 0; i < quantity_of_student; i++)
    //{
    printf("ID: %d Name: %s ", student_inf.id, student_inf.name);
    printf_grades(student_inf, quantity_eval);
    printf("Letter: %c", student_inf.letter);
    printf("\n");
    //}
    return;
}
void printf_grades(Student student_inf, int quantity_eval)
{
    for (int i = 0; i < quantity_eval; i++)
    {
        printf(" Grade for: %s is %d ", (student_inf.grades + i)->eval.description, (student_inf.grades + i)->grade);
    }
    return;
}

/*process function*/
char calculate_letters(char *file_name, Grades *student_grades, int quantity_eval)
{
    FILE *file = open_file(file_name, "rb");
    //int quantity_Students = quantity_of_students(file_name);
    int counter_read = 0, percentage = 0, grade = 0;
    int total = 0;
    char letter_grade = 'L';
    while (counter_read < quantity_eval)
    {
        Evaluation temp;
        fread(&temp, sizeof(Evaluation), 1, file);
        percentage = temp.percentage / 100;
        grade = (student_grades + counter_read)->grade;
        /*printf("This is the calculate letter function\n");*/
        printf("This is the student grades: %d\n", (student_grades + counter_read)->grade);
        printf("This is the percentage: %d \n", temp.percentage);
        total += (percentage * grade);
        printf("This is the value of total moveee %d\n", (student_grades + counter_read)->grade * temp.percentage / 100);
        //printf_students(temp, quantity_of_evaluation);
        counter_read++;
    }
    close_file(file);
    if (total >= 90 && total <= 100)
    {
        letter_grade = 'A';
    }
    else if (total >= 80 && total <= 89)
    {
        letter_grade = 'B';
    }
    else if (total >= 70 && total <= 79)
    {
        letter_grade = 'C';
    }
    return letter_grade;
}

int is_Digit()
{
    int number = 0;
    do
    {
        /* code */
        scanf("%d", &number);
        if (isdigit(number) == 0)
        {
            printf("Invalid value. Try Again!\n");
        }
    } while (isdigit(number) == 0);
    return number;
}

/*File functions*/
FILE *open_file(char *file_name, char *mode)
{
    FILE *file = fopen(file_name, mode);
    if (file == NULL)
    {
        fputs("Fil not open, please check...\n", stderr);
        exit(-1);
    }
    return file;
}

void close_file(FILE *file)
{
    int close = fclose(file);
    close == 0 ? printf("File closed\n") : printf("Error, fil not close!\n");
}

void insert_student_file(char *file_name, Student *student_data, int quantity_student)
{
    FILE *file = open_file(file_name, "a+b");
    fwrite(student_data, sizeof(Student) * quantity_student, 1, file);
    close_file(file);
}

void show_student_file(char *file_name, int quantity_of_evaluation)
{
    FILE *file = open_file(file_name, "rb");
    int quantity_Students = quantity_of_students(file_name);
    int counter_read = 0;
    while (counter_read < quantity_Students)
    {
        Student temp;
        fread(&temp, sizeof(Student), 1, file);
        printf_students(temp, quantity_of_evaluation);
        counter_read++;
    }
    close_file(file);
}

int quantity_of_students(char *file_name)
{
    FILE *file = open_file(file_name, "rb"); //inicio del archivo
    //se necesita saber la cantidad de bytes que tiene el archivo
    fseek(file, 0L, SEEK_END); //mover al final con fseek
    //fseek(archivo, 0L, SE)
    //nos dice cual es el indice, pero este lo dice en bytes
    long bytes = ftell(file); //nos dice donde se encuentra el cursor en los bytes donde nos movemos
    int students = bytes / sizeof(Student);
    //printf("La cantidad de bytes: %d y cantidad de estudiantes: %d\n", cantidad_bytes, cantidad_estudiantes);
    close_file(file);
    //cerrar_archivo(archivo);/
    return students;
}

void insert_evaluation_file(char *file_name, Evaluation *eval_data, int quantity_eval)
{
    FILE *file = open_file(file_name, "a+b");
    fwrite(eval_data, sizeof(Evaluation) * quantity_eval, 1, file);
    close_file(file);
}
/*void show_student_file(char *file_name, int quantity_of_evaluation)
{
    FILE *file = open_file(file_name, "rb");
    int quantity_Students = quantity_of_students(file_name);
    int counter_read = 0;
    while (counter_read < quantity_Students)
    {
        Student temp;
        fread(&temp, sizeof(Student), 1, file);
        printf_students(temp, quantity_of_evaluation);
        counter_read++;
    }
    close_file(file);
}*/
//void insert_evaluation_file(char*, Evaluation*, int);

/*File functions for grades*/
//maybe
/*void insert_grades_file(char * file_name, Grades * grades_data, int quantity_grades) {

}*/
#endif /* !FUNTION_H_ */
