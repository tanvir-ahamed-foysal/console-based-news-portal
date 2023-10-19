#include<stdio.h>
#include<string.h>
#include<time.h>

#define name_list "name_list.txt"
#define info_list "info_list.txt"
#define title_list "title_list.txt"
#define news_list "news_list.txt"
#define reporter_name_list "reporter_name_list.txt"
#define reporter_info_list "reporter_info_list.txt"
#define time_list "time_list.txt"

#define news_length 10000
#define title_length 100


void create_account()
{
    char name[30];
    char mobile[12];
    char password[30];
    char email[30];
    char password_temp[30];
    printf("\nWelcome to Sign up panel\nEnter Your Name: ");
    getchar();
    gets(name);
    printf("Enter Your Mobile Number: ");
    scanf("%s",mobile);
    printf("Enter Your email address: ");
    scanf("%s",email);
    printf("Enter Password: ");
    scanf("%s",password);
    printf("Enter Your Password Again: ");
    scanf("%s",password_temp);
    while(strcmp(password,password_temp)!=0)
    {
        printf("Password did not match.\n");
        printf("Enter Password: ");
        scanf("%s",password);
        printf("Enter Your Password Again: ");
        scanf("%s",password_temp);
    }

    FILE *file = fopen(name_list,"a");
    fprintf(file,"%s\n",name);
    fclose(file);

    FILE *fil = fopen(info_list,"a");
    fprintf(fil,"%s %s %s\n",mobile,email,password);
    fclose(fil);

    printf("Registration Successful.\n\n");
    main();
}

void upload_news(char name[], char mobile[], char email[])
{
    char title[title_length];
    char news[news_length];
    printf("\nPrint Title:\n");
    getchar();
    gets(title);
    printf("Print News:\n");
    //getchar();
    gets(news);

    FILE *name_ptr = fopen(reporter_name_list,"a");
    FILE *info_ptr = fopen(reporter_info_list,"a");
    FILE *title_ptr = fopen(title_list,"a");
    FILE *news_ptr = fopen(news_list,"a");

    fprintf(name_ptr,"%s",name);
    fprintf(info_ptr,"%s %s\n",mobile,email);
    fprintf(title_ptr,"%s\n",title);
    fprintf(news_ptr,"%s\n",news);

    fclose(name_ptr);
    fclose(info_ptr);
    fclose(title_ptr);
    fclose(news_ptr);

    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    FILE *time = fopen(time_list,"a");
    fprintf(time,"%s",asctime(ptr));
    fclose(time);

    main();
}

void verification_panel()
{
    char name[30];
    char mobile[12];
    char password[30];
    char email[30];
    char temp_name[30];
    char temp_password[30];
    printf("\nWelcome to verification panel\nEnter your name: ");
    getchar();
    gets(temp_name);
    temp_name[strlen(temp_name)] = '\n';
    printf("Enter your password: ");
    scanf("%s",temp_password);

    FILE *file1 = fopen(name_list, "r");
    if (!file1) {
        printf("Error opening users file.\n");
    }
    FILE *file2 = fopen(info_list, "r");
    if (!file2) {
        printf("Error opening users file.\n");
    }

    while (fscanf(file2, "%s %s %s", mobile, email, password) != EOF)
    {
        char temp[1];
        fgets(temp ,1, file1);
        fgets(name ,30, file1);
        if (strcmp(name, temp_name) == 0 && strcmp(password, temp_password) == 0)
        {
            printf("verified\n");
            fclose(file2);
            fclose(file1);
            upload_news(name, mobile, email);
        }
    }


    fclose(file1);
    fclose(file2);
    printf("Login failed.\n");
}

void log_in_as_reporter()
{
    int choice;
    do
    {
        printf("\nReporter Menu:\n1. Create Account.\n");
        printf("2. Sign in.\n");
        printf("3. Back to the main menu.\nEnter Your Choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            verification_panel();
            break;
        case 3:
            main();
            break;
        default :
            printf("Invalid Choice.Please try again.\n");

        }
    }
    while(choice != 3);
    }
void print_news()
{
    printf("\n\nPrinting all the news:\n");

    char name[30];
    char mobile[12];
    char email[30];
    char title[title_length];
    char news[news_length];
    char time[30];

    FILE *name_ptr = fopen(reporter_name_list,"r");
    FILE *info_ptr = fopen(reporter_info_list,"r");
    FILE *title_ptr = fopen(title_list,"r");
    FILE *news_ptr = fopen(news_list,"r");
    FILE *time_ptr = fopen(time_list,"r");

    while (fscanf(info_ptr, "%s %s", mobile, email) != EOF)
    {
        char temp[10];
        fgets(name, 30, name_ptr);
        fgets(title, title_length , title_ptr);
        fgets(news, news_length , news_ptr);
        fgets(temp, 1 , time_ptr);
        fgets(time, 30 , time_ptr);

        printf("\n\n");
        printf("%s\n",title);
        printf("Reporter : %s",name);
        printf("Mobile : %s\n",mobile);
        printf("Email : %s\n",email);
        printf("Publishing Time : %s\n",time);
        printf("%s\n\n",news);
    }

    fclose(time_ptr);
    fclose(name_ptr);
    fclose(info_ptr);
    fclose(title_ptr);
    fclose(news_ptr);

    main();
}

int main()
{
    printf("\nWelcome to Main Menu:\n");
    int choice;
    do
    {
        printf("1. Log in as Reporter.\n");
        printf("2. Log in as Visitor.\n");
        printf("3. Exit Program.\n");
        printf("Enter your choice number: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                log_in_as_reporter();
                break;
            case 2:
                print_news();
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n\n");
        }

    }while(choice != 3);
    return 0;
}
