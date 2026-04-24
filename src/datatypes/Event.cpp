#include "Event.h"

Event::Event(
    int id,
    std::string title,
    std::string summary,
    std::string report_date,
    int detail_level,
    int decision_relevance,
    std::string information_density,
    std::string uncertainty_level,
    std::string source_url,
    int category_id,
    int stakeholder_level_id,
    int knowledge_status_id,
    int pandemic_phase_id,
    int source_id
) {

    this->_id = id;
    this->_title = title;
    this->_summary = summary;
    this->_report_date = report_date;
    this->_detail_level = detail_level;
    this->_decision_relevance = decision_relevance;
    this->_information_density = information_density;
    this->_uncertainty_level = uncertainty_level;
    this->_source_url = source_url;
    this->_category_id = category_id;
    this->_stakeholder_level_id = stakeholder_level_id;
    this->_knowledge_status_id = knowledge_status_id;
    this->_pandemic_phase_id = pandemic_phase_id;
    this->_source_id = source_id;

}


std::string Event::toJson() {

    return
        "{\"id\": \"" + std::to_string( this->_id ) + "\"," +
        "\"title\": \"" + this->_title + "\"," +
        "\"summary\": \"" + this->_summary + "\"," +
        "\"report_date\": \"" + this->_report_date + "\"," +
        "\"detail_level\": \"" + std::to_string( this->_detail_level ) + "\"," +
        "\"decision_relevance\": \"" + std::to_string( this->_decision_relevance ) + "\"," +
        "\"information_density\": \"" + this->_information_density + "\"," +
        "\"uncertainty_level\": \"" + this->_uncertainty_level + "\"," +
        "\"source_url\": \"" + this->_source_url + "\"," +
        "\"category_id\": \"" + std::to_string( this->_category_id ) + "\"," +
        "\"stakeholder_level_id\": \"" + std::to_string( this->_stakeholder_level_id ) + "\"," +
        "\"knowledge_status_id\": \"" + std::to_string( this->_knowledge_status_id ) + "\"," +
        "\"pandemic_phase_id\": \"" + std::to_string( this->_pandemic_phase_id ) + "\"," +
        "\"source_id\": \"" + std::to_string( this->_source_id ) + "\"}";

}