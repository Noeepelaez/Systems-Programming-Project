#pragma once
#include "lib.h"

class Test{
    public: 

    static void generateFiles();
    static void benchmark(size_t n );
    static void benchmarkAll();


private:
    
    class Timer{
        std::chrono::steady_clock::time_point start;
        public:
        Timer() : start(std::chrono::steady_clock::now()) {}
        void reset() {start = std::chrono::steady_clock::now();}
        double elapsed() const{
            return std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
        }
    };

static string pathFor(size_t n);
};