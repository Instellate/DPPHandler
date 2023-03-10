//
// Created by instellate on 3/1/23.
//

#include "TestCommandGroup.h"

void TestCommandGroup::testCmd(const dpp::slashcommand_t &cmd) {
    cmd.reply(fmt::format("This is the test command. Executed by {0}", cmd.command.usr.username),
              [token = cmd.command.token](const dpp::confirmation_callback_t &) {
                  auto client = handler().getClient();

                  client->interaction_followup_create(
                          token, dpp::message("Test followup"), dpp::utility::log_error());
              });
}

void TestCommandGroup::testOptCmd(const dpp::slashcommand_t &cmd) {
    auto userIdPtr = std::get_if<dpp::snowflake>(&cmd.get_parameter("user"));
    if (userIdPtr) {
        auto it = cmd.command.resolved.users.find(*userIdPtr);
        std::string msg = fmt::format("You executed a command with options. You selected user \"{0}\".",
                                      it->second.username);
        cmd.reply({msg});
    } else {
        std::string msg = "You executed a command with options. You didn't select any user.";
        cmd.reply({msg});
    }
}

void TestCommandGroup::testButtonsCmd(const dpp::slashcommand_t &cmd) {
    dpp::component actionRow;
    actionRow.set_type(dpp::cot_action_row)
            .add_component(dpp::component().set_type(dpp::cot_button).set_label("This is a button.").set_id("custom_id"));

    dpp::message msg;
    msg.add_component(actionRow)
            .set_content("Hello. Buttons.");

    cmd.reply(msg, [cmd](const dpp::confirmation_callback_t &response) {
        if (response.is_error()) {
            auto logError = dpp::utility::log_error();
            logError(response);
            return;
        }

        handler().addButtonCollector(
                cmd.command.id, 10,
                [](const dpp::button_click_t &e) {
                    e.reply("Clicked the button.");
                },
                [token = cmd.command.token](const std::vector<dpp::button_click_t> &vec) {
                    handler().getClient()->interaction_followup_create(token, {"Finished collecting!"}, dpp::utility::log_error());
                });
    });
}

void TestCommandGroup::testSelectCmd(const dpp::slashcommand_t &cmd) {
    dpp::message msg;
    dpp::component actionRow;
    actionRow.set_type(dpp::cot_action_row);

    dpp::component selectMenu;
    selectMenu.set_type(dpp::cot_selectmenu);
    selectMenu.add_select_option(dpp::select_option().set_value("hello").set_label("Hello!"))
            .add_select_option(dpp::select_option().set_value("hi").set_label("Hi!"));
    selectMenu.set_max_values(2);
    selectMenu.set_min_values(1);
    actionRow.add_component(selectMenu);
    msg.add_component(actionRow);
    msg.set_content("A fucking select menu!");

    cmd.reply(msg, [cmd](const dpp::confirmation_callback_t &response) {
        if (response.is_error()) {
            auto logError = dpp::utility::log_error();
            logError(response);
            return;
        }

        handler().addSelectMenuCollector(
                cmd.command.id, 5,
                [](const dpp::select_click_t &e) {
                    std::string msg = boost::algorithm::join(e.values, ", ");
                    msg = "You selected values " + msg;
                    e.reply(msg);
                },
                [token = cmd.command.token](const std::vector<dpp::select_click_t> &) {
                    handler().getClient()->interaction_followup_create(token, {"Collecting ended"}, dpp::utility::log_error());
                });
    });
}
