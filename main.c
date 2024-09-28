#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>



// so, this could either be something like a stopwatch, or a
// timer, but I'll make both.




enum program_options {TIMER, STOPWATCH};
typedef int USER_OUTPUT;
typedef int HOUR;
typedef int MINUTE;
typedef int SECOND;
typedef struct{
    HOUR hour;
    MINUTE minute;
    SECOND second;
} timer_params;


// inconvenient solution. make it better.
void print_time(HOUR hour, MINUTE minute, SECOND second){
    char hour_zero = '\0', minute_zero = '\0', second_zero = '\0';
    if(hour < 10){
        hour_zero = '0';
    }
    if(minute < 10){
        minute_zero = '0';
    }
    if(second < 10){
        second_zero = '0';
    }
    printf("%c%d:%c%d:%c%d\n", hour_zero, hour, minute_zero, minute, second_zero, second);
    sleep(1);
}

// Stopwatch. Never stops.
void stopwatch(){
    HOUR hour = 0;
    MINUTE minute = 0;
    SECOND second = 0;
    while(1){
        print_time(hour, minute, second);
        second++;
        if(second==60){
            second = 0;
            minute++;
        }
        if(minute==60){
            minute=0;
            hour++;
        }
    }
}
// A good old timer. Self explanatory.
void timer(HOUR hour, MINUTE minute, SECOND second){
    while(hour != 0 || minute != 0 || second != 0){
        print_time(hour, minute, second);
        second--;
        if(second == -1 && minute != 0){
            second = 59;
            minute--;
        }
        if(second == -1 && minute == 0){
            hour = (hour == -1) ? 0 : hour-1;
            minute = 59;
            second = 59;
        }
    }
    if(hour == 0 && minute == 0 && second == 0){
        print_time(hour, minute, second);
        printf("Your timer has finished.\n");
    }
}




void main(){
    USER_OUTPUT choice;
    timer_params timer_params;
    printf("Welcome to the most useless C program to have ever been created.\n"
"How shall I waste your time in this fine evening?\n"
"1. Timer\n"
"2. Stopwatch\n"
"Your Choice: ");                       
    scanf("%d", &choice);
    switch (choice)
    {
    case TIMER + 1:
        while(1)
        {
            printf("Hour(s): ");
            scanf("%d", &timer_params.hour);
            printf("Minute(s): ");
            scanf("%d", &timer_params.minute);
            printf("Second(s): ");
            scanf("%d", &timer_params.second);
            if(!(0 < timer_params.minute && timer_params.minute < 60 && 0 < timer_params.second && timer_params.second < 60)){
                printf("Make sure your minutes and/or seconds don't go over 59 and under 0.\n");
            }
            else break;
        }
        printf("Beginning timer.\n");
        sleep(1);
        timer(timer_params.hour, timer_params.minute, timer_params.second);
        break;
    case STOPWATCH + 1:
        printf("Beginning stopwatch.\n");
        sleep(1);
        stopwatch();
        break;
    default:
        break;
    }
}