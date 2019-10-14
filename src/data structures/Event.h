#ifndef HUMANITYGENERATIONSIMULATION_EVENT_H
#define HUMANITYGENERATIONSIMULATION_EVENT_H

#include <iostream>
#include <functional>
#include <vector>
#include "enums.h"

using namespace std;

class Human;
class Event {
    string data;
    string person;
    vector<Human *> *friends;
    TriggerType action;
    EventType event_type;
    //function<void(vector<Human *>& friends, TriggerType action)> trigger;
    void call_event();
    void visit_event();

public:
    Event(const string &data, const string &person, vector<Human *> *friends, TriggerType action, EventType event_type);
    string apply();
    bool is_private_event(EventType event_type);
};

#endif //HUMANITYGENERATIONSIMULATION_EVENT_H