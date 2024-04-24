// eCAL
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

// Protobuf
#include <Image.pb.h>

using namespace std::chrono_literals;

constexpr char NODE_NAME[] = "ReRun eCAL Bridge-Sample";

void publish_image() {

    static eCAL::protobuf::CPublisher<pb::rerun::Image> image_pub("ImagePub");

    // Create a synthetic image.
    const int HEIGHT = 200;
    const int WIDTH = 300;
    const int CHANNELS = 3;
    std::vector<uint8_t> data(WIDTH * HEIGHT * CHANNELS, 0);
    for (size_t i = 0; i < data.size(); i += 3) {
        data[i] = 255;
    }
    for (size_t y = 50; y < 150; ++y) {
        for (size_t x = 50; x < 150; ++x) {
            data[(y * WIDTH + x) * 3 + 0] = 0;
            data[(y * WIDTH + x) * 3 + 1] = 255;
            data[(y * WIDTH + x) * 3 + 2] = 0;
        }
    }

    pb::rerun::Image image;
    image.set_width(WIDTH);
    image.set_height(HEIGHT);
    image.set_channels(CHANNELS);
    image.set_data(data.data(), data.size());

    image_pub.Send(image);
}

int main() {
    eCAL::Initialize(0, nullptr, NODE_NAME);

    while (eCAL::Ok())
    {
        publish_image();
        std::this_thread::sleep_for(0.1s);
    }

    return eCAL::Finalize();
}