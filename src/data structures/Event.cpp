#include "Event.h"

Event::Event(const string &data, const string &person, vector<Human *> *friends, TriggerType action, EventType event_type) :
data(data), person(person) {
    this->friends = friends;
    this->action = action;
    this->event_type = event_type;
}

string Event::apply() {
    string event_info;
    event_info = person + ": " + data;
    switch (action) {
        case CALL:
            call_event();
            break;

        case VISIT:
            visit_event();
            break;
    }
    if (is_private_event(event_type)) {
        return event_info;
    }
    cout << event_info << endl;
    return "**Private Event**";
}

void Event::call_event() {
    for (size_t i = 0; i < friends->size(); i++) {
        //string name = (*friends)[i]->get_name();
    }
}

void Event::visit_event() {

}

bool Event::is_private_event(EventType event_type) {
    bool is_private = false;
    switch (event_type) {
        case EventType::BIRTHDAY:
        case EventType::DEATH:
        case EventType::KID_BORN:
        case EventType::MARRIAGE:
            is_private = false;
            break;

        case EventType::MEETS:
        case EventType::FRIENDSHIP_STARTED:
        case EventType::THOUGHTS:
        case EventType::CALL:
            is_private = true;
            break;
    }
    return is_private;
}
