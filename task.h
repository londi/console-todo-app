#pragma once
#include <iostream>
#include <ostream>
#include <string>


/**
 * Task struct
 */
struct Task {
    uint8_t m_id;
    std::string m_name, m_state;

    Task(const uint8_t id, const std::string& name, const std::string& state)
        : m_id(id),
          m_name(name),
          m_state(state) {
    }

    friend std::ostream& operator<<(std::ostream& os, const Task& t) {
        return os << "(" << static_cast<unsigned>(t.m_id) << ", " << t.m_name << ", " << t.m_state << ")";
    }
};
