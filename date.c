#include "types.h"
#include "stat.h"
#include "date.h"
#include "user.h"

int main(void)
{
    struct rtcdate rtc;

    rtc.second=1;
    if (getdate(&rtc) == -1)
    {
        printf(2, "Error getdate");
        exit();
    }

    printf(1,"%d/%d/%d  %d:%d:%d\n",rtc.day,rtc.month,rtc.year,rtc.hour,rtc.minute,rtc.second);
    exit();
}