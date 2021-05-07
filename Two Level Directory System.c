#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
struct files
{
    char dname[10][10], fname[10][10];
    int fcnt;
} dir[10];
char check_array[10] = {'\000'};
int directory_count = 0;
    int directory_number()
{
    int k;
    for(k=0;k<10;k++)
    {
        if(strcmp(dir[k].dname[k],check_array)==0)
        {directory_count=k;break;}
    }
    return directory_count;
}

int main()
{
 
    
    int dchoose, s, i, j;
    char directory_name[10], search_direcory[10], search_file[10];

    while (1)
    {
    continue_loop:
        printf("\n ----------------------------------- Two Level Directory System Menu-------------------------------\n");
        printf("\n 1- Create Directory (UPTO 10) \n 2- Create Files (UPTO 10) \n 3- Search Directory \n 4- Search File \n 5- Display Directories \n 6- Display Files In A Directory \n 7- Delete Directory \n 8- Delete File \n 9- Display ALL \n 10- Exit \n");
        printf("\n ---------------------------------------------------------------------------------------------------\n Your Choice= ");
        scanf("%i", &s);
        if (s == 1)
        {
            //dir[0] is fixed if someone wants to create files in root
            directory_number(directory_count);
            printf("\n  Enter Directory Name= ");
            scanf("%s", (dir[directory_count].dname[directory_count]));
            printf("  Directory ( %s )Created ........................\n", (dir[directory_count].dname[directory_count]));
            directory_count++;
        }
        else if (s == 2)
        {
            bool check=false;
            printf("\n Choose Directory\n");
            for (i = 0; i < 10; i++)
            {
                if(strcmp(dir[i].dname[i],check_array)==0)
                {
                    printf("%i - (Create Directory First) \n",i+1);
                }
                else
                {
                printf("%i - %s \n", i + 1, dir[i].dname[i]);
                check=true;
                }
            }
            if(check==false)
            goto continue_loop;
            printf("Directory Number= ");
            scanf("%i", &dchoose);
            dchoose--;
            printf("\nEnter The Name Of File= ");
            scanf("%s", (dir[dchoose].fname[dir[dchoose].fcnt]));
            printf("%s", (dir[dchoose].fname[dir[dchoose].fcnt]));
            printf("\n------------------------------- Files in Directory ------------------------------\n");
            int fdisplay = dir[dchoose].fcnt;
            fdisplay++;
            for (i = 0; i < fdisplay; i++)
            {
                printf("\n %i-%s \n", i + 1, dir[dchoose].fname[i]);
            }
            dir[dchoose].fcnt++;
        }
        else if (s == 3)
        {
            bool check = false;
            printf("\n Enter Directory You Want To Search= ");
            scanf("%s", directory_name);
            for (i = 0; i < directory_count; i++)
            {
                if (strcmp(directory_name, dir[i].dname[i]) == 0)
                {
                    printf("\n Directory Exist \n");
                    check = true;
                }
            }
            if (check == false)
            {
                printf("Directory (%s) Does not Exist", directory_name);
            }
        }
        else if (s == 4)
        {
            printf("\n Enter Name of the File You want to search: ");
            scanf("%s", search_file);
            bool check = false;
            for (i = 0; i < directory_count; i++)
            {
                for (j = 0; j < dir[i].fcnt; j++)
                {
                    if (strcmp(search_file, dir[i].fname[j]) == 0)
                    {
                        printf("File Exist in Directory %s", dir[i].dname[i]);
                        check = true;
                    }
                }
            }

            if (check == false)
            {
                printf("\n File %s Does not exist", search_file);
            }
        }
        else if (s == 5)
        {
            bool check = false;
            printf("\n -------------------------------------Displaying ALL DIRECTORIES--------------------------------------------------------\n ");
            for (i = 0; i < directory_count; i++)
            {
                if (dir[i].dname[i] != NULL)
                {
                    check = true;
                }
                printf("\n %s \n", dir[i].dname[i]);
            }
            if (check == false)
            {
                printf("\nNO DIRECTORIES TO SHOW\n");
            }
            printf("\n ---------------------------------------------------------------------------------------------------\n ");
        }
        else if (s == 6)
        {
            int num = 0;
            printf("\n ---------------------------------- Displaying FILES In A Directory------------------------------------------------------\n ");
            printf("\n Enter Name of the Directory You want to see: ");
            bool check = false;
            bool check2 = false;
            scanf("%s", search_file);
            for (i = 0; i < directory_count; i++)
            {
                if (strcmp(search_file, dir[i].dname[i]) == 0)
                {
                    num = i;
                    printf("\nDirectory Exist\n");
                    check = true;
                }
            }
            if (check == false)
            {
                printf("\n NO SUCH DIRECTORY\n");
                goto continue_loop;
            }
            printf("\n ---------------------------------------------------------------------------------------------------\n ");
            for (i = 0; i < dir[num].fcnt; i++)
            {
                if (dir[num].fname[i] != NULL)
                {
                    check2 = true;
                }
                printf("\n %s \n", (dir[num].fname[i]));
            }
            if (check2 == false)
            {
                printf("\n DIRECTORY IS EMPTY \n");
            }
            printf("\n ---------------------------------------------------------------------------------------------------\n ");
        }
        else if (s == 7)
        {
            char s = 0;
            int num = 0;
            printf("\n ---------------------------------- Deleting A Directory------------------------------------------------------\n ");
            printf("\n Enter Name of the Directory You want to delete: ");
            bool check = false;

            scanf("%s", search_file);
            for (i = 0; i < directory_count; i++)
            {
                if (strcmp(search_file, dir[i].dname[i]) == 0)
                {
                    num = i;
                    printf("\nDeleting Directory................\n");
                    memset(dir[i].dname[i],'\000', 10);
                    for (j = 0; j < dir[i].fcnt; j++)
                    {
                        strncpy(dir[i].fname[j],"",10);
                    }
                    check = true;
                }
            }
            if (check == false)
            {
                printf("\n NO SUCH DIRECTORY\n");
                goto continue_loop;
            }
            printf("\n ---------------------------------------------------------------------------------------------------\n ");
        }
        else if (s == 8)
        {

            char s = 0;
            int num = 0;
            printf("\n ---------------------------------- Deleting A Directory------------------------------------------------------\n ");
            printf("\n Enter Name of the Directory in which file exist: ");
            bool check = false;
            bool check2 = false;
            scanf("%s", search_file);
            for (i = 0; i < directory_count; i++)
            {
                if (strcmp(search_file, dir[i].dname[i]) == 0)
                {
                    num = i;
                    check = true;
                }
            }
            if (check == false)
            {
                printf("\n NO SUCH DIRECTORY\n");
                goto continue_loop;
            }
            printf("\n Enter The name of file you want to delete: ");
            scanf("%s", search_file);
            for (i = 0; i < dir[num].fcnt; i++)
            {
                if (strcmp(search_file, dir[num].fname[i]) == 0)
                {
                    check2 = true;
                    memset(dir[num].fname[i],'\000',10);
                }
            }
            if (check2 == false)
            {
                printf("\n File doesnot exist\n");
            }
            printf("\n ---------------------------------------------------------------------------------------------------\n ");
        }
        else if (s == 9)
        {
            bool check = false;
            printf("\n----------------------------Display Complete Information------------------------------------------\n");
            for (i = 0; i < 10; i++)
            {
                
                printf("\n-----------------------------------------------------------------------------------------------\n");

                if(strcmp(dir[i].dname[i],check_array)!=0)
                    printf("\n Directory %s has following files: ", dir[i].dname[i]);
                
                    
                for (j = 0; j < dir[i].fcnt; j++)
                {
                    if (dir[i].fname[j] != NULL)
                    {
                        printf("%s , ", dir[i].fname[j]);
                        check = true;
                    }
                }
                if (check == false)
                {
                    if(strcmp(dir[i].dname[i],check_array)==0)
                    printf("\nEmpty Space Available\n");
                    else
                    printf("\n Directory is empty\n");
                }
                printf("\n-----------------------------------------------------------------------------------------------\n");
            }
            printf("\n----------------------------Display Complete Information------------------------------------------\n");
        }
        else if (s == 10)
        {
            printf("Exiting Program................................\n");
            goto exit_menu;
        }
    }

exit_menu:
    return 0;
}
