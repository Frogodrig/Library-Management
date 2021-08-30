#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char member[100];
int idno;
int choice;
long int phn_number;
char extn[4] = ".dat";

int newID()
{
    system("clear");
    char temp[50];
    int bookcount=0;

    printf("Enter the ID: ");
    scanf("%d", &idno);

    sprintf(temp, "%d", idno);
    char *filename = strcat(temp, extn);

    FILE *acc;
    acc = fopen(filename, "w");

    system("clear");
    /* Inputs from user to store in file */
    printf("ID Number: %d \n", idno);
    printf("Enter the name of member: ");
    scanf(" %[^\n]s", &member);

    printf("Enter your Phone Number: ");
    scanf("%li", &phn_number);



    fprintf(acc,"%d Books issued.\nID Number: %d \nName of member: %s\nContact Number: %li\n",bookcount, idno, &member, phn_number);

    /* Close file to save file data */
    fclose(acc);
    
    printf("\nAccount Created Succesfully.\n");
    return 0;
}

int iandr()
{

    int choice;
    char temp[50],p;

    printf("Enter your ID Number: ");
    scanf("%d", &idno);
    
    /* Storing idno in temporary buffer(ie. using to convert int to char) */
    sprintf(temp, "%d", idno);
    char *filename = strcat(temp, extn); /* Concatenating temporary buffer with .dat extension to generate filename  */

    FILE *aptr=fopen(filename, "a+");  /*Opening member's file in append+ mode*/
    FILE *rptr=fopen(filename,"r+");  /*Opening member's file in read+ mode*/
    if(aptr==NULL)
    {
        printf("Account does not exist!\n");  /*Checks for invalid accounts*/
        return -1;
    }
    sleep(3);
    system("clear");
    printf("1. Issue a new book.\n");
    printf("2. Return book.\n");
    printf("Enter you choice: ");
    scanf("%d", &choice);
    if (choice == 1) /*Book issue*/
    {
            char ISBN[25],bookname[50],author[50],t,date[9],n;
            int converted=0;

            n=fgetc(rptr);  /*Reading no. of books issued in the file */
    
            converted = n -'0' ;  /*Converting character to integer*/

            if(converted<3&&converted>-1)  /*Member only allowed to issue not more than 3 books*/
            {
                printf("List of books : \n");
                FILE *ptr=fopen("Books.dat", "r");
                t = fgetc(ptr);
                while (t != EOF)   /*Traversing and printing each character of Books.dat*/
                {
                    printf("%c", t);
                    t = fgetc(ptr);
                }
                printf("\nEnter the ISBN no. of the book of the book you want to issue: ");
                scanf("%s",&ISBN);
                printf("Enter name of the book : ");
                scanf("\n");
                scanf("%[^\n]s",&bookname);
                printf("Enter name of the author: ");
                scanf("\n");
                scanf("%[^\n]s",&author);
                printf("Enter the date: ");
                scanf("\n");
                scanf("%s",&date);

                fprintf(aptr,"\n%s\t%s by %s issued at %s.\n",ISBN,bookname,author,date);

                converted++;  /*Increasing no. of books issued by member*/
                p = converted + '0';  /*Converting integer to character*/
            
                fseek(rptr,0,SEEK_SET);  /*Bringing file cursor to the beggining of the file */
                fputc(p,rptr); /*Updating number of books issued by member */
        
                fclose(aptr);
                fclose(rptr);
                fclose(ptr);
                printf("Book issued succesfully.\n");
                
                sleep(3);
                 system("clear");
            }
            else
            {
                printf("Limit of issue exceeded!\n");
                sleep(3);
                 system("clear");
            }
    }
    else if (choice == 2) /*Book return*/
    {
        
        char ISBN[25],bookname[50],author[50],t,date[9],n;
        int converted=0;
        
        n = fgetc(rptr);
        converted= n - '0';
        if(converted!=0)
        {
            FILE *ptr=fopen("Books.dat", "r");
            t = fgetc(ptr);
            while (t != EOF)
            {
                printf("%c", t);
                t = fgetc(ptr);
            }
            printf("\nEnter the ISBN no. of the book of the book you want to return: ");
            scanf("%s",&ISBN);
            printf("Enter name of the book : ");
            scanf("\n");
            scanf("%[^\n]s",&bookname);
            printf("Enter name of the author: ");
            scanf("\n");
            scanf("%[^\n]s",&author);
            printf("Enter the date: ");
            scanf("\n");
            scanf("%s",&date);

            fprintf(aptr,"\n%s\t%s by %s returned at %s.\n",ISBN,bookname,author,date);

            converted--;
            p = converted + '0';
            
            fseek(rptr,0,SEEK_SET);
            fputc(p,rptr);
        
            

            fclose(aptr);
            fclose(rptr);
            fclose(ptr);
            printf("Book returned successfully.\n");
            sleep(3);
            system("clear");

        }
        else
        {
            printf("You have not issued any book!\n");
            sleep(3);
            system("clear");
        }    
    }
}

int viewDetails()
{
    char c;
    char temp[50];

    printf("Enter your ID Number: ");
    scanf("%d", &idno);

    sprintf(temp, "%d", idno);
    char *filename = strcat(temp, extn);
    system("clear");
    FILE *acc;
    acc = fopen(filename, "r");

    if (acc == NULL)  /*Checking for invalid file*/
    {
        system("clear");
        printf("Unfortunately,the member does not exist \nPlease create a new account. \n");
        return -1;
    }

    c = fgetc(acc);
    while (c != EOF)  /*traversing and printing each character of the member's file*/
    {
        printf("%c", c);
        c = fgetc(acc);
    }

    fclose(acc);
    return 0;
}

void removeID()
{

    char temp[50];

    printf("Enter your ID Number: ");
    scanf("%d", &idno);

    sprintf(temp, "%d", idno);
    char *filename = strcat(temp, extn);

    if (remove(filename) == 0) 

      printf("Deleted successfully\n"); 

   else

      printf("Unable to delete the file\n"); 

    system("clear");
    printf("Member's account has been removed Succesfully\n");
    sleep(3);
    system("clear");
}


int main()
{
    system("clear");
    int choice;
    while (1)
    {
        printf("\n-------------WELCOME TO OUR LIBRARY-----------\n");
        printf("\n1. Create a new ID\n");
        printf("2. Issue or return book\n");
        printf("3. View details\n");
        printf("4. Close an Account\n");
        printf("5. Exit program\n");
        printf("------------------------------------------------\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            newID();
            break;
        case 2:
            iandr();
            break;
        case 3:
            viewDetails();
            break;
        case 4:
            removeID();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Wrong entry!!\n");
            break;
        }
    }
    return 0;
}