#pragma once

#include <Image.pb.h>

#include "ISubscriberLogger.hpp"

class ImageLogger : public ISubscriberLogger {
  public:
    ImageLogger(
        const eCAL::Monitoring::STopicMon& topic, std::shared_ptr<rerun::RecordingStream> rec_stream
    )
        : ISubscriberLogger(rec_stream) {
        subscriber = eCAL::protobuf::CSubscriber<pb::rerun::Image>(topic.tname);
        subscriber.AddReceiveCallback(std::bind(&ImageLogger::log, this, std::placeholders::_2));

        setup(topic);
    }

    void log(const eCAL::SReceiveCallbackData* data_) override {
        const std::lock_guard<std::mutex> lock(mutex);

        pb::rerun::Image imagePb;
        imagePb.ParseFromArray(data_->buf, data_->size);
    }

  private:
};