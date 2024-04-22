#pragma once

#include <rerun.hpp>

constexpr char NODE_NAME[] = "ReRun eCAL Bridge";

class ReRunLogger {
  public:
    ReRunLogger();

    void Execute();

  private:
    const rerun::RecordingStream m_rec{NODE_NAME};
};