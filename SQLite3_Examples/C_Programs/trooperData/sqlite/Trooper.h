#pragma once

#include <string>
using namespace std;

/*
 * This is used to store data about troopers.
 */
class Trooper
{
	public:
		explicit Trooper() {};
		virtual ~Trooper() {};

		// Setters.
		inline void const trooperID(const int value)				{ id = value; }
		inline void const trooperName(const string value)			{ name = value; }

		// ATTACK.
		inline void const setRawAttack(const float value)			{ attackRaw = value; }
		inline void const setRawAttackRange(const float value)		{ attackRawRange = value; }
		inline void const setBonusAttack(const float value)			{ attackBonus = value; }
		inline void const setBonusAttackRange(const float value)	{ attackBonusRange = value; }
		inline void const setAttackRange(const int value)			{ attackRange = value; }

		// DEFENCE.
		inline void const setRawDefence(const float value)			{ defence = value; }

		// PERCENTAGES.
		inline void const setCriticalChance(const float value)		{ criticalChance = value; }
		inline void const setCriticalMultiplier(const float value)	{ criticalDamage = value; }
		inline void const setEvasion(const float value)				{ evasion = value; }
		inline void const setCooldown(const float value)			{ skillCooldown = value; }

		// HEALTH.
		inline void const setMaxHealth(const float value)			{ maximumHealth = value; }
		inline void const setCurrentHealth(const float value)		{ health = value; }

		// MOVEMENT.
		inline void const setMovement(const int value)				{ numberOfTiles = value; }

		// ACTIONS.
		inline void const setNumberOfActions(const int value)		{ numberOfActions = value; }

		// Getters.
		inline int const trooperID()			{ return id; }
		inline string const trooperName()		{ return name; }

		// ATTACK.
		inline float const rawAttack()			{ return attackRaw; }
		inline float const rawAttackRange()		{ return attackRawRange; }
		inline float const bonusAttack()		{ return attackBonus; }
		inline float const bonusAttackRange()	{ return attackBonusRange; }
		inline int const range()				{ return attackRange; }

		// DEFENCE.
		inline float const rawDefence()			{ return defence; }

		// PERCENTAGES.
		inline float const criticalPercentage() { return criticalChance; }
		inline float const criticalMultiplier() { return criticalDamage; }
		inline float const chanceToEvade()		{ return evasion; }
		inline float const cooldown()			{ return skillCooldown; }

		// HEALTH.
		inline float const maxHealth()			{ return maximumHealth; }
		inline float const currentHealth()		{ return health; }

		// MOVEMENT.
		inline int const movement()				{ return numberOfTiles; }

		// ACTIONS.
		inline int const actions()				{ return numberOfActions; }

	protected:
		// Trooper Stats.
		int id = 0;
		string name = "";

		// Attack Stats.
		float attackRaw = 10.0f;
		float attackRawRange = 2.0f;
		float attackBonus = 15.0f;
		float attackBonusRange = 5.0f;
		int attackRange = 1;

		// Defence Stats.
		float defence = 5.0f;

		// Percentages.
		float criticalChance = 0.0f;
		float criticalDamage = 1.0f;
		float evasion = 0.0f;
		float skillCooldown = 0.0f;

		// Health.
		float maximumHealth = 100.0f;
		float health = 100.0f;

		// Movement.
		int numberOfTiles = 2;

		// Actions.
		int numberOfActions = 1;
};