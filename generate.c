/*****************************************************************************************************
* FILE NAME: generate.c
* AUTHOR: Marc Rutland Towse
* UNIT: Unic and C Programming
* PURPOSE: to generate test data for this assignment
* REFERENCE: stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
* LAST MOD: 22nd May 2018
* COMMENTS: weak coding and commenting due to this not being apart of assignment, only included as
*       additional sources
*****************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*****************************************************************************************************
* NAME: main
* PURPOSE: generate a data file in required format
* IMPORTS: none
* EXPORTS: return 0
* PRE ASSERTIONS: none
* POST ASSERTIONS: data file created
* REMARKS: poor coding, was just a quick knock up to mass generate as much data as needed
******************************************************************************************************/
int main()
{
    int i,size=150,day=0;
    char *dayS;
    FILE* example = fopen("exampleFile.txt", "w");
    time_t t;
    char ch = 'a'; 
    char cap = 'A'; 
    srand((unsigned)time(&t));

    if(example != NULL)
    {
        /*randomly generate a day*/
        for(i=1; i<size; i++)
        {
            day = rand() % 7;
            switch(day){
                case 1 :
                    dayS = "Monday";
                    break;
                case 2 :
                    dayS = "Tuesday";
                    break;
                case 3 :
                    dayS = "Wednesday";
                    break;
                case 4 :
                    dayS = "Thursday";
                    break;
                case 5 :
                    dayS = "Friday";
                    break;
                case 6 :
                    dayS = "Saturday";
                    break;
                case 0 :
                    dayS = "Sunday";
                    break;
            }
            /*randomly generate a capitol followed by 3 lowercase charcters then the number in the file in brackets*/
            fprintf(example, "%c%c%c%c(%d)\n",cap+(rand()%26),ch+(rand()%26),ch+(rand()%26),ch+(rand()%27),i);
            /*print the day and randomly generate a time*/
            fprintf(example, "%s %d:%d%d\n",dayS,rand()%24,rand()%6,rand()%9);       
        }
    }
    else
    {
        perror("Error opening file");
    }
 
    if(ferror(example))
    {
        perror("Error Reading from File");
    }
    fclose(example);

    return(0);
}

