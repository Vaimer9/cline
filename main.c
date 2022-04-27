#include <stdio.h>
#include <stdlib.h>
#include "cline.h"

#define findsize(VAL, TYPE) sizeof(VAL)/sizeof(TYPE) 

int main()
{
    selection_value values[] = {
        { "One" },
        { "Two" },
        { "Three" },
        { "Four" },
        { "Five" },
        { "Six" },
        { "Seven" },
        { "Eight" },
        { "Nine" },
        { "Ten" },
        { "Eleven" },
        { "Twelve" },
        { "Thirteen" },
        { "Fourteen" },
        { "Fifteen" },
        { "Sixteen" },
        { "Seventeen" },
        { "Eighteen" },
    };
    selection_config *config = new_config(
        findsize(values, selection_value),
        values,
        "Select the given options: "
    );

    start_selection(config);

    return 0;
}
