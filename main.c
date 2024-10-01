#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
enum program_options {TIMER = 1, STOPWATCH = 2}; 
typedef int *USER_OUTPUT, *HOUR, *MINUTE, *SECOND; 
typedef struct{
    HOUR hour; 
    MINUTE minute; 
    SECOND second;
} *timer_params;
// inconvenient solution. make it better.
void print_time(timer_params timer_params){
    char hour_zero = '\0', minute_zero = '\0', second_zero = '\0';
    if(*(timer_params->hour) < 10){
        hour_zero = '0';
    }
    if(*(timer_params->minute) < 10){
        minute_zero = '0';
    }
    if(*(timer_params->second) < 10){
        second_zero = '0';
    }
    printf("%c%d:%c%d:%c%d\n", hour_zero, *(timer_params->hour), minute_zero, *(timer_params->minute), second_zero, *(timer_params->second));
    sleep(1);
}
void timer_stopwatch(timer_params timer_params, int user_output){
    switch (user_output)
    {
    case TIMER:
        (*(timer_params->second))--;
        if(*(timer_params->second) == - 1 && *(timer_params->minute) != 0){
            *(timer_params->second) = 59;
            (*(timer_params->minute))--;
        }
        if(*(timer_params->second) == - 1 && *(timer_params->minute) == 0){
            *(timer_params->hour) = (*(timer_params->hour) == -1) ? 0 : *(timer_params->hour) - 1; 
            *(timer_params->second) = 59;
            *(timer_params->minute) = 59;
        }
        break;
    case STOPWATCH:
        (*(timer_params->second))++;
        if(*(timer_params->second) == 60){
            *(timer_params->second) = 0;
            *(timer_params->minute)++;
        }
        if(*(timer_params->minute) == 60){
            *(timer_params->minute) = 0;
            *(timer_params->hour)++;
        }
        break;
    default:
        break;
    }
}
void main(){
    timer_params timer_params = malloc(sizeof(timer_params)); 
    timer_params->hour = malloc(sizeof(int));
    timer_params->minute = malloc(sizeof(int));
    timer_params->second = malloc(sizeof(int));
    USER_OUTPUT user_output = malloc(sizeof(int));
    printf("1. Timer\n"
           "2. Stopwatch\n"
           "Your choice: ");
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
            *timer_params->hour = 0;
            *timer_params->minute = 0;
            *timer_params->second = 0;
        default:
            break;
    }    
    while((*user_output == TIMER) ? (*timer_params->hour != 0 || *timer_params->minute != 0 || *timer_params->second != 0) : 1){
        print_time(timer_params);
        timer_stopwatch(timer_params, *user_output);
    }
}
