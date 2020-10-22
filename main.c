#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funtion.h"
/**
 * Analysing
 * n evaluations -> description and percentage
 * m students -> id, name, grades
 * add a evaluation structure 
 * add a students structure whose is goin to have the grades
 * add a grade structure which is going to have the grades according to the evaluation
 * have a function that calculates the total grade
 * have a function that display everything
 * 
 * funtionalities:
 * have a function that adds the evaluations +
 * have a function that adds a student 
 * have a function that adds a grade
 * 
 * check:
 * have printf staments to check if everything is working
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
 * check if the grade of the studnets is 100 per each evaluation, if not keep asking
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
} Student;

/*Evaluation functions*/
Evaluation *insert_evaluction_values(int *);
Evaluation get_evaluation();
void printf_evaluation(Evaluation *, int);

/*Grades functions*/
Grades *insert_grades(int);
Grades get_grades();
void printf_grades(Student, int);

/*Student functions*/
Student *insert_student_values(int *, int);
Student get_student(int);
void printf_students(Student *, int, int);

int main()
{
    int number_eval = 0, quantity_students = 0;
    Evaluation *evaluation_main;
    Student *student_main;
    evaluation_main = insert_evaluction_values(&number_eval);
    //printf_evaluation(evaluation_main, number_eval);

    student_main = insert_student_values(&quantity_students, number_eval);
    printf_students(student_main, quantity_students, number_eval);
    return 0;
}

Evaluation *insert_evaluction_values(int *number_eval)
{
    int counter = 0;

    Evaluation *evaluation_values;
    printf("Insert the quantity of evaluations:\n");
    //checks if the number_eval is a number
    scanf("%d", number_eval);
    // printf("This is number %d", &number_eval);
    evaluation_values = (Evaluation *)malloc(sizeof(Evaluation) * (*number_eval));
    //printf("This is number %d", number_eval);
    do
    {
        *(evaluation_values + counter) = get_evaluation(); //printf("Insert the description:");
        counter++;
    } while (counter < *(number_eval));
    return evaluation_values;
}

Evaluation get_evaluation()
{
    Evaluation inf_eval;
    fflush(stdin);
    printf("Insert the description of the evaluation:\n");
    //check if char
    gets(inf_eval.description);
    //fflush(stdin);
    printf("Insert the percentage of the evaluation %s\n", inf_eval.description);
    //if integer
    //check if the inserted value is allowed
    scanf("%d", &inf_eval.percentage);
    return inf_eval;
}

void printf_evaluation(Evaluation *evaluation_inf, int quantity_eval)
{
    for (int i = 0; i < quantity_eval; i++)
    {
        printf("Values : %d %s \n", (evaluation_inf + i)->percentage, (evaluation_inf + i)->description);
    }
}

Student *insert_student_values(int *quantity_students, int quantity_eval)
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
        *(student_value + counter) = get_student(quantity_eval);
        printf("Here i'm in the first function\n");
        counter++;
    } while (counter < (*quantity_students));
    return student_value;
}

Student get_student(int quantity_eval)
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
    printf("Here i'm\n");
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
    printf("Insert the grade\n"); //for %s evaluation \n", (inf_eval + counter)->description);
    //check if percentage is less or equal to 100%
    //check if the values inserted is an integer
    scanf("%d", &inf_grade.grade);
    //strcpy((grade_values + counter)->eval.description, inf_eval->description);
    //scanf("%d", (grade_values + counter)->grade);
    strcpy(inf_grade.eval.description, "Try");
    return inf_grade;
}

void printf_students(Student *student_inf, int quantity_of_student, int quantity_eval)
{
    for (int i = 0; i < quantity_of_student; i++)
    {
        printf("ID: %d Name: %s ", (student_inf + i)->id, (student_inf + i)->name);
        printf_grades(*(student_inf + i), quantity_eval);
        printf("\n");
    }
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