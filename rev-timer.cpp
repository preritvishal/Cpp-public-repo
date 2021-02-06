#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>

#define DEBUG false

typedef struct DateStr
{ // struct to store date input
    unsigned short day, month, year;
} DateStr;

typedef struct CurrentTimeStr
{ // struct to fetch and store current time from system
    unsigned short day, month, year, hrs, min, sec;
} CurrentTimeStr;

typedef struct RemainingTime
{
    unsigned short hrs, min, sec;
} RemainingTime;

std::string takeInput()
{ // function to take date input

    std::cout << "Enter Date as [ DD-MM-YY ]  :   ";

    std::string input;
    std::cin >> input;
    return input;
}

DateStr extractDate(std::string in)
{ // function to extract date from string format
    DateStr usr_in;
    usr_in.day = ((in.at(0) - 48) * 10) + (in.at(1) - 48);
    usr_in.month = ((in.at(3) - 48) * 10) + (in.at(4) - 48);
    usr_in.year = ((in.at(6) - 48) * 10) + (in.at(7) - 48);

    return usr_in;
}

CurrentTimeStr getCurrentTime()
{                                 // fetch system date and time
    time_t time_var = time(NULL); //creating time var of type time_t
    struct tm *tm_str_ptr = localtime(&time_var);
    // passing refernce of time_var to function local time which retruns pointer to struct tm

    CurrentTimeStr cur_time;
    cur_time.day = tm_str_ptr->tm_mday;
    cur_time.month = tm_str_ptr->tm_mon + 1;
    cur_time.year = tm_str_ptr->tm_year - 100;
    cur_time.hrs = tm_str_ptr->tm_hour;
    cur_time.min = tm_str_ptr->tm_min;
    cur_time.sec = tm_str_ptr->tm_sec;

    return cur_time;
}

std::string takeNote()
{
    std::string note_for_timer;
    std::cout << "Enter a label for timer : ";
    std::cin.get();
    getline(std::cin, note_for_timer);

    return note_for_timer;

}

RemainingTime conversionLogic(DateStr date_input, CurrentTimeStr current_time)
{
    RemainingTime remain_time;

    unsigned short rem_year = date_input.year - current_time.year ;

    if( date_input.month < current_time.month ){
        --rem_year;
        date_input.month += 12;
    }

    unsigned short rem_month = date_input.month - current_time.month;
    
    if( date_input.day < current_time.day ){
        --rem_month;
        date_input.day += 30;
    }

    unsigned short rem_day = date_input.day - (current_time.day + 1) ;   

    remain_time.hrs = 24 - (current_time.hrs + 1);
    remain_time.min = 60 - (current_time.min + 1);
    remain_time.sec = 60 - current_time.sec;

    while(rem_day){
        --rem_day; 
        remain_time.hrs += 24;
    }

    return remain_time;
}

void displayTimer(RemainingTime remains, std::string label, DateStr timer_date)
{

    while ( true )
    {
        // countdown logic 

        if(!remains.sec){
            --remains.min;
            remains.sec += 59;
        }

        if(!remains.min){
            --remains.hrs;
            remains.min += 59;
        }

        sleep(1);
        system("clear");
        --remains.sec ;

        std::cout << std::setfill(' ')
                  << std::setw(40)
                  << "Timer for date : "
                  << timer_date.day ;
                  switch(timer_date.day)
                  {
                        case 1 : std::cout << "st ";
                                break;
                        case 2 : std::cout << "nd ";
                                break;
                        case 3 : std::cout << "rd ";
                                break;
                        default : std::cout << "th ";
                                break;
                  }

        switch(timer_date.month)
        {
            case 1 : std::cout << "Jan ";break;
            case 2 : std::cout << "Feb ";break;
            case 3 : std::cout << "Mar ";break;
            case 4 : std::cout << "Apr ";break;
            case 5 : std::cout << "May ";break;
            case 6 : std::cout << "Jun ";break;
            case 7 : std::cout << "Jul ";break;
            case 8 : std::cout << "Aug ";break;
            case 9 : std::cout << "Sep ";break;
            case 10 : std::cout << "Oct ";break;
            case 11 : std::cout << "Nov ";break;
            case 12 : std::cout << "Dec ";break;
        }

        std::cout << "20" << timer_date.year
                  << std::endl << std::endl ;
        
        std::cout << std::setfill(' ') << std::setw(43) << label << std::endl;

        std::cout << std::setfill(' ') << std::setw(58) << " --------------------------------- " << std::endl;

        std::cout << std::setfill(' ') << std::setw(29);

        std::cout << " | " << std::setfill('0') << std::setw(2) << remains.hrs << " hrs | ";
        std::cout << std::setfill('0') << std::setw(2) << remains.min << " min | ";
        std::cout << std::setfill('0') << std::setw(2) << remains.sec << " sec | " << std::endl;

        std::cout << std::setfill(' ') << std::setw(58) << " --------------------------------- " << std::endl;
    }
}

int main()
{
    DateStr date_var = extractDate(takeInput());
    CurrentTimeStr cur_date_var = getCurrentTime();
    std::string note = takeNote();

    RemainingTime rem_var = conversionLogic(date_var, cur_date_var);

    displayTimer(rem_var,note,date_var);

    #if DEBUG
        std::cout   << "Date : " << date_var.day << " " << date_var.month << " " << date_var.year << std::endl ;

        std::cout << "Current time : "
                << cur_date_var.hrs << " hours " 
                << cur_date_var.min << " mins " 
                << cur_date_var.sec << " seconds "
                << std::endl 
                << cur_date_var.day << " days " 
                << cur_date_var.month << " months " 
                << cur_date_var.year << " years "
                << std::endl << std::endl ;

        std::cout << "Remaining time : "
                << rem_var.hrs << " hrs "
                << rem_var.min << " mins "
                << rem_var.sec << " secs "
                << std::endl << std::endl ;

    #endif
    return 0;
}