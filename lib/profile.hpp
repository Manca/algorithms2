#pragma once
//
//  profile.hpp - A singelton profile class for performance measurements
//
//  Algorithms: Design and Analysis, Part 2
//
//  Created by Nenad Mancevic on 04/19/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
#define PROFILE(name) tools::Profile::getInstance()->start(name);
#define PROFILE_STOP() tools::Profile::getInstance()->stop();

#include <chrono>
#include <iostream>
#include <string>

namespace tools
{
    class Profile
    {
        typedef std::chrono::steady_clock::time_point t_Point;
    public:
        static Profile* getInstance()
        {
            if (_instance == nullptr)
                _instance = new Profile();
                
            return _instance;
        }

        void start(const std::string& name)
        {
            _profileName = name;
            _start = std::chrono::steady_clock::now();
        }
        void stop()
        {
            _end = std::chrono::steady_clock::now();
            _duration = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();

            std::cout << "[PROFILE] " << _profileName << " took " << _duration << "ms" << " to run." << std::endl;
        }

        long long elapsed()
        {
            return _duration;
        }

    private:
        static Profile* _instance;
        t_Point         _start, _end;
        long long       _duration;
        std::string     _profileName;

        Profile()
        {            
        }
        ~Profile()
        {

        }
    };
    Profile* Profile::_instance = nullptr;
    /*
    void testProfile()
    {
        Profile::getInstance()->start("Sleep 430");
        Sleep(430);
        Profile::getInstance()->stop();
        assert(Profile::getInstance()->elapsed() == 430);

        Profile::getInstance()->start("Sleep 1000");
        Sleep(1000);
        Profile::getInstance()->stop();
        Sleep(3000);
        assert(Profile::getInstance()->elapsed() == 1000);
    }
    */
} // namespace
