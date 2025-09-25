/******************************************************************************

Author: Darius Morrison
Date: 4/13/24

*******************************************************************************/
#include <stdio.h>

int main()
{
    int num1;
    int num2;
    int additionSum;
    
    //Addition
    printf("Enter first interger for Addition: \n");
    scanf("%d", &num1);
    printf("Enter second interger for Additon: \n");
    scanf("%d", &num2);
    additionSum = num1 + num2;
    printf("%d plus %d is equal to %d.\n", num1, num2, additionSum);
    printf("-----------------------------------------------------------------\n");
    
    //Subtraction
    int subNum1;
    int subNum2;
    int subtractionSum;
    
    printf("Enter first interger for Subtration: \n");
    scanf("%d", &subNum1);
    printf("Enter second interger for Subtraction: \n");
    scanf("%d", &subNum2);
    subtractionSum = subNum1 - subNum2;
    printf("%d minus %d is equal to %d.\n", subNum1, subNum2, subtractionSum);
    printf("-----------------------------------------------------------------\n");
    
    //Multiplication
    int multNum1;
    int multNum2;
    int multiplicationSum;
    
    printf("Enter first interger for Multiplication: \n");
    scanf("%d", &multNum1);
    printf("Entert second interger for Multiplication: \n");
    scanf("%d", &multNum2);
    multiplicationSum = multNum1 * multNum2;
    printf("%d multiplied by %d is equal to %d.\n", multNum1, multNum2, multiplicationSum);
    printf("-----------------------------------------------------------------\n");
    
    //Division
    int divNum1;
    int divNum2;
    float divisionSum;
    
    printf("Enter first number for division: \n");
    scanf("%d", &divNum1);
    printf("Enter second number for division: \n");
    scanf("%d", &divNum2);
    divisionSum = (float)divNum1/divNum2;
    printf("%d divided by %d is equal to %.2f.\n", divNum1, divNum2, divisionSum);
    printf("-----------------------------------------------------------------\n");
    
    //Modulus
    int modNum1;
    int modNum2;
    int modSum;
    
    printf("Enter first number for modulus: \n");
    scanf("%d", &modNum1);
    printf("Enter second number for modulus: \n");
    scanf("%d", &modNum2);
    modSum = modNum1 % modNum2;
    printf("The remainder of %d divided by %d is %d.\n", modNum1, modNum2, modSum);
    printf("-----------------------------------------------------------------\n");
    
    printf("******************************\n");
    
    int out = -1;
    //should print 33
    out = 1 + 4 * 15 / 2 + 2;
    printf("1+4*15/2+2 = %d\n", out);
    
    // This expression should print the value of 16
    out = 1+4*15/(2+2);
    printf("1+4*15/(2+2) = %d\n", out);

    // This expression should print the value of 39
    out = (1+4)*15/2+2;
    printf("(1+4)*15/2+2 = %d\n", out);

    // This expression should print the value of 18
    out = (1+4)*15/(2+2);
    printf("(1+4)*15/(2+2) = %d\n", out);
    
    return 0;
}
