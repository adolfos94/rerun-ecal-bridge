#pragma once

// eCAL
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>

// ReRun Loggers
#include "loggers/ImageLogger.hpp"
#include "loggers/Points3dLogger.hpp"

class ReRunLogger {
  public:
    void execute();

  private:
    // eCAL Monitoring
    eCAL::Monitoring::SMonitoring m_monitoring;

    // eCAL Topics
    std::map<std::string, eCAL::Monitoring::STopicMon> m_topics_info;

    // eCAL Subscribers
    std::map<std::string, std::unique_ptr<ISubscriberLogger>> m_subscribers;

    void get_topics(std::map<std::string, eCAL::Monitoring::STopicMon>& topics);

    void update_topics();

    void create_logger(const eCAL::Monitoring::STopicMon& topic);
};