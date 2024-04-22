#include <ecal/ecal.h>

#include "ReRunLogger.hpp"

int main() {
    eCAL::Initialize(0, nullptr, NODE_NAME, eCAL::Init::All);

    ReRunLogger node;
    node.execute();

    return eCAL::Finalize();
}