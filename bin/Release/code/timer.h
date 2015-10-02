#ifndef TIMER_H
#define TIMER_H

class Timer
{
    private:
        int startTicks;
        bool started;
    public:
        Timer();
        void start();
        int get_ticks();
};

#endif
