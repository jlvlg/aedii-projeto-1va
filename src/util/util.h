#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

/// @file
/// Provides general use shortcuts and functions

/// Encapsulates functions into the util namespace
struct util_methods {
    /// @brief Tries to allocate memory and exits the program with error code 1 in case of failure to do so
    /// @param size Size in bits
    void* (*safe_malloc)(size_t size);

    /// @brief Allocates enough space in memory for a string
    /// @return Pointer to allocated memory
    char* (*string_malloc)(char string[]);

    /// @brief Allocates memory and copy the contents of a string into it
    /// @return The copied string
    char* (*init_string)(char string[]);

    /// @brief Compares two strings in lowercase
    /// @return 0 if str1 == str2 @n>0 if str1 > str2 @n<0 if str1 < str2
    int (*lowercmp)(char str1[], char str2[]);

    /// @brief Max between two numbers
    /// @return Greatest number
    int (*max)(int a, int b);
};

extern const struct util_methods util;

#endif