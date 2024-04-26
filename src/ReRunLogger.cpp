#include "ReRunLogger.hpp"

using namespace std::chrono_literals;

void ReRunLogger::execute() {
    while (eCAL::Ok()) {
        update_topics();
    }
}

void ReRunLogger::get_topics(std::map<std::string, eCAL::Monitoring::STopicMon>& topics) {
    eCAL::Monitoring::GetMonitoring(m_monitoring);

    for (const auto& topic : m_monitoring.publisher) {
        topics.insert({topic.tname, topic});
    }
}

void ReRunLogger::update_topics() {
    // Get current eCAL topics from monitoring
    std::map<std::string, eCAL::Monitoring::STopicMon> topics_info;
    get_topics(topics_info);

    // Update eCAL topics
    for (const auto& [topic_name, topic] : topics_info) {
        // Topic exist or isn't a valid topic
        if (m_topics_info.find(topic_name) != m_topics_info.end()) {
            continue;
        }

        // New topic
        m_topics_info.insert({topic_name, topic});

        create_logger(topic);
    }

    // Remove unused eCAL topics
    std::erase_if(m_topics_info, [&](auto& kv) {
        return topics_info.find(kv.first) == topics_info.end();
    });
}

void ReRunLogger::create_logger(const eCAL::Monitoring::STopicMon& topic) {
    const std::string message_type = topic.tdatatype.name;
    if (message_type == "pb.rerun.Image") {
        m_subscribers.insert({topic.tname, std::unique_ptr<ImageLogger>(new ImageLogger(topic))});
    }
}