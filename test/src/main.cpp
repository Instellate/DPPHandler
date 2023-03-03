//
// Created by instellate on 3/1/23.
//

#include <dpp_handler/Handler.h>

using namespace DPPHandler;

int main() {
    handler().createClient("token");
    handler().start();

    return 0;
}