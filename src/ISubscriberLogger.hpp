#pragma once

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>

class ISubscriberLogger {
  public:
    virtual void log() = 0;

  protected:
    eCAL::CSubscriber m_subscriber;
};