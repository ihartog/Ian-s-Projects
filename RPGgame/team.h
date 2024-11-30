#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <string>
#include "character.h"

namespace seneca {
    class Team {
    private:
        std::string m_name;          // Name of the team
        Character** m_members;       // Array of pointers to Character
        size_t m_size;               // Number of members in the team
        size_t m_capacity;           // Current capacity of the array
                
        void resize();

    public:
        // Default constructor
        Team();

        // Parameterized constructor
        Team(const char* name);

        ~Team();                                  // Destructor
        Team(const Team& other);                  // Copy constructor
        Team& operator=(const Team& other);       // Copy assignment
        Team(Team&& other) noexcept;              // Move constructor
        Team& operator=(Team&& other) noexcept;   // Move assignment

        // Public methods
        void addMember(const Character* c);        // Add a new member
        void removeMember(const std::string& name); // Remove a member by name
        Character* operator[](size_t idx) const;   // Access a member by index
        void showMembers() const;                  // Display the members of the team
    };
}
#endif // !SENECA_TEAM_H

