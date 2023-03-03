//
// Created by instellate on 3/3/23.
//

#pragma once

#include <functional>
#include <thread>
#include <vector>

namespace DPPHandler::util {
    class ExpirationThreadHandler {
        std::vector<std::function<void()>> functions;
        std::thread loopThread;
        std::atomic<bool> stop = false;

        void loop();

    public:
        void addFunctionToLoop(const std::function<void()> &function);

        ExpirationThreadHandler() {
            loopThread = std::thread(&ExpirationThreadHandler::loop, this);
        }

        ~ExpirationThreadHandler() {
            stop = true;
            loopThread.join();
        }
    };
}// namespace DPPHandler::util