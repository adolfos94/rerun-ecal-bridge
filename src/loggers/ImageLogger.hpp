#pragma once

#include <Image.pb.h>

#include "ISubscriberLogger.hpp"

class ImageLogger : public ISubscriberLogger {
  public:
    ImageLogger(const eCAL::Monitoring::STopicMon& topic) {
        subscriber = eCAL::protobuf::CSubscriber<pb::rerun::Image>(topic.tname);
        subscriber.AddReceiveCallback(std::bind(&ImageLogger::log, this, std::placeholders::_2));

        setup(topic);
    }

    void log(const eCAL::SReceiveCallbackData* data_) override {
        pb::rerun::Image image;
        image.ParseFromArray(data_->buf, data_->size);

        logger()->log(
            entity_path,
            rerun::Image(
                {image.height(), image.width(), image.channels()},
                (uint8_t*)image.data().data()
            )
        );
    }

  private:
};