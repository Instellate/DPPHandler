//
// Created by instellate on 3/1/23.
//

#include "EnvReader.h"
#include <dpp_handler/Handler.h>
#include <filesystem>

using namespace DPPHandler;
namespace fs = std::filesystem;

int main() {
    EnvReader secrets;
    secrets.parseFile(fs::canonical("../../test/src/.env").string()); // Works ¯\_(ツ)_/¯

    handler().createClient(secrets["BOT_TOKEN"]);
    handler().start();

    return 0;
}