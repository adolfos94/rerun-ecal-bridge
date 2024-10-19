#pragma once

#include <Points3D.pb.h>

#include "ISubscriberLogger.hpp"

class Points3dLogger : public ISubscriberLogger {
  public:
    Points3dLogger(
        const eCAL::Monitoring::STopicMon& topic, std::shared_ptr<rerun::RecordingStream> rec_stream
    )
        : ISubscriberLogger(rec_stream) {
        subscriber = eCAL::protobuf::CSubscriber<pb::rerun::Points3D>(topic.tname);
        subscriber.AddReceiveCallback(std::bind(&Points3dLogger::log, this, std::placeholders::_2));

        setup(topic);
    }

    void log(const eCAL::SReceiveCallbackData* data_) override {
        const std::lock_guard<std::mutex> lock(mutex);

        pb::rerun::Points3D points3dPb;
        points3dPb.ParseFromArray(data_->buf, data_->size);

        std::vector<rerun::Position3D> points3d(points3dPb.points_size());
        for (size_t i = 0; i < points3d.size(); ++i) {
            const auto& point3dPb = points3dPb.points(i);
            points3d[i] = rerun::Position3D(point3dPb.x(), point3dPb.y(), point3dPb.z());
        }

        std::vector<rerun::Color> colors(points3dPb.colors_size());
        for (size_t i = 0; i < colors.size(); ++i) {
            const auto& colorPb = points3dPb.colors(i);
            colors[i] = rerun::Color(
                static_cast<uint8_t>(colorPb.r() * 255.0F),
                static_cast<uint8_t>(colorPb.g() * 255.0F),
                static_cast<uint8_t>(colorPb.b() * 255.0F),
                static_cast<uint8_t>(colorPb.a() * 255.0F)
            );
        }

        std::vector<rerun::Radius> radii(points3dPb.radius_size());
        for (size_t i = 0; i < radii.size(); ++i) {
            radii[i] = points3dPb.radius(i);
        }

        logger()->log(entity_path, rerun::Points3D(points3d).with_colors(colors).with_radii(radii));
    }

  private:
};