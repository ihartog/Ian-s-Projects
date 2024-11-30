#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <string>
#include "character.h"

namespace seneca {
    class Guild {
    private:
        std::string m_name;          // Name of the guild
        Character** m_members;       // Array of pointers to Character
        size_t m_size;               // Number of members in the guild
        size_t m_capacity;           // Current capacity of the array

        // Private methods to handle array resizing
        void resize();

    public:
        // Default constructor
        Guild();

        // Parameterized constructor
        Guild(const char* name);

        ~Guild();                                  // Destructor
        Guild(const Guild& other);                 // Copy constructor
        Guild& operator=(const Guild& other);      // Copy assignment
        Guild(Guild&& other) noexcept;             // Move constructor
        Guild& operator=(Guild&& other) noexcept;  // Move assignment

        // Public methods
        void addMember(Character* c);               // Add a new member and give them extra 300 health
        void removeMember(const std::string& name); // Remove a member and deduct 300 health
        Character* operator[](size_t idx) const;    // Access a member by index
        void showMembers() const;                   // Display the members of the guild
    };
}

#endif // !SENECA_GUILD_H
