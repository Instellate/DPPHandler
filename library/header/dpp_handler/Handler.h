//
// Created by instellate on 3/1/23.
//

#pragma once

#include "Option.h"
#include "util/ButtonCollector.h"
#include <dpp/cluster.h>
#include <memory>
#include <vector>

namespace DPPHandler {
    using clientPtr = std::shared_ptr<dpp::cluster>;
    using methodFunc = std::function<void(const dpp::slashcommand_t &)>;

    class PartialCommandBase {
    public:
        virtual void registerCommand() noexcept = 0;
    };

    class Handler {
    private:
        std::vector<std::shared_ptr<PartialCommandBase>> commandInstance;
        std::unordered_map<std::string, methodFunc> commandMap;
        std::vector<dpp::slashcommand> unregisteredCommands;
        clientPtr client = nullptr;
        util::ButtonCollector buttonCollector{};

    public:
        void createClient(const std::string &token) noexcept;

        int registerCommand(const std::shared_ptr<PartialCommandBase> &instance) noexcept;

        void registerCommand(const std::string &name, const methodFunc &method);

        void addCommandToQueue(const dpp::slashcommand &cmd);

        void addCollector(const dpp::snowflake &id, int expiringSeconds, const std::function<void(const dpp::button_click_t &)> &collectFunc,
                          const std::function<void(const std::vector<dpp::button_click_t> &)> &collectExpireFunc);

        void start();

        clientPtr getClient() const noexcept;
    };

    Handler &handler() noexcept;
}// namespace DPPHandler