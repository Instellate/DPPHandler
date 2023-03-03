//
// Created by instellate on 3/1/23.
//

#pragma once

#include <dpp_handler/CommandBase.h>
#include <fmt/format.h>

using namespace DPPHandler;

class TestCommandGroup : public CommandBase<TestCommandGroup> {
    COMMAND_LIST_BEGIN
    COMMAND_ADD("test", "A test command", TestCommandGroup::testCmd);
    COMMAND_ADD("test_opt", "A test command with options", TestCommandGroup::testOptCmd,
                {"user", "The user selected", dpp::co_user});
    COMMAND_ADD("test_button", "A test command for buttons.", TestCommandGroup::testButtonsCmd);
    COMMAND_LIST_END

    static void testCmd(const dpp::slashcommand_t &cmd);

    static void testOptCmd(const dpp::slashcommand_t &cmd);

    static void testButtonsCmd(const dpp::slashcommand_t &cmd);
};
