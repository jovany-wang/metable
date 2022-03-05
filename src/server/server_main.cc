#include <fstream>
#include <iostream>

#include "common/logging.h"
#include "metable_server.h"

using namespace metable;

int main(int argc, char **argv) {
    metable::MetableLog::StartMetableLog("log/test.log",
                                         metable::MetableLogLevel::RLL_INFO, 10, 3);
    std::cout << "Metable Loading." << std::endl;
    metable::MetableLog::ShutDownMetableLog();
    std::fstream file("log/test.log");

    MetableServer metable_server;
    metable_server.Loop();

    return 0;
}
