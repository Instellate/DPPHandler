//
// Created by instellate on 2023-03-04.
//

#pragma once
#include "ExpirationThreadHandler.h"
#include <dpp/dispatcher.h>
#include <unordered_map>
#include <vector>

namespace DPPHandler::util {
    struct SelectMenuData {
        timePoint expiration;
        std::function<void(const dpp::select_click_t &)> collect;
        std::function<void(const std::vector<dpp::select_click_t> &)> collectEnd;
        std::vector<dpp::select_click_t> eventsCollected;
    };

    class SelectMenuCollector {
        std::mutex mtx;

        void loop();

    public:
        std::unordered_map<dpp::snowflake, SelectMenuData> selectMenus;

        explicit SelectMenuCollector(ExpirationThreadHandler &handler) {
            handler.addFunctionToLoop(std::bind(&SelectMenuCollector::loop, this));// NOLINT(modernize-avoid-bind) Too op.
        }

        void onSelectMenuClick(const dpp::select_click_t &e);
    };
}// namespace DPPHandler::util
