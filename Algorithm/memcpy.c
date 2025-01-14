
// memcpy thực hiện việc copy data số tới vùng nhớ khác để xử lí
#include<stdio.h>
#include<stdlib.h> // Quản lí bộ nhớ với malloc(), calloc(), realloc(), free(), toán học
#include <string.h> // Quản lí và chứa memcpy
#include <stdint.h>

void Read_Toorque_Sensor(uint8_t *TorqueSensor, uint8_t numSenSor)
{
    for (uint8_t i = 0; i < numSenSor; i++){
        TorqueSensor[i] = rand() % 256;
        printf("TorqueSensor[%d]: %d\n", i, TorqueSensor[i]);
    }
}

int main()
{
    uint8_t numSenSorEps = 8;
    uint8_t SenSor_Eps[numSenSorEps]; 
    uint8_t copydataSenSor[numSenSorEps];

    Read_Toorque_Sensor(SenSor_Eps, numSenSorEps);  // don't have &SenSor_Eps, because we are pointing to SenSor_Eps[0]

    memcpy(copydataSenSor, SenSor_Eps, numSenSorEps);

    for (uint8_t i = 0; i < numSenSorEps; i++){
        printf("copydataSenSor[%d]: %d\n", i, copydataSenSor[i]);
    }

    return 0;  
}

// Statement	Purpose	                    Scope	                    Typical Use Case
// return 0	    Success	                    Returns to caller (main)	Indicating successful program execution.
// return 1	    Generic error or failure	Returns to caller	        Indicating an error occurred.
// return -1	Specific error or failure	Returns to caller	        Indicating a specific type of error.
// exit(0)	    Success	                    erminates program	        Immediate termination with success.
// exit(1)	    Error	                    Terminates program	        Immediate termination with error.

 