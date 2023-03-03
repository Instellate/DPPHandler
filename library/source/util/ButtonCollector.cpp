//
// Created by instellate on 3/2/23.
//

#include "dpp_handler/util/ButtonCollector.h"

using namespace std::chrono_literals;

void DPPHandler::util::ButtonCollector::expirationCheckLoop() {
    while (true) {
        std::lock_guard guard(mtx);
        if (stop) break;

        auto it = buttons.begin();
        while (it != buttons.end()) {
            if (it->second.expire < std::chrono::system_clock::now()) {
                it->second.collectEnd(it->second.eventsCollected);
                buttons.erase(it++);
            } else
                ++it;
        }

        std::this_thread::sleep_for(500ms);
    }
}

void DPPHandler::util::ButtonCollector::onButtonClick(const dpp::button_click_t &e) {
    auto it = buttons.find(e.command.message_id);
    if (it == buttons.end()) return;
    it->second.collect(e);
    it->second.eventsCollected.emplace_back(e);
}
