#include "ReRunLogger.hpp"

using namespace std::chrono_literals;

ReRunLogger::ReRunLogger() {
    m_rec.spawn().exit_on_failure();

    eCAL::Monitoring::GetMonitoring(m_monitoring);
}

void ReRunLogger::execute() {
    while (eCAL::Ok()) {
        // Check for new topics every 0.1s

        update_topics();

        std::this_thread::sleep_for(0.1s);
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
        // Topic exist
        if (m_topics_info.find(topic_name) != m_topics_info.end()) {
            continue;
        }

        // New topic
        m_topics_info.insert({topic_name, topic});
    }

    // Remove unused eCAL topics
    std::erase_if(m_topics_info, [&](auto& kv) {
        return topics_info.find(kv.first) == topics_info.end();
    });
}