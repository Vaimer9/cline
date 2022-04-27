#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    const char *name;
    /* Other fields will be added soon */
} selection_value;

typedef struct 
{
    int total;
    selection_value *values;
    char *selection_prompt;
} selection_config;

void startSelection(selection_config *config);
selection_config *new_config(int max, selection_value* values, char* prompt);
