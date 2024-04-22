#include <ecal/ecal.h>

#include "ReRunLogger.hpp"

int main() {
    eCAL::Initialize(0, nullptr, NODE_NAME, eCAL::Init::Monitoring);

    ReRunLogger node;
    node.Execute();

    return eCAL::Finalize();
}