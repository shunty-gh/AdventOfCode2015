#include <limits>
#include <queue>
#include "aocutil.h"

//#define TEST
#ifdef TEST
    const int InitialBossHP = 14;
    const int InitialBossDamage = 8;
    const int InitialPlayerHP = 10;
    const int InitialPlayerMana = 250;
#else
    const int InitialBossHP = 55;
    const int InitialBossDamage = 8;
    const int InitialPlayerHP = 50;
    const int InitialPlayerMana = 500;
#endif

struct Spell {
    int Id, Cost, Damage, Heal, Armor, Mana, EffectLength;
};

struct PlayState {
    int BossHP, BossDamage;
    int PlayerHP, PlayerArmor, PlayerMana;
    int Cost;
    bool Fault;
    std::vector<Spell> SpellStack;

    PlayState() {
        BossHP = InitialBossHP;
        BossDamage = InitialBossDamage;
        PlayerHP = InitialPlayerHP;
        PlayerArmor = 0;
        PlayerMana = InitialPlayerMana;
        Cost = 0;
        Fault = false;
        SpellStack = std::vector<Spell>{};
    }
};

struct PlayStateToTry {
    PlayState State;
    Spell SpellToCast;
};

int play_game(const std::vector<Spell>&, bool);
PlayState fight(PlayState, Spell, bool);

aoc_result_t day22() {
    std::vector<Spell> availableSpells{
        Spell{0,  53, 4, 0, 0,   0, 0 },  // Magic missile
        Spell{1,  73, 2, 2, 0,   0, 0 },  // Drain
        Spell{2, 113, 0, 0, 7,   0, 6 },  // Shield - effect lasts for 6 turns - armor increased by 7
        Spell{3, 173, 3, 0, 0,   0, 6 },  // Poison - effect lasts for 6 turns - deals the boss 3 damage
        Spell{4, 229, 0, 0, 0, 101, 5 },  // Recharge - effect lasts for 5 turns - gives you 101 new mana
    };

#ifdef TEST
    PlayState state{};
    Spell spell = availableSpells[4];
    state = fight(state, spell);
    spell = availableSpells[2];
    state = fight(state, spell);
    spell = availableSpells[1];
    state = fight(state, spell);
    spell = availableSpells[3];
    state = fight(state, spell);
    spell = availableSpells[0];
    state = fight(state, spell); // Expect BossHP = -1; PlayerHP = 1; Armor = 0; Mana = 114;
    return {0,0};
#endif

    int part1 = play_game(availableSpells, false);
    int part2 = play_game(availableSpells, true);
    return {part1, part2};
}

int play_game(const std::vector<Spell>& availableSpells, bool isPart2) {
    int lowest = INT_MAX;
    std::queue<PlayStateToTry> totry;
    for (auto &&spell : availableSpells) {
        totry.push(PlayStateToTry{PlayState{}, spell});
    }

    PlayStateToTry pst;
    while (!totry.empty()) {
        pst = totry.front();
        totry.pop();

        // don't bother continuing if we're already more expensive than we need to be
        if ((pst.State.Cost + pst.SpellToCast.Cost) > lowest) {
            continue;
        }

        auto nextState = fight(pst.State, pst.SpellToCast, isPart2);
        // Has this battle reached its conclusion
        if (nextState.Fault || nextState.BossHP <= 0 || nextState.PlayerHP <= 0) {
            if (!nextState.Fault && nextState.BossHP <= 0) {
                // We won. Make a note, if necessary
                if (nextState.Cost < lowest) {
                    lowest = nextState.Cost;
                }
            }
            continue;
        }

        // Try the next spells - if they're not too expensive
        for (auto& nextSpell : availableSpells) {
            if ((nextState.Cost + nextSpell.Cost) < lowest) {
                totry.push(PlayStateToTry{PlayState{nextState}, nextSpell});
            }
        }
    }
    return lowest;
}

PlayState fight(PlayState state, Spell spellToCast, bool isPart2) {

    // Players turn
    PlayState result{state};
    result.SpellStack.clear(); // Rebuild this as necessary
    result.PlayerArmor = 0; // This will be reinstated if the Shield spell is cast in this round

    if (isPart2) {
        result.PlayerHP -= 1;
        if (result.PlayerHP <= 0) return result;
    }

    // first apply the effect of the current spell stack
    for (auto& spell : state.SpellStack) {
        if (spell.EffectLength <= 0) {
            continue;
        }
        result.BossHP -= spell.Damage;
        result.PlayerHP += spell.Heal;
        result.PlayerMana += spell.Mana;
        if (spell.EffectLength > 1) {
            Spell newspell{spell};
            newspell.EffectLength -= 1;
            result.SpellStack.push_back(newspell);
        }

        if (result.BossHP <= 0) {
            return result;
        }
    }

    // Now check we can actually apply this next spell
    if (spellToCast.Cost > result.PlayerMana) { // Too expensive
            result.Fault = true;
    }
    bool alreadyGotOne = false;
    for (auto& ss : result.SpellStack) {
        if (ss.Id == spellToCast.Id && ss.EffectLength > 0) { // Already one of these spells active
            result.Fault = true;
            break;
        }
    }
    if (result.Fault) return result;

    // Now apply this spell
    result.PlayerMana -= spellToCast.Cost;
    result.Cost += spellToCast.Cost;
    result.SpellStack.push_back(spellToCast);

    // Boss' turn
    // Apply the effects of the spell stack
    for (auto& spell : result.SpellStack) {
        result.BossHP -= spell.Damage;
        result.PlayerHP += spell.Heal;
        result.PlayerArmor += spell.Armor;
        result.PlayerMana += spell.Mana;
        spell.EffectLength -= 1;
    }
    if (result.BossHP <= 0) {
        return result;
    }
    // Now the boss finally gets to attack
    int attack = result.BossDamage - result.PlayerArmor;
    if (attack <= 0) attack = 1;
    result.PlayerHP -= attack;

    return result;
}
