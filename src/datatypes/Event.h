#pragma once
#include <string>

class Event {

    public:

        Event(
            int id = 0,
            std::string title = "",
            std::string summary = "",
            std::string report_date = "",
            int detail_level = 0,
            int decision_relevance = 0,
            std::string information_density = "",
            std::string uncertainty_level = "",
            int stakeholder_level_id = 0,
            int category_id = 0,
            int pandemic_phase_id = 0,
            int source_id = 0,
            int knowledge_status_id = 0,
            std::string source_url = ""
        );

        std::string toJson();

        int getId() { return this->_id; }

    private:

        int _id;
        std::string _title;
        std::string _summary;
        std::string _report_date;
        int _detail_level;
        int _decision_relevance;
        std::string _information_density;
        std::string _uncertainty_level;
        std::string _source_url;
        int _category_id;
        int _stakeholder_level_id;
        int _knowledge_status_id;
        int _pandemic_phase_id;
        int _source_id;

};