//
// Created by instellate on 3/1/23.
//

#pragma once

#include <utility>

#include "Handler.h"

#define COMMAND_LIST_BEGIN                     \
    void registerCommand() noexcept override { \
        if (T == 0) {// This is here to guarantee that the type gets registered.
#define COMMAND_ADD(string, description, method, ...) \
    addCommand(string, method);                       \
    addCommandToRegistrationProcess(string, description, {__VA_ARGS__})
#define COMMAND_LIST_END \
    }                    \
    return;              \
    }

namespace DPPHandler {
    template<typename type>
    class CommandBase : public PartialCommandBase {
    public:
        const static inline int T = handler().registerCommand(std::make_shared<type>());

    protected:
        template<typename FUNCTION>
        static void addCommand(std::string &&str, FUNCTION &&function) {
            handler().registerCommand(str, function);
        }

        static void addCommandToRegistrationProcess(std::string &&name, std::string &&description, std::vector<Option> &&options) {
            dpp::slashcommand command(name, description, dpp::snowflake());

            for (auto &option: options) {
                dpp::command_option commandOption(option.type, option.name, option.description, option.required);
                command.add_option(commandOption);
            }

            handler().addCommandToQueue(command);
        }
    };
}// namespace DPPHandler