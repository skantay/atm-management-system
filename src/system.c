#include "header.h"
#include <unistd.h>
#include <stdio.h>

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
	        u.id,
	        u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void fail(struct User u)
{
    int option;
    printf("\nFail!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        r.id = cr.id + 1;
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);
    
    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void updateAcc(struct User u)
{
   system("clear");
   printf("\t\t\t===== Update record =====\n");
   FILE *pf = fopen(RECORDS, "a+");
   struct Record cr;
   int accNum;
   int found = 0;
   
   printf("\nEnter account number you want to change:");
   scanf("%d", &accNum);

    while (getAccountNumber(pf, &cr))
    {
        if (strcmp(u.name, cr.name) == 0)
        {
            if (cr.accountNbr == accNum)
            {
                found = 1;
                break;
            }
        }
    }

   if (found == 0)
   {
       printf("✖ Account number is not found\n");
       fail(u);
   }
    
   char country[100];
   int phone;
   printf("\nYou can change only phone number and country");
   printf("\nDo you want to change country ? y/n:");
   char changeCountry;
   scanf(" %c", &changeCountry);

   if (changeCountry == 'y')
   {
       printf("\nEnter country:");
       scanf("%s",country);
       updateCountry(&cr, country);
   }

   printf("\nDo you want to change phone number ? y/n:");
   char changePhone;
   scanf(" %c", &changePhone);
   if (changePhone == 'y')
   {
        char input[256];
       printf("\nEnter number:");
       if (sscanf(input, "%d", &phone) != 1)
       {
        printf("NON valid number!\n");
        fail(u);
       }

       updatePhone(&cr, phone);
   }

    fclose(pf);
   success(u);
}

void updateCountry(struct Record *cr, char *country)
{
    FILE *pf = fopen(RECORDS, "r+");
    strcpy(cr->country, country);
    writeRecord(pf, cr);
}

void updatePhone(struct Record *cr, int phone)
{
    FILE *pf = fopen(RECORDS, "r+");
    cr->phone = phone;
    writeRecord(pf, cr);
}

void writeRecord(FILE *pf, struct Record *cr)
{
    FILE *tempFile = fopen("./data/temp.txt", "w");
    if (tempFile == NULL)
    {
        perror("Error opening temporary file");
        exit(EXIT_FAILURE);
    }

    struct Record temp;
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &temp.id,
                  &temp.userId,
                  temp.name,
                  &temp.accountNbr,
                  &temp.deposit.month,
                  &temp.deposit.day,
                  &temp.deposit.year,
                  temp.country,
                  &temp.phone,
                  &temp.amount,
                  temp.accountType) != EOF)
    {

        if ((strcmp(temp.name, cr->name) == 0) && temp.accountNbr == cr->accountNbr)
        {
            // Update the existing record
            fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    cr->id,
                    cr->userId,
                    cr->name,
                    cr->accountNbr,
                    cr->deposit.month,
                    cr->deposit.day,
                    cr->deposit.year,
                    cr->country,
                    cr->phone,
                    cr->amount,
                    cr->accountType);
        }
        else
        {
            // Copy the record as is
            fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    temp.id,
                    temp.userId,
                    temp.name,
                    temp.accountNbr,
                    temp.deposit.month,
                    temp.deposit.day,
                    temp.deposit.year,
                    temp.country,
                    temp.phone,
                    temp.amount,
                    temp.accountType);
        }
    }

    fclose(pf);
    fclose(tempFile);

    // Remove the original file
    if (remove(RECORDS) != 0)
    {
        perror("Error deleting the original file");
        exit(EXIT_FAILURE);
    }

    // Rename the temporary file to the original file
    if (rename("./data/temp.txt", RECORDS) != 0)
    {
        perror("Error renaming the temporary file");
        exit(EXIT_FAILURE);
    }
}


int getAccountNumber(FILE *ptr, struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
                  &r->userId,
                  r->name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}