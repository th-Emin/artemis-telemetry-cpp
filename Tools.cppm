// This code write for Principles of Programming Languages Homework 1
// th-Emin
export module Tools;

import std;

export int random(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}