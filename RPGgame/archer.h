#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"
#include "weapons.h"
#include <iostream>

namespace seneca {

    template <typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth> {
    private:
        int m_baseDefense;   // Base defense value
        int m_baseAttack;    // Base attack value
        Weapon_t m_weapon;   // Weapon the archer uses

    public:
        // Constructor
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon);

        // Public methods
        int getAttackAmnt() const;
        int getDefenseAmnt() const;
        Character* clone() const override;
        void attack(Character* enemy) override;
        void takeDamage(int dmg) override;
    };

    // Constructor definition
    template <typename Weapon_t>
    Archer<Weapon_t>::Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
        : CharacterTpl<seneca::SuperHealth>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(weapon) {}

    // Get attack amount: Archer's attack is 1.3 * base attack, weapon is ignored
    template <typename Weapon_t>
    int Archer<Weapon_t>::getAttackAmnt() const {
        return static_cast<int>(1.3 * m_baseAttack);
    }

    // Get defense amount: Archer's defense is 1.2 * base defense
    template <typename Weapon_t>
    int Archer<Weapon_t>::getDefenseAmnt() const {
        return static_cast<int>(1.2 * m_baseDefense);
    }

    // Clone method: Creates a copy of the current Archer
    template <typename Weapon_t>
    Character* Archer<Weapon_t>::clone() const {
        return new Archer(*this);
    }

    // Attack method: Prints the attack message, calculates damage, and applies it to the enemy
    template <typename Weapon_t>
    void Archer<Weapon_t>::attack(Character* enemy) {
        std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

        // Get attack damage
        int damage = getAttackAmnt();

        std::cout << "Archer deals " << damage << " ranged damage!" << std::endl;

        // Inflict damage on the enemy
        enemy->takeDamage(damage);
    }

    // Take damage method: Reduces the damage by defense, then applies the remaining damage
    template <typename Weapon_t>
    void Archer<Weapon_t>::takeDamage(int dmg) {
        std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "Archer has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

        // Apply defense reduction
        dmg -= getDefenseAmnt();
        if (dmg < 0) dmg = 0;

        // Call the base class takeDamage to apply the final damage
        CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
    }

    // Explicit template instantiations for specific types
    template class Archer<Crossbow>;
    template class Archer<Bow>;

} // namespace seneca

#endif // SENECA_ARCHER_H
