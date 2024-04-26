#pragma once

// ReRun
#include <rerun.hpp>

// eCAL
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>

constexpr char NODE_NAME[] = "ReRun eCAL Bridge";

class ISubscriberLogger {
  public:
    virtual ~ISubscriberLogger() = 0 {};

    void setup(const eCAL::Monitoring::STopicMon& topic) {
        entity_path = topic.uname + "/" + topic.tname;
    }

    std::shared_ptr<rerun::RecordingStream> logger() {
        if (!m_rec_stream_ptr) {
            m_rec_stream_ptr = std::make_shared<rerun::RecordingStream>(NODE_NAME);
            m_rec_stream_ptr->spawn();
        }

        return m_rec_stream_ptr;
    }

    virtual void log(const eCAL::SReceiveCallbackData* data_) = 0;

  protected:
    std::string entity_path;
    eCAL::CSubscriber subscriber;

  private:
    std::shared_ptr<rerun::RecordingStream> m_rec_stream_ptr;
};