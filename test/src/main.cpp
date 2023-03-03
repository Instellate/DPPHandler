//
// Created by instellate on 3/1/23.
//

#include "envReader.h"
#include <dpp_handler/Handler.h>
#include <filesystem>

using namespace DPPHandler;
namespace fs = std::filesystem;

int main() {
    envReader secrets;
    secrets.parseFile(fs::canonical("../../test/src/.env").string()); // Works ¯\_(ツ)_/¯

    handler().createClient(secrets.secrets["BOT_TOKEN"]);
    handler().start();

    return 0;
}