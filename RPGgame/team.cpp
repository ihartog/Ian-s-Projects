#include "team.h"
#include <iostream>
#include <cstring>

namespace seneca {

    // Default constructor
    Team::Team() : m_name(""), m_members(nullptr), m_size(0), m_capacity(0) {}

    // Parameterized constructor
    Team::Team(const char* name) : m_name(name), m_members(nullptr), m_size(0), m_capacity(0) {}

    // Destructor
    Team::~Team() {
        if (m_members != nullptr) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;
        }
    }



    // Copy constructor
    Team::Team(const Team& other)
        : m_name(other.m_name), m_size(other.m_size), m_capacity(other.m_capacity) {

        if (m_capacity < m_size) {
            m_capacity = m_size;
        }

        if (m_capacity > 0) {
            m_members = new Character * [m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                if (other.m_members[i] != nullptr) {
                    m_members[i] = other.m_members[i]->clone();
                }
                else {
                    m_members[i] = nullptr;
                }
            }
        }
        else {
            m_members = nullptr;
        }
    }




    // Copy assignment operator
    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            // Clean up existing members
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;

            // Copy new data
            m_name = other.m_name;
            m_size = other.m_size;

            // Ensure m_capacity is at least m_size
            m_capacity = (other.m_capacity < other.m_size) ? other.m_size : other.m_capacity;

            if (m_capacity > 0) {
                m_members = new Character * [m_capacity];
                for (size_t i = 0; i < m_size; ++i) {
                    if (other.m_members[i] != nullptr) {
                        m_members[i] = other.m_members[i]->clone();
                    }
                    else {
                        m_members[i] = nullptr;
                    }
                }
            }
            else {
                m_members = nullptr;
            }
        }
        return *this;
    }

    // Move constructor
    Team::Team(Team&& other) noexcept
        : m_name(std::move(other.m_name)),
        m_members(other.m_members),
        m_size(other.m_size),
        m_capacity(other.m_capacity) {
        other.m_members = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // Move assignment operator
    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            // Clean up current members
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;

            // Transfer ownership of resources
            m_name = std::move(other.m_name);
            m_members = other.m_members;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            // Reset the moved-from object
            other.m_members = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    // Resize the members array
    void Team::resize() {
        size_t newCapacity = (m_capacity == 0) ? 2 : m_capacity * 2;
        Character** newMembers = new Character * [newCapacity];

        // Copy the existing members into the new array
        for (size_t i = 0; i < m_size; ++i) {
            newMembers[i] = m_members[i]; // Simply transfer the pointers, no need to clone or delete
        }

        // Delete the old array (not the characters, just the array itself)
        delete[] m_members;

        // Assign the new array and update the capacity
        m_members = newMembers;
        m_capacity = newCapacity;
    }





    // Add a member to the team
    void Team::addMember(const Character* c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;
            }
        }

        if (m_size >= m_capacity) {
            resize();
        }

        m_members[m_size++] = c->clone();
    }

    // Remove a member by name
    void Team::removeMember(const std::string& name) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == name) {
                delete m_members[i];

                for (size_t j = i; j < m_size - 1; ++j) {
                    m_members[j] = m_members[j + 1];
                }

                m_members[m_size - 1] = nullptr;
                --m_size;
                return;
            }
        }
        std::cout << "Character not found." << std::endl;
    }

    // Access member by index
    Character* Team::operator[](size_t idx) const {
        if (idx < m_size) {
            return m_members[idx];
        }
        return nullptr;
    }

    // Show members of the team
    void Team::showMembers() const {
        if (m_members == nullptr || m_size == 0) {
            std::cout << "No team." << std::endl;
            return;
        }

        std::cout << "[Team] " << m_name << std::endl;
        for (size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl;
        }
    }

}
