#include <stdio.h>
#include <stdlib.h>

//piecewise recurrence relation: F(n) = F(n-3) + F(n -2) where F(0) = 0, F(1) = 1, and F(2) = 2.

// method 1 -> recursion method

//Time Complexity: Exponential
//Auxiliary space complexity: O(n)  (maximum depth of the recursion tree is n.)

// recursion tree
//              F(n)
///              / \
//      F(n-3)           F(n-2)
///        /\            /   \
//   F(n-6) F(n-5)     F(n-4) F(n-3)
//


int fib1(int n)
{
    if (n <= 2)
        return n;
    return fib1(n - 2) + fib1(n - 3);
}



// using Dynamic Programming

//Time complexity: O(n) for given n
//Auxiliary space: O(n)
int fib2(int n)
{
    /* Declare an array to store Fibonacci numbers. */
    int f[n+2];   // 1 extra to handle case, n = 0
    int i;

    /* 0th and 1st number of the series are 0 and 1*/
    f[0] = 0;
    f[1] = 1;
    f[2] = 2;

    for (i = 3; i <= n; i++)
    {
        /* Add the previous 2 numbers in the series
           and store it */
        f[i] = f[i-2] + f[i-3];
    }

    return f[n];
}


//space optimized method

//we utilize storing (like dp),however, the two numbers (n-2 & n-3) only because that is all we need to get the next Fibonacci number in series.
//Time Complexity: O(n)
//Extra Space: O(1)

//d will always be equal to a+b
// to get the n-2 and n-3 numbers, we put equate a to b and b to c (since c starts at 2), we also change equate c to d
// example testcase for fib(5): at n=3 -> d should be (n-2 + n-3 ) which is 0 + 1
// since at 4, d should be 2+1 -> then a should be the previous b (1) and b should be the previous c (2) to achieve the needed results
// c equates to d at the end of each iteration so that it can be (n-2) for the number at the next iteration and so on
int fib3(int n)
{
    int a = 0, b = 1, c = 2, d, i;

    if (n<=2) return n;

    for (i = 3; i <= n; i++)
    {
        d = a + b;
        a = b;
        b = c;
        c = d;
    }
    return d;
}

// Another approach I found interesting is the Binet’s formula
// Fn = {[(√5 + 1)/2] ^ n} / √5
// However, it only works up to n = 71
// Time Complexity: O(logn)
// Auxiliary Space: O(1)


void main() {
    int method1, method2, method3;
    for (int i = 0; i < 20; i++) {
        method1 = fib1(i);
        method2 = fib2(i);
        method3 = fib3(i);
        printf("F(%d):\n", i);
        printf("Way One: %-4d  Way Two: %-4d  Way Three: %d\n", method1, method2, method3);
    }
}