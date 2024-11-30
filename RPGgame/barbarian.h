#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.h"
#include "weapons.h"
#include "abilities.h"
#include <iostream>

namespace seneca {

    // Templated Barbarian class derived from CharacterTpl<T>
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
    private:
        int m_baseDefense;         // Base defense value
        int m_baseAttack;          // Base attack value
        Ability_t m_ability;       // Special ability of the Barbarian
        Weapon_t m_weapon[2];      // Two weapons the Barbarian uses

    public:
        // Constructor
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon);

        // Copy constructor
        Barbarian(const Barbarian& other);

        // Copy assignment operator
        Barbarian& operator=(const Barbarian& other);

        // Public methods
        int getAttackAmnt() const;
        int getDefenseAmnt() const;
        Character* clone() const override;
        void attack(Character* enemy) override;
        void takeDamage(int dmg) override;
    };

    // Constructor definition
    template <typename T, typename Ability_t, typename Weapon_t>
    Barbarian<T, Ability_t, Weapon_t>::Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
        : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack) {
        m_weapon[0] = primaryWeapon;
        m_weapon[1] = secondaryWeapon;
    }

    // Copy constructor
    template <typename T, typename Ability_t, typename Weapon_t>
    Barbarian<T, Ability_t, Weapon_t>::Barbarian(const Barbarian& other)
        : CharacterTpl<T>(other), // Copy the base class
        m_baseDefense(other.m_baseDefense),
        m_baseAttack(other.m_baseAttack),
        m_ability(other.m_ability) {
        m_weapon[0] = other.m_weapon[0];
        m_weapon[1] = other.m_weapon[1];
    }

    // Copy assignment operator
    template <typename T, typename Ability_t, typename Weapon_t>
    Barbarian<T, Ability_t, Weapon_t>& Barbarian<T, Ability_t, Weapon_t>::operator=(const Barbarian& other) {
        if (this != &other) {
            // Call base class assignment operator
            CharacterTpl<T>::operator=(other);

            // Copy Barbarian-specific members
            m_baseDefense = other.m_baseDefense;
            m_baseAttack = other.m_baseAttack;
            m_ability = other.m_ability;
            m_weapon[0] = other.m_weapon[0];
            m_weapon[1] = other.m_weapon[1];
        }
        return *this;
    }

    // Get attack amount
    template <typename T, typename Ability_t, typename Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getAttackAmnt() const {
        return static_cast<int>(m_baseAttack + (m_weapon[0] / 2.0) + (m_weapon[1] / 2.0));
    }

    // Get defense amount
    template <typename T, typename Ability_t, typename Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getDefenseAmnt() const {
        return m_baseDefense;
    }

    // Clone method
    template <typename T, typename Ability_t, typename Weapon_t>
    Character* Barbarian<T, Ability_t, Weapon_t>::clone() const {
        return new Barbarian(*this);
    }

    // Attack method
    template <typename T, typename Ability_t, typename Weapon_t>
    void Barbarian<T, Ability_t, Weapon_t>::attack(Character* enemy) {
        std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

        // Use special ability
        m_ability.useAbility(this);

        // Get the attack damage
        int damage = getAttackAmnt();

        // Enhance the damage using the ability
        m_ability.transformDamageDealt(damage);

        std::cout << "    Barbarian deals " << damage << " melee damage!" << std::endl;

        // Inflict damage on the enemy
        enemy->takeDamage(damage);
    }

    // Take damage method
    template <typename T, typename Ability_t, typename Weapon_t>
    void Barbarian<T, Ability_t, Weapon_t>::takeDamage(int dmg) {
        std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "    Barbarian has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

        // Apply defense
        dmg -= getDefenseAmnt();
        if (dmg < 0) dmg = 0;

        // Use special ability to reduce damage further
        m_ability.transformDamageReceived(dmg);

        // Call base class to update health
        CharacterTpl<T>::takeDamage(dmg);
    }

    template class Barbarian<int, Fireball, Sword>;
    template class Barbarian<double, Heal, Bow>;

}

#endif // !SENECA_BARBARIAN_H
