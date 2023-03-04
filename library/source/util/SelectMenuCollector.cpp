//
// Created by instellate on 2023-03-04.
//

#include "dpp_handler/util/SelectMenuCollector.h"

void DPPHandler::util::SelectMenuCollector::loop() {
    std::lock_guard guard(mtx);

    auto it = selectMenus.begin();
    while(it != selectMenus.end()) {
        if(it->second.expiration < std::chrono::system_clock::now()) {
            it->second.collectEnd(it->second.eventsCollected);
            selectMenus.erase(it++);
        } else ++it;
    }
}

void DPPHandler::util::SelectMenuCollector::onSelectMenuClick(const dpp::select_click_t &e) {
    auto it = selectMenus.find(e.command.msg.interaction.id);
    if(it != selectMenus.end()) {
        it->second.collect(e);
        it->second.eventsCollected.emplace_back(e);
    }
}
