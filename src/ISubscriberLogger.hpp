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

    inline static rerun::RecordingStream& logger() {
        static bool connect = true;

        if (connect) {
            connect = m_rec_stream.spawn() != rerun::Error::ok();
        }
        return m_rec_stream;
    }

    virtual void log(const eCAL::SReceiveCallbackData* data_) = 0;

  protected:
    std::mutex mutex;

    std::string entity_path;
    eCAL::CSubscriber subscriber;

  private:
    inline static rerun::RecordingStream m_rec_stream = rerun::RecordingStream(NODE_NAME);
};