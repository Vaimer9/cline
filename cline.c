#include "cline.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

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

void startSelection(selection_config *config)
{
    char input;

    /* Print all of the options*/
    for (int i = 0; i < 10; i++ )
    {
        printf("%d. %s\n", i+1, config->values[i].name);
    }

    printf("%s", config->selection_prompt);
    while (1) {
        if (kbhit()) {
            input = (char)getch();
            printf("\nYou pressed: %c\n", input);
            break;
        }
    }
    printf("oh wow\n");
}

selection_config *new_config(int max, selection_value* values, char* prompt)
{
    selection_config *new = malloc(sizeof(selection_config));
    new->total = max;
    new->values = values;
    new->selection_prompt = prompt;

    return new;
}

