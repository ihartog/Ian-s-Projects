#include "guild.h"
#include <iostream>

namespace seneca {
    // Default constructor
    Guild::Guild() : m_name(""), m_members(nullptr), m_size(0), m_capacity(0) {}

    // Parameterized constructor
    Guild::Guild(const char* name) : m_name(name), m_members(nullptr), m_size(0), m_capacity(0) {}

    // Destructor
    Guild::~Guild() {
        delete[] m_members;
        m_members = nullptr;
    }


    // Copy constructor
    Guild::Guild(const Guild& other)
        : m_name(other.m_name), m_size(other.m_size), m_capacity(other.m_capacity) {

        if (m_capacity < m_size) {
            m_capacity = m_size;
        }

        m_members = new Character * [m_capacity];

        for (size_t i = 0; i < m_size; ++i) {
            m_members[i] = other.m_members[i];
        }
    }


    // Copy assignment operator 
    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            delete[] m_members;

            // Copy new data
            m_name = other.m_name;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            if (m_capacity > 0) {
                m_members = new Character * [m_capacity];
                for (size_t i = 0; i < m_size; ++i) {
                    m_members[i] = other.m_members[i];
                }
            }
            else {
                m_members = nullptr;
            }
        }
        return *this;
    }




    // Move constructor
    Guild::Guild(Guild&& other) noexcept
        : m_name(std::move(other.m_name)),
        m_members(other.m_members),
        m_size(other.m_size),
        m_capacity(other.m_capacity)
    {
        other.m_members = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // Move assignment operator
    Guild& Guild::operator=(Guild&& other) noexcept {
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
    void Guild::resize() {
        size_t newCapacity = (m_capacity == 0) ? 2 : m_capacity * 2;
        Character** newMembers = new Character * [newCapacity];

        for (size_t i = 0; i < m_size; ++i) {
            newMembers[i] = m_members[i];
        }

        delete[] m_members;
        m_members = newMembers;
        m_capacity = newCapacity;
    }

    // Add a member to the guild and give them 300 extra health points
    void Guild::addMember(Character* c) {
        // Check if character is already in the guild
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;
            }
        }

        // Resize if necessary
        if (m_size == m_capacity) {
            resize();
        }

        // Increase max health by 300
        c->setHealthMax(c->getHealthMax() + 300);

        // Add the new character
        m_members[m_size++] = c;
    }

    // Remove a member by name and reduce their health by 300 points
    void Guild::removeMember(const std::string& name) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == name) {
                // Decrease max health by 300
                m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);

                // Shift the remaining elements
                for (size_t j = i; j < m_size - 1; ++j) {
                    m_members[j] = m_members[j + 1];
                }
                --m_size;
                return;
            }
        }
    }

    // Access member by index
    Character* Guild::operator[](size_t idx) const {
        if (idx < m_size) {
            return m_members[idx];
        }
        return nullptr;
    }

    // Show members of the guild
    void Guild::showMembers() const {
        // Check if the guild is empty (no members) but ensure the guild name is printed if it exists
        if (m_size == 0 || m_members == nullptr) {
            if (m_name.empty()) {
                std::cout << "No guild." << std::endl;
            }
            else {
                std::cout << "[Guild] " << m_name << std::endl;
            }
            return;
        }

        // Print the guild name
        std::cout << "[Guild] " << m_name << std::endl;

        // Print each member in the guild
        for (size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl;
        }
    }
}
