//
// Created by instellate on 3/2/23.
//

#pragma once
#include "ExpirationThreadHandler.h"
#include <dpp/dispatcher.h>
#include <iostream>

namespace DPPHandler::util {
    using timePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;

    struct ButtonData {
        timePoint expire;
        std::function<void(const dpp::button_click_t &)> collect;
        std::function<void(const std::vector<dpp::button_click_t> &)> collectEnd;
        std::vector<dpp::button_click_t> eventsCollected;
    };

    class ButtonCollector {
    private:
        std::mutex mtx;
        void expirationCheckLoop();

    public:
        explicit ButtonCollector(ExpirationThreadHandler &handler) {
            handler.addFunctionToLoop(std::bind(&ButtonCollector::expirationCheckLoop, this));// NOLINT(modernize-avoid-bind)
        }

        std::unordered_map<dpp::snowflake, ButtonData> buttons;

        void onButtonClick(const dpp::button_click_t &e);
    };
}// namespace DPPHandler::util
