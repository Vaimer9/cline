#include <stdio.h>
#include <stdlib.h>
#include "cline.h"

#define findsize(VAL, TYPE) sizeof(VAL)/sizeof(TYPE) 

int main()
{
    selection_value values[] = {
        { "Hi" },
        { "How are you today" },
        { "Fine" },
        { "Fine" },
        { "Fine" },
        { "Fine" },
        { "Fine" },
        { "Fine" },
        { "Fine" },
        { "Fine" },
        { "Fine" },
        { "Fine" },
        { "Fine" },
        { "but better Fine" },
        { "but better Fine" },
        { "but better Fine" },
        { "but better Fine" },
        { "but better Fine" },
    };
    selection_config *config = new_config(
        findsize(values, selection_value),
        values,
        "Select the given options: "
    );

    startSelection(config);

    return 0;
}
