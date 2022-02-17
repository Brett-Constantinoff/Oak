#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class Timer{
    private:
        static std::chrono::high_resolution_clock::time_point m_start;
        static std::chrono::high_resolution_clock::time_point m_stop;
        static std::chrono::duration<double> m_time;
    private:
        Timer(){};
    public:
        static void start(void);
        static void stop(void);
};

#endif