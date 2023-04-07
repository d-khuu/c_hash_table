/**
 * @file prime.h
 * @author Danny Khuu
 * @brief Header file for the prime.c file
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PRIME_H
#define PRIME_H

/**
 * @brief Checks if the number is a prime
 * 
 * It also checks for prime numbers faster
 * than that example in Wikipedia (Take that!)
 * 
 * @param num Number to check if it is prime
 * @return int 0 if not prime or 1 if prime
 */
int isPrime(int num);

/**
 * @brief Generates the next available prime number
 * 
 * @param num The reference prime number to beat
 * @return int The next available larger prime number
 */
int generatePrime(int num);

#endif