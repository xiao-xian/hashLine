#ifndef HELPERS_H
#define HELPERS_H

#include <sys/time.h>
using namespace std;

void startHashTimer( timeval& i_startTimer )
{
    gettimeofday( &i_startTimer, NULL );
}

double stopHashTimer( timeval& i_startTimer )
{
    timeval end;
    gettimeofday( &end, NULL );

    return ( ( (          end.tv_sec * 1000000 +          end.tv_usec ) -
               ( i_startTimer.tv_sec * 1000000 + i_startTimer.tv_usec ) ) / 1000000.0);
}

#endif // HELPERS_H
