#include <iostream>
#include <fstream>
#include "common/logging.h"

int main(int argc, char **argv) {
    metable::MetableLog::StartMetableLog("log/test.log",
                                         metable::MetableLogLevel::RLL_INFO, 10, 3);
    std::cout << "Metable Loading." << std::endl;
    metable::MetableLog::ShutDownMetableLog();
    std::fstream file("log/test.log");
    return 0;
}
