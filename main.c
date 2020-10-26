#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funtion.h"
#include <ctype.h>
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
int main()
{
    int number_eval = 0, quantity_students = 0, option = 0, menu_option = 0;
    //files for students, grades and evaluation
    char *binay_file = "binary_file.dat";
    char *binay_file2 = "binary_file_eval.dat";
    char *binay_file3 = "binary_file_grades.dat";
    do
    {
        //menu
        printf("WELCOME TO THE STUDENTS REGISTER!\n");
        printf("Select the option you want to choose\n");
        printf("1 -> Insert evaluation\n");
        printf("2 -> Insert student\n");
        printf("3 -> Display student\n");
        printf("4 -> Delete all data\n");
        scanf("%d", &menu_option);
        switch (menu_option)
        {
        case 1:
            //insert evaluation
            insert_evaluction_values(&number_eval, binay_file2);
            //printf_evaluation()
            break;
        case 2:
            //check if evaluation is emty
            if (quantity_of_evaluation(binay_file2) == 0)
            {
                /* the file evaluation is empty*/
                printf("You need to insert evaluations first\n");
            }
            else
            {
                //add the counter for number eval
                number_eval = quantity_of_evaluation(binay_file2);
                //insert student
                insert_student_values(&quantity_students, number_eval, binay_file, binay_file2, binay_file3);
            }

            break;
        case 3:
            //display the data
            number_eval = quantity_of_evaluation(binay_file2);
            printf("%-10s%-30s ", "id", "name");
            show_description(binay_file2, number_eval);
            printf("%-15s\n", "letter");
            show_student_file(binay_file, binay_file3, number_eval);
            break;
        case 4:
            //delete all data from files
            close_file(open_file(binay_file, "w+b"));
            close_file(open_file(binay_file2, "w+b"));
            close_file(open_file(binay_file3, "w+b"));
            break;
        default:
            //default message
            printf("Error :(!! Try again\n");
            break;
        }
        //user option
        printf("Do you want to do something else? Yes(1) or No(0) \n");
        scanf("%d", &option);
    } while (option);

    return 0;
}