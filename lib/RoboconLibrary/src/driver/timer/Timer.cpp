#include "driver/timer/Timer.hpp"
#include "driver/timer/Clock.hpp"   // DWTラッパー想定
#include "core/System.hpp"


Timer::Timer() {
    start_time = 0;
    accumulated = 0;
    running = false;
}

 void Timer::class_initialized() const {
    if(initialized) return;

    MCU_Init();
    Clock::init();
    Clock::Update();
    
    initialized = true;
}

void Timer::start() {
    class_initialized();

    if (!running) {
        Clock::Update();
        start_time = Clock::now();
        running = true;
    }
}

void Timer::stop() {
    class_initialized();

    if (running) {
        Clock::Update();
        accumulated = (uint64_t)(Clock::now() - start_time);
        running = false;
    }
}

void Timer::reset() {
    class_initialized();

    accumulated = 0;
    Clock::Update();
    if (running) {
        start_time = Clock::now();
    }   
}

uint64_t Timer::read() const {
    class_initialized();

    if (!running) {
        return accumulated;
    }
    return Clock::now() - start_time;
}

uint32_t Timer::read_us() const {
    class_initialized();

    return read() / (SystemCoreClock / 1000000);
}

uint32_t Timer::read_ms() const {
    class_initialized();

    return (read() / (SystemCoreClock / 1000000)) / 1000;
}

bool Timer::isRunning() const {
    class_initialized();
    
    return running;
}