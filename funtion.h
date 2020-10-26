/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description: this is were all the functions and it's use are located
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
 * have a function that calculates the total grade (needs evaluation and grades) +
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
 * the maximum amount of studnets is 20 +
 * the maximum amount of evaluations is 10 +
 * char values hav a maximum value of 100 +
 * you can't register students without any evaluation +
 * 
 * Implicit rules
 * check if the evalution is 100%, if not keep asking the user +
 * check if the values is more than the 100% evaluation, if yes keep asking +
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
    //data
    int grade;
    char eval[100];
} Grades;

typedef struct
{
    //data
    int id;
    char name[100];
    char letter;
} Student;

/*Evaluation functions*/
void *insert_evaluction_values(int *, char *);
Evaluation get_evaluation(int *, int, int);
void printf_evaluation(Evaluation *, int);

/*Grades functions*/
char insert_grades(int, char *, char *);
Grades get_grades(char *);
void printf_grades(int);

/*Student functions*/
void *insert_student_values(int *, int, char *, char *, char *);
Student get_student(int, char *, char *);
void printf_students(Student, Grades *, int);
int quantity_of_students(char *);

/*Checking functions*/
int is_Digit();

/*File functions*/
FILE *open_file(char *, char *);
void close_file(FILE *);

/*File functions for student*/
void insert_student_file(char *, Student *, int);
void show_student_file(char *, char *, int);

/*File functions for evaluation*/
void insert_evaluation_file(char *, Evaluation *, int);
int check_if_emty(char *);
//void insert_evaluation_file(char*, Evaluation*, int);

/*File functions for grades*/
char calculate_letters(char *, Grades *, int);
void insert_grades_file(char *, Grades *, int);

void *insert_evaluction_values(int *number_eval, char *file_name)
{
    int counter = 0, total_percentage = 0;
    Evaluation *evaluation_values;
    printf("Insert the quantity of evaluations:\n");
    scanf("%d", number_eval);
    evaluation_values = (Evaluation *)malloc(sizeof(Evaluation) * (*number_eval));
    do
    {
        //insert the evaluation data into the pointer evaluation_values
        *(evaluation_values + counter) = get_evaluation(&total_percentage, *number_eval, counter);
        counter++;
    } while (counter < *(number_eval));
    //inserting in file
    insert_evaluation_file(file_name, evaluation_values, *(number_eval));
    return evaluation_values;
}

Evaluation get_evaluation(int *total_percentage, int number_eval, int counter)
{
    int true = 1;
    Evaluation inf_eval;
    fflush(stdin);
    printf("Insert the description of the evaluation:\n");
    gets(inf_eval.description);
    do
    {
        /* User insert data*/
        printf("Insert the percentage of the evaluation %s\n", inf_eval.description);
        scanf("%d", &inf_eval.percentage);
        if (number_eval == 1 && inf_eval.percentage == 100) //if the number of evaluation = 1 then it must be 100%
        {
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
            //error message
            printf("Error! Invalid Value. Try Again\n");
            printf("Maybe you don't have enough space!!\n");
        }
    } while (true); // the loop will continues until the variable true is zero
    return inf_eval;
}

//funtion to check the insertion of evaluation
void printf_evaluation(Evaluation *evaluation_inf, int quantity_eval)
{
    for (int i = 0; i < quantity_eval; i++)
    {
        printf("Values : %d %s \n", (evaluation_inf + i)->percentage, (evaluation_inf + i)->description);
    }
}

void *insert_student_values(int *quantity_students, int quantity_eval, char *file_name, char *file_name_eval, char *file_name_grades)
{
    int counter = 0;
    Student *student_value;
    printf("Insert the number of students: \n");
    scanf("%d", quantity_students);
    student_value = (Student *)malloc(sizeof(Student) * (*quantity_students));
    do
    {
        /* insert the data to the student_value pointer*/
        *(student_value + counter) = get_student(quantity_eval, file_name_eval, file_name_grades);
        counter++;
    } while (counter < (*quantity_students));
    //inset in file student
    insert_student_file(file_name, student_value, (*quantity_students));
    return student_value;
}

Student get_student(int quantity_eval, char *file_name_eval, char *file_name_grades)
{
    //insert user data
    fflush(stdin);
    Student inf_student;
    printf("Insert the student's ID: \n");
    scanf("%d", &inf_student.id);
    fflush(stdin);
    printf("Insert the student's name: \n");
    gets(inf_student.name);
    //insert the letter of the grades proportional to the evaluations
    inf_student.letter = insert_grades(quantity_eval, file_name_eval, file_name_grades);
    return inf_student;
}

char insert_grades(int quantity_eval, char *file_name_eval, char *file_name_grade)
{
    fflush(stdin);
    int counter = 0, total = 0;
    char letter_grade = 'L';
    Grades *grade_values;
    grade_values = (Grades *)malloc(sizeof(Grades) * quantity_eval);
    FILE *file = open_file(file_name_eval, "r+b");
    do
    {
        Evaluation eval_desc;
        fread(&eval_desc, sizeof(Evaluation), 1, file);
        *(grade_values + counter) = get_grades(eval_desc.description);
        counter++;
    } while (counter < quantity_eval);
    close_file(file);
    letter_grade = calculate_letters(file_name_eval, grade_values, quantity_eval);
    insert_grades_file(file_name_grade, grade_values, quantity_eval);
    return letter_grade;
}

