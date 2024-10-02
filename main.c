#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
enum program_options {TIMER = 1, STOPWATCH = 2, QUIT = 3, SETTINGS = 4}; 
typedef int *TIME_UNIT, *USER_OUTPUT; typedef char *ZERO_CHAR;
typedef struct{
    TIME_UNIT time_unit_amount;
    ZERO_CHAR zero_char;
} *time_unit;
typedef struct{
    time_unit hour, minute, second;
} *timer_params;
static timer_params timer_params_mem(timer_params timer_params){
    timer_params->hour = malloc(sizeof(time_unit));
    timer_params->minute = malloc(sizeof(time_unit));
    timer_params->second = malloc(sizeof(time_unit));
    timer_params->hour->time_unit_amount = malloc(sizeof(int));
    timer_params->minute->time_unit_amount = malloc(sizeof(int));
    timer_params->second->time_unit_amount = malloc(sizeof(int));
    timer_params->hour->zero_char = malloc(sizeof(char));
    timer_params->minute->zero_char = malloc(sizeof(char));
    timer_params->second->zero_char = malloc(sizeof(char));
}
static timer_params print_time(timer_params timer_params){
    *timer_params->hour->zero_char = (*timer_params->hour->time_unit_amount < 10) ? '0' : '\0';
    *timer_params->minute->zero_char = (*timer_params->minute->time_unit_amount < 10) ? '0' : '\0';
    *timer_params->second->zero_char = (*timer_params->second->time_unit_amount < 10) ? '0' : '\0';
    printf("%c%d:%c%d:%c%d\n", *timer_params->hour->zero_char, *(timer_params->hour->time_unit_amount), *timer_params->minute->zero_char, *(timer_params->minute->time_unit_amount), *timer_params->second->zero_char, *(timer_params->second->time_unit_amount));
    sleep(1);
}
static timer_params timer_stopwatch(timer_params timer_params, USER_OUTPUT user_output){
    switch (*user_output)
    {
    case TIMER:
        (*(timer_params->second->time_unit_amount))--;
        if((*(timer_params->second->time_unit_amount)) == - 1 && (*(timer_params->minute->time_unit_amount)) != 0){
            (*(timer_params->second->time_unit_amount)) = 59;
            (*(timer_params->minute->time_unit_amount))--;
        }
        if((*(timer_params->second->time_unit_amount)) == - 1 && (*(timer_params->minute->time_unit_amount)) == 0){
            (*(timer_params->second->time_unit_amount)) = 59;
            (*(timer_params->minute->time_unit_amount)) = 59;
            (*(timer_params->hour->time_unit_amount)) = ((*(timer_params->hour->time_unit_amount)) == -1) ? 0 : (*(timer_params->hour->time_unit_amount)) - 1; 
        }
        break;
    case STOPWATCH:
        (*(timer_params->second->time_unit_amount))++;
        if(*(timer_params->second->time_unit_amount) == 60){
            *(timer_params->second->time_unit_amount) = 0;
            *(timer_params->minute->time_unit_amount)++;
        }
        if(*(timer_params->minute->time_unit_amount) == 60){
            *(timer_params->minute->time_unit_amount) = 0;
            *(timer_params->hour->time_unit_amount)++;
        }
        break;
    default:
        break;
    }
}
void main(){
    timer_params timer_params;
    timer_params_mem(timer_params);
    USER_OUTPUT user_output = malloc(sizeof(int));
    printf("1. Timer\n"
           "2. Stopwatch\n"
           "3. Quit\n"
           "Your choice: ");
    scanf("%d", user_output);
    switch(*user_output){
        case TIMER:
            while(1){
                printf("Hour(s): ");
                scanf("%d", timer_params->hour->time_unit_amount);
                printf("Minute(s): ");
                scanf("%d", timer_params->minute->time_unit_amount);
                printf("Second(s): ");
                scanf("%d", timer_params->second->time_unit_amount);
                if(*timer_params->minute->time_unit_amount < 0 || *timer_params->minute->time_unit_amount > 59 || *timer_params->second->time_unit_amount < 0 || *timer_params->second->time_unit_amount > 59){
                    printf("Make sure your seconds and/or minutes don't go over 59 or under 0.");
                }
                else break;
            }
            break;
        case STOPWATCH:
            *timer_params->hour->time_unit_amount = 0;
            *timer_params->minute->time_unit_amount = 0;
            *timer_params->second->time_unit_amount = 0;
        case QUIT: exit(1);
        default: break;
    }    
    while((*user_output == TIMER) ? (*timer_params->hour->time_unit_amount != 0 || *timer_params->minute->time_unit_amount != 0 || *timer_params->second->time_unit_amount != 0) : 1){
        print_time(timer_params);
        timer_stopwatch(timer_params, user_output);
    } 
}
