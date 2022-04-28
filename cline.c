#include "cline.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Implementation of getch() from ncurses.h just without all the ncurses shenanigans */
int getch(void) {
    int c, res = 0;

    struct termios org_opts, new_opts;

    res=tcgetattr(STDIN_FILENO, &org_opts);

    new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);

    c = getchar();
    res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);

    return(c);
}

/* I have to implement kbhit() because glibc is stoopid */
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}

void concat_c(char *str, char c)
{
    for (; *str; str++);
    *str++ = c;
    *str++ = 0;
}

void start_selection(selection_config *config)
{
    /* Initialize the reactive prompt */
    char *prompt = malloc(sizeof(config->selection_prompt) + 2);

    /* single char buffer for input */
    char buf;

    /* Print all of the options just for debugging for now*/
    for (int i = 0; i < 10; i++ )
    {
        printf("%d. %s\n", i+1, config->values[i].name);
    }

    /* Copy the contents of selection_prompt for initial prompt */
    strncpy(prompt, config->selection_prompt, strlen(config->selection_prompt));

    restart:

    /* join the single char to the prompt */
    concat_c(prompt, buf);
    printf("\r%s", prompt);

    while (1) {

        /* if a keystroke is detected */
        if (kbhit()) {

            /* if the keystroke is enter, do nothing else add the input to the prompt */
            if((buf = (char)getch()) == 10)
                continue;
            else
                goto restart;
        }
    }

    free(prompt);
}

selection_config *new_config(int max, selection_value* values, char* prompt)
{
    selection_config *new = malloc(sizeof(selection_config));
    new->total = max;
    new->values = values;
    new->selection_prompt = prompt;

    return new;
}
