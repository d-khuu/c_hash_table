/**
 * @file prime.h
 * @author Danny Khuu
 * @brief 
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PRIME_H
#define PRIME_H

/**
 * @brief Checks for prime numbers faster 
 * than the example in Wikipedia (Take that!)
 * 
 * @param num Number to be evaluated
 * @return int 0 = not prime, 1 = prime
 */
int isPrime(int num);

/**
 * @brief Generates the next available prime number.
 * 
 * @param num The reference prime number to beat
 * @return int The next available greater prime number
 */
int generatePrime(int num);

#endif