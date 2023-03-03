//
// Created by instellate on 3/3/23.
//

#include "dpp_handler/util/ExpirationThreadHandler.h"

using namespace std::chrono_literals;

void DPPHandler::util::ExpirationThreadHandler::addFunctionToLoop(const std::function<void()> &function) {
    functions.emplace_back(function);
}

void DPPHandler::util::ExpirationThreadHandler::loop() {
    while (true) {
        if (stop) break;

        for (const auto &function: functions)
            function();

        std::this_thread::sleep_for(500ms);
    }
}
