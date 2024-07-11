#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Boolean Data Type */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned char boolean;

/* Unsigned Data Types */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;


/* Signed Data Types */
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;

/* Other common types */
typedef unsigned char uint8_least;
typedef unsigned short uint16_least;
typedef unsigned long uint32_least;
typedef signed char sint8_least;
typedef signed short sint16_least;
typedef signed long sint32_least;
typedef float float32;
typedef double float64;

/* Standard Return Type */
typedef uint8 Std_ReturnType;

#define E_OK 0x00
#define E_NOT_OK 0x01

#endif /* STD_TYPES_H */
