/**
 * @file prime.c
 * @author Danny Khuu
 * @brief 
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "prime.h"

int isPrime(int num)
{
    if(num == 2 || num == 3)
    {
        return 1;
    }
    // If even number => not prime
    else if((num%2) == 0 || (num%3) == 0 || num <= 1)
    {
        return 0;
    }

    // All primes are (6k +- 1)
    // where k is an integer greater than 1
    int eval = (num%6);
    if(((eval+1) == 6) || ((eval-1) == 0))
    {
        return 1;
    }

    return 0;
}


int generatePrime(int num)
{
    switch(num)
    {
        case 2:
            return 3;
        case 3:
            return 5;
        default:
            break;
    }

    int k = num / 6;
    if((6*k-1) == num)
    {
        return (6*k+1);
    }
    else if((6*k+1) == num)
    {
        return (6*(k+1)-1);
    }
    else
    {
        return (6*(k+1)+1);
    }
}