#pragma once

#include <thread>

#include <ecal/ecal.h>
#include <rerun.hpp>

constexpr char NODE_NAME[] = "ReRun eCAL Bridge";

class ReRunLogger {
  public:
    ReRunLogger();

    void execute();

  private:
    // ReRun Stream
    const rerun::RecordingStream m_rec{NODE_NAME};

    // eCAL Monitoring
    eCAL::Monitoring::SMonitoring m_monitoring;

    // eCAL Topics
    std::map<std::string, eCAL::Monitoring::STopicMon> m_topics_info;

    void get_topics(std::map<std::string, eCAL::Monitoring::STopicMon>& topics);

    void update_topics();
};