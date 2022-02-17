#include "Timer.h"
#include <iostream>

std::chrono::high_resolution_clock::time_point Timer::m_start;
std::chrono::high_resolution_clock::time_point Timer::m_stop;
std::chrono::duration<double> Timer::m_time;

void Timer::start(void){
    m_start = std::chrono::high_resolution_clock::now();
};

void Timer::stop(void){
    m_stop = std::chrono::high_resolution_clock::now();
    m_time = std::chrono::duration_cast<std::chrono::duration<double>>(m_stop - m_start);
    std::cout << "Proccess took " << m_time.count() << " seconds." << "\n";
}