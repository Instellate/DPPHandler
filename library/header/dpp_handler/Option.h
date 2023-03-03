//
// Created by instellate on 3/2/23.
//

#pragma once

#include <dpp/appcommand.h>
#include <string>

namespace DPPHandler {
    class Option {
    public:
        std::string name;
        std::string description;
        dpp::command_option_type type;
        bool required;

        Option(std::string optionName, std::string optionDescription, dpp::command_option_type optionType, bool optionRequired = false)
            : name(std::move(optionName)), description(std::move(optionDescription)), type(optionType), required(optionRequired) {}
    };
}// namespace DPPHandler