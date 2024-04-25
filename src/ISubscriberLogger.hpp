#pragma once

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>

class ISubscriberLogger {
  public:
    virtual ~ISubscriberLogger() = 0 {};

    void setup() {}

    virtual void log() = 0;

    std::string m_entity_path;
    eCAL::CSubscriber m_subscriber;

  protected:
};