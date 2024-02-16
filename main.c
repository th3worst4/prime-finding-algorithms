#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void displayHelp(){
    printf("Prime finder. This program uses different prime finding algorithms, they diverge on execution time and memory usage. \nUsage: primes [options] <unsigned int>\n");
    printf("Options:\n-h: display this help\n-r: display a bool for the last result only[default]\n-l: display a long list with time and memory info\n-s: display a short list with primes only\n-i: display only the last result, the elapsed time and memory usage\n");
    printf("-t: uses Trial Division Algorithm, it uses less memory but more time\n-e: uses Sieve of Eratosthenes Algorithm, it uses more memory but is pretty fast[default]\n"); 
    printf("You can combine one display method with one algorithm, eg.: -ld\n");
}

void printTable(bool *numberArray, unsigned int size){
    for(unsigned int i = 0; i < size; i++){
        printf("%u is %s\n", i+1, *(numberArray+i) ? "prime" : "not prime");
    }
}

void printArray(unsigned int *primeArray, size_t size){
    for(size_t i = 0; i < size; i++) printf("%u\n", *(primeArray+i));
}

void trial_division(unsigned int n, int print){
    unsigned int *primes = malloc(n*sizeof(unsigned int));

    clock_t time_req = clock();
    *primes = 2;
    size_t numberofprimes = 1;

    for(unsigned int i = 3; i <= n; i++){
        bool isprime = true;
        for(size_t j = 0; j < numberofprimes; j++){
            if((*(primes+j))*(*(primes+j)) > i) break; //wtf sqrt is faster than pow??
            isprime = (i % *(primes+j) == 0)? false : true;
            if(!isprime) break;
        }
        if(isprime){
            *(primes+numberofprimes) = i;   
            numberofprimes++;
        }
    }
    time_req = clock() - time_req;
    primes = realloc(primes, numberofprimes*sizeof(unsigned int));
    
    if(print == 0){
        printf("%s\n", (*(primes+numberofprimes-1) == n) ? "true" : "false");
    }else if(print == 1){
        printArray(primes, numberofprimes);
        printf("Time taken: %f seconds\n", (float)time_req / CLOCKS_PER_SEC); 
        printf("Memory used: %luB\n", n*(sizeof(bool)+sizeof(unsigned int)));
    }else if(print == 2){
        printArray(primes, numberofprimes); 
    }else if(print == 3){
        printf("%s\n", (*(primes+numberofprimes-1) == n) ? "true" : "false");
        printf("Time taken: %f seconds\n", (float)time_req / CLOCKS_PER_SEC); 
        printf("Memory used: %luB\n", n*sizeof(unsigned int)); 
    } 

    free(primes);
}

void sieve_of_eratosthenes(unsigned int n, int print){
    bool *numberArray = malloc(n);
    unsigned int *primes = malloc(n*sizeof(unsigned int));
    size_t numberofprimes = 0;
    memset(numberArray, true, n*sizeof(bool));

    clock_t time_req = clock();
    for(unsigned int i = 1; i < n; i++){
        if(*(numberArray+i)){
            *(primes+numberofprimes) = i+1;
            numberofprimes++;

            unsigned int j = 2;
            while((i+1)*j <= n){
                *(numberArray+(i+1)*j-1) = false;
                j++;
            }
        }else{
            continue;
        }
    }
    time_req = clock() - time_req;
    
    primes = realloc(primes, numberofprimes*sizeof(unsigned int));
    
    if(print == 0){
        printf("%s\n", (*(numberArray+n-1)) ? "true" : "false");
    }else if(print == 1){
        printTable(numberArray, n);
        printf("Time taken: %f seconds\n", (float)time_req / CLOCKS_PER_SEC); 
        printf("Memory used: %luB\n", n*(sizeof(bool)+sizeof(unsigned int)));
    }else if(print == 2){
        printArray(primes, numberofprimes); 
    }else if(print == 3){
        printf("%s\n", (*(numberArray+n-1)) ? "true" : "false");
        printf("Time taken: %f seconds\n", (float)time_req / CLOCKS_PER_SEC); 
        printf("Memory used: %luB\n", n*(1+sizeof(unsigned int))); 
    } 
    
    free(numberArray);    
    free(primes);
}

int main(int argc, char **argv){
    if(argc < 2){
        printf("Wrong usage\nTry \"primes -h\" to get some help\n");
        return -1;
    }
    
    unsigned int n;
    if(!strncmp(*(argv+1), "-", 1)){
        if(argc == 3) n = strtol(*(argv+2), (argv+3), 0);
        int len = strlen(*(argv+1));
        if(len > 3){
            printf("Wrong usage\n Try \"primes -h\" to get some help\n");
            return -1;
        }
        int sum = (*(*(argv+1)+1)) + (*(*(argv+1)+2));
        switch (sum) {
            case 104: //h
                displayHelp();
                break; 
            case 206: //ie
                sieve_of_eratosthenes(n, 3);
                break;
            case 209: //le
                sieve_of_eratosthenes(n, 1);
                break;
            case 215: //re
                sieve_of_eratosthenes(n, 0);
                break;
            case 216: //se
                sieve_of_eratosthenes(n, 2);
                break;

            case(221): //it
                trial_division(n, 3);
                break;
            case 224: //lt
                trial_division(n, 1);
                printf("NOTE: Trial Division does not return the same long output as Eratosthenes\n");
                break;
            case 230: //rt
                trial_division(n, 0);
                break;
            case 231: //st
                trial_division(n, 2);
                break;
        }       
    }else {
        if(argc == 2) n = strtol(*(argv+1), (argv+2), 0);
        sieve_of_eratosthenes(n, 0);
    }
    
    
    return 0;
}
