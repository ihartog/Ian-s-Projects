#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "weapons.h"
#include "abilities.h"
#include <iostream>

namespace seneca {
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
    private:
        int m_baseDefense;        // Base defense value
        int m_baseAttack;         // Base attack value
        FirstAbility_t m_firstAbility;  // First special ability
        SecondAbility_t m_secondAbility; // Second special ability
        seneca::Dagger m_weapon;  // Weapon used by rogue (dagger)

    public:
        // Constructor
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense);

        // Public methods
        int getAttackAmnt() const;
        int getDefenseAmnt() const;
        Character* clone() const override;
        void attack(Character* enemy) override;
        void takeDamage(int dmg) override;
    };

    // Constructor definition
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    Rogue<T, FirstAbility_t, SecondAbility_t>::Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
        : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(seneca::Dagger()) {}

    // Get attack amount: Rogue's attack is base attack + 2 * dagger damage
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    int Rogue<T, FirstAbility_t, SecondAbility_t>::getAttackAmnt() const {
        return static_cast<int>(m_baseAttack + 2 * m_weapon);
    }

    // Get defense amount: Rogue's defense is base defense
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    int Rogue<T, FirstAbility_t, SecondAbility_t>::getDefenseAmnt() const {
        return m_baseDefense;
    }

    // Clone method: Creates a copy of the current Rogue
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    Character* Rogue<T, FirstAbility_t, SecondAbility_t>::clone() const {
        return new Rogue(*this);
    }

    // Attack method: Prints the attack message, activates abilities, enhances damage, and applies it to the enemy
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    void Rogue<T, FirstAbility_t, SecondAbility_t>::attack(Character* enemy) {
        std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

        // Activate first special ability
        m_firstAbility.useAbility(this);

        // Activate second special ability
        m_secondAbility.useAbility(this);

        // Get the attack damage
        int damage = getAttackAmnt();

        // Enhance the damage using the first special ability
        m_firstAbility.transformDamageDealt(damage);

        // Enhance the damage using the second special ability
        m_secondAbility.transformDamageDealt(damage);

        std::cout << "Rogue deals " << damage << " melee damage!" << std::endl;

        // Inflict damage on the enemy
        enemy->takeDamage(damage);
    }

    // Take damage method: Reduces the damage using defense and special abilities, then calls base class to apply damage
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    void Rogue<T, FirstAbility_t, SecondAbility_t>::takeDamage(int dmg) {
        std::cout << "    " << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

        // Apply defense reduction
        dmg -= getDefenseAmnt();
        if (dmg < 0) dmg = 0;

        // Further reduce damage using first ability
        m_firstAbility.transformDamageReceived(dmg);

        // Further reduce damage using second ability
        m_secondAbility.transformDamageReceived(dmg);

        // Call the base class takeDamage to apply the final damage
        CharacterTpl<T>::takeDamage(dmg);
    }

    template class Rogue<int, Fireball, Heal>;
    template class Rogue<double, Fireball, Heal>;

} // namespace seneca

#endif // SENECA_ROGUE_H
