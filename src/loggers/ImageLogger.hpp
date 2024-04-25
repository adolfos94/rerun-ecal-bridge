#pragma once

#include <Image.pb.h>

#include "ISubscriberLogger.hpp"

class ImageLogger : public ISubscriberLogger {
  public:
    ImageLogger(const eCAL::Monitoring::STopicMon& topic) {
        m_subscriber = eCAL::protobuf::CSubscriber<pb::rerun::Image>(topic.tname);
    }

    void log() override {}

  private:
};