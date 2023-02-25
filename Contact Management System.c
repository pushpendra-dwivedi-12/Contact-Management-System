#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>

struct contact
{
long long ph;
char name[20],add[20],email[30];
}list;

char query[20],name[20];
FILE *fp, *ft;
int i,n,ch,l,found;

void main_menu();
void main_choice();
void add_contact();
void view_contact();
void search_contact();
void edit_contact();
void delete_contact();
void main_choice_menu();

int main()
{


main_menu();

main_choice();

main_choice_menu();

return 0;
}

/* ************Main menu ***********************  */
void main_menu()
{
    
system("cls");    
printf("\n\t ====================================");
printf("\n\t      Welcome to contact Manager     ");
printf("\n\t ====================================");
printf("\n\n\n\t\t\tMAIN MENU\n\t\t");
printf("=====================\n\t\t");
printf("[1] Add a new Contact\n\t\t");
printf("[2] List all Contacts\n\t\t");
printf("[3] Search for contact\n\t\t");
printf("[4] Edit a Contact\n\t\t");
printf("[5] Delete a Contact\n\t\t");
printf("[0] Exit\n\t\t");
printf("=====================\n\t\t");
}

/* ************Main Choice ***********************  */
void main_choice()
{
    
printf("Enter the choice:");
scanf("%d",&ch);

switch(ch)
{
case 0:
printf("\n\n\t\tAre you sure u want to exit?");
break;

case 1:
    add_contact();
break;

case 2:
    view_contact();
break;

case 3:
    search_contact();
break;

case 4:
    edit_contact();
break;

case 5:
    delete_contact();
break;

default:
printf("Invalid choice");
break;
}
}

/* ************Main Choice Menu ***********************  */
void main_choice_menu()
{

printf("\n\n\n..::Enter the Choice:\n\n\t");
printf("[1] Main Menu\t\t");
printf("[0] Exit\n");
scanf("%d",&ch);
switch (ch)
{
case 1:
    main();


case 0:
break;

default:
printf("Invalid choice");
break;
}
}

/* *********************add new contacts************  */
void add_contact()
{
    
system("cls");
fp=fopen("con.txt","a");
for (;;)
{ fflush(stdin);
printf("To exit enter blank space in the name input\nName (Use identical):");
scanf("%[^\n]",&list.name);
if(stricmp(list.name,"")==0 || stricmp(list.name," ")==0)
break;
fflush(stdin);
printf("Phone:");
scanf("%lld",&list.ph);
fflush(stdin);
printf("address:");
scanf("%[^\n]",&list.add);
fflush(stdin);
printf("email address:");
gets(list.email);
printf("\n");
fwrite(&list,sizeof(list),1,fp);
}
fclose(fp);
}

/* *********************list of contacts*************************  */
void view_contact()
{
system("cls");
printf("\n\t\t================================\n\t\t\t");
printf("LIST OF CONTACTS\n\t\t");
printf("================================\n\n");
printf("Name\t\t");
printf("Phone No\t    ");
printf("Address\t\t");
printf("E-mail ad.\n");
printf("=================================================================\n\n");

for(i=97;i<=122;i=i+1)
{

fp=fopen("con.txt","r");
fflush(stdin);
found=0;
while(fread(&list,sizeof(list),1,fp)==1)
{
if(list.name[0]==i || list.name[0]==i-32)
{
printf("\nName\t: %s\nPhone\t: %lld\nAddress\t: %s\nEmail\t: %s\n",list.name,
list.ph,list.add,list.email);
found++;
}
}
if(found!=0)
{
    printf("=========================================================== [%c]-(%d)\n\n",i-32,found);
    getch();

}
fclose(fp);

}

}

/* *******************search contacts**********************  */
void search_contact()
{
system("cls");
do
{
found=0;
printf("\n\n\t..::CONTACT SEARCH\n\t===========================\n\t..::Name of contact to search: ");
fflush(stdin);
scanf("%[^\n]",&query);
l=strlen(query);
fp=fopen("con.txt","r");

system("cls");
printf("\n\n..::Search result for '%s' \n===================================================\n",query);
while(fread(&list,sizeof(list),1,fp)==1)
{
for(i=0;i<=l;i++)
name[i]=list.name[i];
name[l]='\0';
if(stricmp(name,query)==0)
{
printf("\n..::Name\t: %s\n..::Phone\t: %lld\n..::Address\t: %s\n..::Email\t:%s\n",list.name,list.ph,list.add,list.email);
found++;
if (found%4==0)
{
printf("..::Press any key to continue...");
getch();
}
}
}

if(found==0)
printf("\n..::No match found!");
else
printf("\n..::%d match(s) found!",found);
fclose(fp);
printf("\n ..::Try again?\n\n\t[1] Yes\t\t[0] No\n\t");
scanf("%d",&ch);
}while(ch==1);
}

/* *********************edit contacts************************/
void edit_contact()
{
system("cls");
fp=fopen("con.txt","r");
ft=fopen("temp.dat","w");
fflush(stdin);
printf("..::Edit contact\n===============================\n\n\t..::Enter the name of contact to edit:");
scanf("%[^\n]",name);
while(fread(&list,sizeof(list),1,fp)==1)
{
if(stricmp(name,list.name)!=0)
fwrite(&list,sizeof(list),1,ft);
}
fflush(stdin);
printf("\n\n..::Editing '%s'\n\n",name);
printf("..::Name(Use identical):");
scanf("%[^\n]",&list.name);
fflush(stdin);
printf("..::Phone:");
scanf("%lld",&list.ph);
fflush(stdin);
printf("..::address:");
scanf("%[^\n]",&list.add);
fflush(stdin);
printf("..::email address:");
gets(list.email);
printf("\n");
fwrite(&list,sizeof(list),1,ft);
fclose(fp);
fclose(ft);
remove("con.txt");
rename("temp.dat","con.txt");
}

/* ********************delete contacts**********************/
void delete_contact()
{
system("cls");
fflush(stdin);
printf("\n\n\t..::DELETE A CONTACT\n\t==========================\n\t..::Enter the name of contact to delete:");
scanf("%[^\n]",&name);
fp=fopen("con.txt","r");
ft=fopen("temp.dat","w");
while(fread(&list,sizeof(list),1,fp)!=0)
if (stricmp(name,list.name)!=0)
fwrite(&list,sizeof(list),1,ft);
fclose(fp);
fclose(ft);
remove("con.txt");
rename("temp.dat","con.txt");
}