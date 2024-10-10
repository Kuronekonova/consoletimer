#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ALLOC_MEM 0
#define FREE_MEM 1

enum program_options {TIMER = 1, STOPWATCH = 2, QUIT = 3, SETTINGS = 4}; 
typedef int *TIME_UNIT, *USER_OUTPUT; typedef char *ZERO_CHAR; typedef FILE * TIMER_FILE;

typedef struct{TIME_UNIT hour, minute, second;} *timer_params;
static timer_params timer_params_mem(timer_params timer_params, int free_memory){
    switch (free_memory)
    {
    case ALLOC_MEM:
        timer_params->hour = malloc(sizeof(int));
        timer_params->minute = malloc(sizeof(int));
        timer_params->second = malloc(sizeof(int));
        break;
    case FREE_MEM:
        free(timer_params->hour);
        free(timer_params->minute);
        free(timer_params->second);
        break;
    default:
        break;
    }
}
static timer_params print_time(timer_params timer_params){
    printf("%c%d:%c%d:%c%d\n", (*timer_params->hour < 10) ? '0' : '\0', 
                               *timer_params->hour, 
                               (*timer_params->minute < 10) ? '0' : '\0', 
                               *timer_params->minute, 
                               (*timer_params->second < 10) ? '0' : '\0', 
                               *timer_params->second);
    sleep(1);
}
static timer_params timer_stopwatch(timer_params timer_params, USER_OUTPUT user_output){
    switch (*user_output)
    {
    case TIMER:
        (*(timer_params->second))--;
        if((*(timer_params->second)) == - 1 && (*(timer_params->minute)) != 0){
            (*(timer_params->second)) = 59;
            (*(timer_params->minute))--;
        }
        if((*(timer_params->second)) == - 1 && (*(timer_params->minute)) == 0){
            (*(timer_params->second)) = 59;
            (*(timer_params->minute)) = 59;
            (*(timer_params->hour)) = ((*(timer_params->hour)) == -1) ? 0 : (*(timer_params->hour)) - 1; 
        }
        break;
    case STOPWATCH:
        (*(timer_params->second))++;
        if(*(timer_params->second) == 60){
            *(timer_params->second) = 0;
            (*(timer_params->minute))++;
        }
        if(*(timer_params->minute) == 60){
            *(timer_params->minute) = 0;
            (*(timer_params->hour))++;
        }
        break;
    default:
        break;
    }
}
static timer_params timer_ended_alert(timer_params timer_params){
    if(*timer_params->hour == 0 && *timer_params->minute == 0 && *timer_params->second== 0){
        fprintf(stdout, "Your timer has ended!\n");
    }
}
void main(){
    while(1){
        timer_params timer_params;
        timer_params_mem(timer_params, ALLOC_MEM);
        USER_OUTPUT user_output = malloc(sizeof(int));
        printf("1. Timer\n2. Stopwatch\n3. Quit\nYour choice: ");
        scanf("%d", user_output);
        switch(*user_output){
            case TIMER:
                while(1){
                    printf("Hour(s): ");
                    scanf("%d", timer_params->hour);
                    printf("Minute(s): ");
                    scanf("%d", timer_params->minute);
                    printf("Second(s): ");
                    scanf("%d", timer_params->second);
                    if(*timer_params->minute < 0 || *timer_params->minute > 59 || *timer_params->second < 0 || *timer_params->second > 59){
                        printf("Make sure your seconds and/or minutes don't go over 59 or under 0.");
                    }
                    else break;
                }
                break;
            case STOPWATCH:
                *(timer_params->hour) = 0;
                *(timer_params->minute) = 0;
                *(timer_params->second) = 0;
                break;
            case QUIT: exit(1);
            default: break;
        }
        while((*user_output == TIMER) ? (*timer_params->hour != 0 || *timer_params->minute != 0 || *timer_params->second != 0) : 1){
            print_time(timer_params);
            timer_stopwatch(timer_params, user_output);
        } 
        timer_params_mem(timer_params, FREE_MEM);
    }
}
