//
// Created by instellate on 3/2/23.
//

#pragma once
#include "ExpirationThreadHandler.h"
#include <dpp/dispatcher.h>
#include <iostream>

namespace DPPHandler::util {
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
            handler.addFunctionToLoop(std::bind(&ButtonCollector::expirationCheckLoop, this));// NOLINT(modernize-avoid-bind) I feel like a lambda would be a bit op for this.
        }

        std::unordered_map<dpp::snowflake, ButtonData> buttons;

        void onButtonClick(const dpp::button_click_t &e);
    };
}// namespace DPPHandler::util
