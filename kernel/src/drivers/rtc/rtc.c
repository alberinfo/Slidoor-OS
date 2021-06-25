#include "rtc.h"

#define ADDRESS_REG     0x70
#define DATA_REG        0x71

/* Values/Commands for RTC Registers */
#define SECOND          0x00    //Second      00-59
#define MINUTE          0x02    //Minute      00-59
#define HOUR            0x04    //Hour        00-23
#define DAY_OF_WEEK     0x06    //Day of Week 01-0DAY
#define DAY             0x07    //Day         00-31
#define MONTH           0x08    //Month       00-12
#define YEAR            0x09    //Year        00-99

uint8 Century_reg = 0;

void setRTCenturyReg(uint8 value)
{
    Century_reg = value;
}

uint8 uint_to_bcd(uint8 value)
{
    uint8 hi, lo;
    if(value > 99)
    {
        return 0xFF;
    };
    lo = value % 10;
    hi = (value / 10);
    hi *= 16;
    return hi | lo;
}

int bcd_to_int(uint8 bcd)
{
    char characters[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int ret = 0;
    ret = ((bcd & 0xF0) >> 4) * 10 + (bcd & 0xF);
    return ret;
}

/* Function to Get any RTC Parameter */
uint8 get_RTC_val(uint8 param)
{
    CPUDisableInts();
    outportb(ADDRESS_REG, param);
    CPUEnableInts();
    return inportb(DATA_REG);
}

bool isupdateinprogress()
{
    return get_RTC_val(0x0A) & 0x80;
}

/* Function to Set any RTC Parameter */
void set_RTC_val(uint8 setVal)
{
    CPUDisableInts();
    outportb(ADDRESS_REG, setVal);
    outportb(setVal, DATA_REG);
    CPUEnableInts();
}

int getRtc(int option)
{
    //Option; 0 = second, 1 = minute, 2 = hour, 3 = day, 4 = month, 5 = year
    uint8 second, lastsecond, minute, lastminute, hour,lasthour, day,lastday,month,lastmonth, year, lastyear, century, lastcentury;
    while(isupdateinprogress());
    second = get_RTC_val(SECOND);
    minute = get_RTC_val(MINUTE);
    hour = get_RTC_val(HOUR);
    day = get_RTC_val(DAY);
    month = get_RTC_val(MONTH);
    year = get_RTC_val(YEAR);
    if(Century_reg != 0)
    {
        century = get_RTC_val(Century_reg);
    }
    do
    {
        lastsecond = second;
        lastminute = minute;
        lasthour = hour;
        lastday = day;
        lastmonth = month;
        lastyear = year;
        lastcentury = century;
        while(isupdateinprogress());
        second = get_RTC_val(SECOND);
        minute = get_RTC_val(MINUTE);
        hour = get_RTC_val(HOUR);
        day = get_RTC_val(DAY);
        month = get_RTC_val(MONTH);
        year = get_RTC_val(YEAR);
        if(Century_reg != 0)
        {
            century = get_RTC_val(Century_reg);
        }
    } while((lastsecond != second) || (lastminute != minute) || (lasthour != hour) || (lastday !=day) || (lastmonth != month) || (lastyear != year) || (lastcentury != century));
    if(option == 0)
    {
        return bcd_to_int(second);
    } else if(option == 1) {
        return bcd_to_int(minute);
    } else if(option == 2) {
        return bcd_to_int(hour);
    } else if(option == 3) {
        return bcd_to_int(day);
    } else if(option == 4) {
        return bcd_to_int(month);
    } else if(option == 5) {
        if(Century_reg) return (bcd_to_int(year) + bcd_to_int(century)*100);
        else
        {
            int Year = bcd_to_int(year) + (2021/100)*100;
            if(Year < 2021) return Year+100;
            return Year;
        }
    }
    return NULL;
}
