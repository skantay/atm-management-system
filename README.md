# atm-managenebt-system

## About this project

ATM management system where users can do the following actions:

    Login/Register
    Create a new account
    Check the details of existing accounts
    Update information of existing accounts
    Remove existing accounts
    Check list of owned accounts
    Make transactions

## The following features were implemented by me

1.  The Registration feature
    - The program registers new users, users with the same name can not exist (names must be unique). They are saved in data/users.txt.

2.  The Update information of existing account feature, users can update their country or phone number.

    1. They are asked which account to change by asking its ID. Then the program asks what fields user wants to change (the only fields that are permitted to update is the phone number and the country).

    2. Whenever users update an account, it is saved into the corresponding file.

3.  The Checking the details of existing accounts feature, users can check just one account at a time.

    1. For this they must be asked to input the account id they want to see

    2. If the account is either savings, fixed01, fixed02 and fixed03 the system will display the information of that account and the interest you will acquire depending on the account:
        savings: interest rate 7%
        fixed01(1 year account): interest rate 4%
        fixed02(2 year account): interest rate 5%
        fixed03(3 year account): interest rate 8%
        If the account is current you must display You will not get interests because the account is of type current

    For example: for an account of type savings with a deposit date of 10/10/2002 and an amount of $1023.20 the system will show "You will get $5.97 as interest on day 10 of every month".

4.  The Make transaction feature, users can create transactions, withdrawing or depositing money to a certain account. All transactions are updated and saved into the corresponding file. Accounts of type fixed01, fixed02 and fixed03 are not allowed to make transactions and an error message displayed if transactions are attempted with these accounts.

5.  The Remove existing account feature, users can to delete their own account, the same happens here, updates are saved into the corresponding file.

6.  The Transfer owner feature, users can transfer their account to another user, by:

    1. Identifying the account and the user they want to transfer the ownership to

    2. Saving the information in the corresponding file


## What I learned

-   C language
-   Data manipulation
    1. File manipulation
    2. Data structures
-   Makefile
-   Terminal UI
-   Memory management
-   Pipes and child processes

## Bonus 

- I want to implement real database. Stay tuned
