//
// Created by instellate on 3/2/23.
//

#pragma once
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
        std::atomic<bool> stop = false;
        std::mutex mtx;
        // This is going to be made into its own class so select menu, modal etc. uses the same thread for the expiring loop.
        std::thread expiringThread;
        void expirationCheckLoop();

    public:
        ButtonCollector() {
            expiringThread = std::thread(&ButtonCollector::expirationCheckLoop, this);
        }

        ~ButtonCollector() {
            stop = true;
            expiringThread.join();
        }

        std::unordered_map<dpp::snowflake, ButtonData> buttons;

        void onButtonClick(const dpp::button_click_t &e);
    };
}// namespace DPPHandler::util
