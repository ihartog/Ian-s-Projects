#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include <string>
#include <type_traits>
#include "character.h"
#include "health.h"

namespace seneca {

    // Templated CharacterTpl class derived from Character
    template <typename T>
    class CharacterTpl : public Character {
    private:
        int m_healthMax;   // Maximum health
        T m_health;        // Current health of type T

    public:
        // Constructor
        CharacterTpl(const std::string& name, int maxHealth);

        // Override methods
        void takeDamage(int dmg) override;
        int getHealth() const override;
        int getHealthMax() const override;
        void setHealth(int health) override;
        void setHealthMax(int health) override;
    };

    // Method implementations

    // Constructor definition
    template <typename T>
    CharacterTpl<T>::CharacterTpl(const std::string& name, int maxHealth)
        : Character(name.c_str()), m_healthMax(maxHealth)
    {
        m_health = maxHealth; 
    }

    // takeDamage method
    template <typename T>
    void CharacterTpl<T>::takeDamage(int dmg) {
        m_health -= dmg;

        // Ensure health does not go below 0
        if (m_health < 0) {
            m_health = 0;
        }

        if (getHealth() <= 0) {
            std::cout << "    " << getName() << " has been defeated!" << std::endl;
        }
        else {
            std::cout << "    " << getName() << " took " << dmg << " damage, "
                << getHealth() << " health remaining." << std::endl;
        }
    }


    // getHealth method
    template <typename T>
    int CharacterTpl<T>::getHealth() const {
        return static_cast<int>(m_health);
    }

    // getHealthMax method
    template <typename T>
    int CharacterTpl<T>::getHealthMax() const {
        return m_healthMax;
    }

    // setHealth method
    template <typename T>
    void CharacterTpl<T>::setHealth(int health) {
        m_health = health;
    }

    // setHealthMax method
    template <typename T>
    void CharacterTpl<T>::setHealthMax(int health) {
        m_healthMax = health;
        m_health = health;
    }

}

#endif // SENECA_CHARACTERTPL_H
