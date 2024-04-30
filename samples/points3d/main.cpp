#include <random>

// eCAL
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

// Protobuf
#include <Points3D.pb.h>

using namespace std::chrono_literals;

std::default_random_engine gen;

void publish_points3d() {
    static eCAL::protobuf::CPublisher<pb::rerun::Points3D> points3d_pub("Points3DPub");

    std::uniform_real_distribution<float> dist_pos(-5.0f, 5.0f);
    std::uniform_real_distribution<float> dist_color(0.0f, 1.0f);
    std::uniform_real_distribution<float> dist_radius(0.1f, 1.0f);

    pb::rerun::Points3D points3d;

    for (size_t i = 0; i < 10; ++i) {
        auto point3 = points3d.mutable_points()->Add();
        point3->set_x(dist_pos(gen));
        point3->set_y(dist_pos(gen));
        point3->set_z(dist_pos(gen));

        auto color = points3d.mutable_colors()->Add();
        color->set_r(dist_color(gen));
        color->set_g(dist_color(gen));
        color->set_b(dist_color(gen));
        color->set_a(dist_color(gen));

        points3d.mutable_radius()->Add(dist_radius(gen));
    }

    points3d_pub.Send(points3d);
}

int main() {
    eCAL::Initialize(0, nullptr, "Points3DSample");

    while (eCAL::Ok()) {
        publish_points3d();
        std::this_thread::sleep_for(0.1s);
    }

    return eCAL::Finalize();
}