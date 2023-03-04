//
// Created by instellate on 3/1/23.
//

#include "dpp_handler/Handler.h"

int DPPHandler::Handler::registerCommand(const std::shared_ptr<PartialCommandBase> &instance) noexcept {
    this->commandInstance.emplace_back(instance);// I don't know why I have this. But meh.
    instance->registerCommand();
    return 0;
}

DPPHandler::clientPtr DPPHandler::Handler::getClient() const noexcept {
    return this->client;
}

void DPPHandler::Handler::createClient(const std::string &token) noexcept {
    this->client = std::make_shared<dpp::cluster>(token);
    this->client->on_log(dpp::utility::cout_logger());
}

void DPPHandler::Handler::registerCommand(const std::string &name, const methodFunc &method) {
    this->commandMap.emplace(name, method);
}

void DPPHandler::Handler::start() {
    client->on_slashcommand([this](const dpp::slashcommand_t &event) {
        std::string commandName = event.command.get_command_name();
        auto it = this->commandMap.find(commandName);
        if (it == commandMap.end()) {
            dpp::message msg;
            msg.set_content("This command shouldn't exist.");
            msg.set_flags(dpp::message_flags::m_ephemeral);
            event.reply(msg);
            return;
        }
        try {
            it->second(event);
        } catch (const std::exception &e) {
            std::stringstream ss;
            ss << "Command " << commandName << " has thrown a exception. Error msg:\n\t " << e.what();
            client->log(dpp::ll_info, ss.str());
            dpp::message msg;
            msg.set_content("This command have thrown a exception.");
            msg.set_flags(dpp::message_flags::m_ephemeral);
            event.reply(msg);
            return;
        }
    });

    client->on_ready([this](const dpp::ready_t &) {
        this->client->global_commands_get([this](const dpp::confirmation_callback_t &confirmation) {
            if (confirmation.is_error()) {
                auto logError = dpp::utility::log_error();
                logError(confirmation);
            }

            bool needToUpdate = false;
            auto slashCommands = confirmation.get<dpp::slashcommand_map>();
            // Going to implement comparison to see if a slash command update is needed.

            this->client->global_bulk_command_create(this->unregisteredCommands, [this](const dpp::confirmation_callback_t &confirmation) {
                if (confirmation.is_error()) {
                    auto logError = dpp::utility::log_error();
                    logError(confirmation);
                } else {
                    this->unregisteredCommands.clear();
                }
            });
        });
    });

    client->on_button_click([&bc = this->buttonCollector](const dpp::button_click_t &e) {
        bc.onButtonClick(e);
    });

    client->on_select_click([&slc = this->selectMenuCollector](const dpp::select_click_t &e) {
        slc.onSelectMenuClick(e);
    });

    client->start(false);
}

void DPPHandler::Handler::addCommandToQueue(const dpp::slashcommand &cmd) {
    this->unregisteredCommands.emplace_back(cmd);
}

void DPPHandler::Handler::addButtonCollector(const dpp::snowflake &id, int expiringSeconds, const std::function<void(const dpp::button_click_t &)> &collectFunc, const std::function<void(const std::vector<dpp::button_click_t> &)> &collectExpireFunc) {
    util::ButtonData data;
    data.collect = collectFunc;
    data.collectEnd = collectExpireFunc;
    data.expire = (std::chrono::system_clock::now() + std::chrono::seconds(expiringSeconds));

    buttonCollector.buttons.emplace(id, data);
}
void DPPHandler::Handler::addSelectMenuCollector(const dpp::snowflake &id, int expiringSeconds, const std::function<void(const dpp::select_click_t &)> &collectFunc, const std::function<void(const std::vector<dpp::select_click_t> &)> &collectExpireFunc) {
    util::SelectMenuData data;
    data.collect = collectFunc;
    data.collectEnd = collectExpireFunc;
    data.expiration = (std::chrono::system_clock::now() + std::chrono::seconds(expiringSeconds));

    selectMenuCollector.selectMenus.emplace(id, data);
}

namespace DPPHandler {
    Handler &handler() noexcept {
        static Handler mainHandler;

        return mainHandler;
    }
}// namespace DPPHandler