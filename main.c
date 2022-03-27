#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

FILE *fp;
void existing_user(void);
void lobby(void);
void month(void);
float me;
void add_exp(void)
{
	float expense;
	char name[41];
	printf("Enter the name of the expense(max 40 chars)");
	scanf("%s",name);
	printf("Enter the expense in rupees");
	scanf("%f",&expense);
	if (expense > me)
	{
		printf("You dont have enough allowance. You'll be redirected to the main menu");
		sleep(7);
		lobby();
	}
	else
	{
		fseek(fp,0,SEEK_END);
		fprintf(fp,"\n%s\t%.2f",name,expense);
		printf("\n\n");
		month();
	}


}

void month(void)
{
	float fbuf;
	char buf[100];
	int c = fgetc(fp);
	if (c == EOF)
	{
		float expen;
 		printf("\n\tEnter the total monthly expenditure in rupees\n");
		scanf("%f",&expen);
		fprintf(fp,"Monthly Expenditure\t%.2f\n",expen);
		printf("Redirecting to main menu");
		sleep(5);
		lobby();
	}
	else
	{
		fseek(fp,0,SEEK_SET);
		printf("\n");
		while(fscanf(fp,"%[^\t] %f",buf,&fbuf)==2)
		{
			if(strcmp(buf,"Monthly Expenditure")==0)
				me = fbuf;
			else
				me-=fbuf;
			printf("\n%s : %.2f rupees\n",buf,fbuf);
		}
		printf("\nAllowance left : %.2f\n",me);
		if(me>0)
		{
			int choice;
			printf("\nPress 1 - To add more expenditure \t\t2 - To return back to menu\n");
			scanf("%d",&choice);
			while(choice != 1 && choice != 2 )
			{
				printf("\t\tWrong choice\n\t\t\tEnter\n 1 - To add more expenditure \t\t 2 - To return back to main menu\n");
				scanf("%d",&choice);
			}
			if(choice == 1)
				add_exp();
			else if(choice ==2)
				lobby();
		}
		else
		{
			printf("You have exhausted your monthly allowance. No more spending.\nYou'll be redirected back to main menu in a few seconds");
			sleep(10);
			lobby();
		}
	}
}

void split_bill()
{
	float bill,per_person;
	int people,j=3;
	printf("\n\nEnter the total bill amount and number of people\n\n");
	scanf("%f %d",&bill,&people);
	per_person=bill/(float)people;
	printf("\nEverybody owes %.2f\n",per_person);
	printf("\nRedirecting to the main menu in\n");
	while(j>0)
	{
		printf("%d\n",j);
		j -= 1;
		sleep(1);
	}
	lobby();

}

void lobby()
{
	printf("\033[2J\033[1;1H");
	printf("\n\n\t\tWELCOME\n");
	printf("\t\t Enter");
	printf("\n1 - Split Bill\t\t2- Monthly Expenditure \t\t 3 - Quit\n");
	int choice;
	scanf("%d",&choice);
	while(choice != 1 && choice != 2 && choice !=3 )
	{
		printf("\t\tWrong choice\n\t\t\tEnter\n 1 - Split bill \t\t 2 - Monthly Expenditure \t\t 3 - Quit\n");
		scanf("%d",&choice);
	}
	if(choice == 1)
		split_bill();
	else if(choice == 2)
		month();
	else if(choice == 3)
	{
		printf("\033[2J\033[1;1H");
		printf("Thank You for using Splittr.");
	}
}



void new_user()
{
	printf("Enter your name(limit 30 characters and no space)\n");
	char name[31] , buf[35];
	scanf("%s",name);
	sprintf(buf,"%s.txt",name);
	if(fp == fopen(buf,"r"))
	{
		printf("Account already exists. \nPress 1 - To try again \t\t 2 - To go to existing account\n");
		int choice;
		scanf("%d",&choice);
		while(choice != 1 && choice != 2 )
		{
			printf("\t\tWrong choice\n\t\t\tEnter\n 1 - To try again \t\t 2 - To go to existing account\n");
			scanf("%d",&choice);
		}
		if(choice == 1)
			new_user();
		else if(choice == 2)
			existing_user();
	}
	else
	{
		fclose(fp);
		fp = fopen(buf,"a+");
		lobby();
	}
}

void existing_user()
{
	printf("Enter your name as entered previously without space(case sensitive)\n");
	char name[31],buf[35];
	scanf("%s",name);
	sprintf(buf,"%s.txt",name);
	if(fp == fopen(buf,"r"))
	{
		fclose(fp);
		fp = fopen(buf,"a+");
		lobby();
	}
	else
	{
		printf("Account does not exist.\nPress 1 - To try again \t\t 2 - To make a new account\n");
		int choice;
		scanf("%d",&choice);
		while(choice != 1 && choice != 2 )
		{
			printf("\t\tWrong choice\n\t\t\tEnter\n 1 - To try again \t\t 2 - To make a new account\n");
			scanf("%d",&choice);
		}
		if(choice == 1)
			existing_user();
		else if(choice == 2)
			new_user();
	}
}


int main(void)
{
	printf("\n\n\tWelcome To Splittr - Money Management System\n");
	printf("\t\t\tEnter\n 1 - For new user \t\t 2 - For existing user\n");
	int user;
	scanf("%d",&user);
	while(user != 1 && user != 2 )
	{
		printf("\t\tWrong choice\n\t\t\tEnter\n 1 - For new user \t\t 2 - For existing user\n");
		scanf("%d",&user);
	}
	if(user == 1)
		new_user();
	else if(user == 2)
		existing_user();

	return(0);
}
