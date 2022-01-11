/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#pragma once

#include <stddef.h>

/**
 * @brief Меняет порядок символов в строке на противоположный
 * 
 * @param str Строка для преобразования на месте
 */
void strver(char *str);

/**
 * @brief Функция для записи числа в строчном представлении
 * 
 * @param n Исходное число
 * @param buffer Буфер для записи
 * @return Длину результирующей строки
 */
int itoa(int n, char *buffer);