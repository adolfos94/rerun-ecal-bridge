#include "ReRunLogger.hpp"

ReRunLogger::ReRunLogger() {
    _rec.spawn().exit_on_failure();
}

void ReRunLogger::Execute() {}