Grades get_grades(char *file_name_eval)
{
    Grades inf_grade;
    do
    {

        printf("Insert the grade for %s: \n", file_name_eval);
        scanf("%d", &inf_grade.grade);
        //check if the grade is less or equal to 100%
        if (inf_grade.grade < 0 && inf_grade.grade > 100)
        {
            printf("Invalid Value. Please, try again!!\n");
        }
        strcpy(inf_grade.eval, file_name_eval); //copy the name of the evaluation in grade
    } while (inf_grade.grade < 0 && inf_grade.grade > 100);
    return inf_grade;
}

void printf_students(Student student_inf, Grades *grades_inf, int quantity_eval)
{
    //formated way to display all the data
    printf("%-10d%-30s", student_inf.id, student_inf.name);
    return;
}
void printf_grades(int student_inf)
{
    ///formated way to display all the data (grades)
    printf("%-10d", student_inf);
    return;
}

/*process function*/
char calculate_letters(char *file_name, Grades *student_grades, int quantity_eval)
{
    FILE *file = open_file(file_name, "rb");
    int counter_read = 0, grade = 0;
    float total = 0, percentage = 0;
    char letter_grade = 'L'; //default value
    while (counter_read < quantity_eval)
    {
        Evaluation temp;
        fread(&temp, sizeof(Evaluation), 1, file);
        percentage = temp.percentage / 100;
        grade = (student_grades + counter_read)->grade;
        total += (temp.percentage * grade) / 100; //total obtains the sum of all the grades percentages
        counter_read++;
    }
    close_file(file);
    //letter clasification according to the total calculated
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
    else
    {
        letter_grade = 'F';
    }
    //return the letter so it can be inserted in the student file
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
    close == 0 ?: printf("Error, fil not close!\n");
}

/*insert in the student file*/
void insert_student_file(char *file_name, Student *student_data, int quantity_student)
{
    FILE *file = open_file(file_name, "a+b");
    fwrite(student_data, sizeof(Student) * quantity_student, 1, file);
    close_file(file);
}

void show_student_file(char *file_name, char *file_name_grades, int quantity_of_evaluation)
{
    //open both student and grades files
    FILE *file = open_file(file_name, "rb");
    FILE *file_g = open_file(file_name_grades, "rb");
    int quantity_Students = quantity_of_students(file_name); //obtains the quantity of students
    int counter_read = 0, counter = 0;
    while (counter_read < quantity_Students)
    {
        Student temp;
        fread(&temp, sizeof(Student), 1, file);
        printf_students(temp, 0, quantity_of_evaluation); //print students data in the formated way
        //prints all the grades for each student
        do
        {
            Grades temp_g;
            fread(&temp_g, sizeof(Grades), 1, file_g);
            printf_grades(temp_g.grade);
            counter++;
        } while (counter < quantity_of_evaluation); //th loop will stop when the counter reaches the quentity of evaluatios
        printf("%-8c", temp.letter);                //print the letter of the student
        printf("\n");
        counter = 0;
        counter_read++;
    }
    close_file(file);
    close_file(file_g);
}

int quantity_of_students(char *file_name)
{
    FILE *file = open_file(file_name, "rb");
    fseek(file, 0L, SEEK_END); //move at the end of the file
    long bytes = ftell(file);  //tells the location of the cursor
    int students = bytes / sizeof(Student);
    //close file
    close_file(file);
    return students;
}
/*insert in the evaluation file*/
void insert_evaluation_file(char *file_name, Evaluation *eval_data, int quantity_eval)
{
    FILE *file = open_file(file_name, "a+b");
    fwrite(eval_data, sizeof(Evaluation) * quantity_eval, 1, file);
    close_file(file);
}
/*insert in the grades file*/
void insert_grades_file(char *file_name, Grades *grades_data, int quantity_eval)
{
    FILE *file = open_file(file_name, "a+b");
    fwrite(grades_data, sizeof(Grades) * quantity_eval, 1, file);
    close_file(file);
}

//cheks if the file of evaluation is empty
int check_if_emty(char *file_name_eval)
{
    FILE *file = fopen(file_name_eval, "r+b");
    if (fseek(file, 0L, SEEK_END) == 0) //if it is empty it will return 1
    {
        close_file(file);
        return 1;
    }
    else
    {
        close_file(file);
        return 0;
    }
}

/*
*return the quantity of evaluations
*This function is used when the user stops the program and, inicialize the programm again
*/
int quantity_of_evaluation(char *file_name)
{
    FILE *file = open_file(file_name, "rb");
    fseek(file, 0L, SEEK_END);
    long bytes = ftell(file);                             //tell the quantity in bytes
    int evaluation_quantity = bytes / sizeof(Evaluation); //dividing it by the size give us the quantity
    close_file(file);
    return evaluation_quantity;
}

/*print the data in a formated way, prints the tittle of each evaluation*/
void show_description(char *file_name, int quantity_eval)
{
    FILE *file = open_file(file_name, "r+b");
    for (int i = 0; i < quantity_eval; i++)
    {
        Evaluation student_inf_des;
        fread(&student_inf_des, sizeof(Evaluation), 1, file);
        printf("%-5s", student_inf_des.description);
    }
    close_file(file);
}
#endif /* !FUNTION_H_ */
