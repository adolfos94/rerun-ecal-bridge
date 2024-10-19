#pragma once

// ReRun
#include <rerun.hpp>

// eCAL
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>

constexpr char NODE_NAME[] = "ReRun eCAL Bridge";

class ISubscriberLogger {
  public:
    ISubscriberLogger(std::shared_ptr<rerun::RecordingStream> rec_stream)
        : m_rec_stream(rec_stream){};

    virtual ~ISubscriberLogger() = 0 {};

    void setup(const eCAL::Monitoring::STopicMon& topic) {
        entity_path = topic.uname + "/" + topic.tname;
    }

    inline std::shared_ptr<rerun::RecordingStream> logger() {
        return m_rec_stream;
    }

    virtual void log(const eCAL::SReceiveCallbackData* data_) = 0;

  protected:
    std::mutex mutex;

    std::string entity_path;
    eCAL::CSubscriber subscriber;

    std::shared_ptr<rerun::RecordingStream> m_rec_stream;
};