#include <queue>
#include "aocutil.h"

//#define TEST
#ifdef TEST
    const int BossHP = 12;
    const int BossDamage = 7;
    const int BossArmor = 2;
    const int PlayerHP = 8;
#else
    const int BossHP = 103;
    const int BossDamage = 9;
    const int BossArmor = 2;
    const int PlayerHP = 100;
#endif

struct Item {
    int Cost, Damage, Armor;
};

struct Equipment {
    int WeaponId = -1, ArmorId = -1, Ring1 = -1, Ring2 = -1, Cost = 0, Damage = 0, Armor = 0;
    Equipment() {}
    Equipment(int weapon, int cost, int damage, int armor) { WeaponId = weapon; Cost = cost; Damage = damage; Armor = armor; }
};

bool fight(Equipment);

aoc_result_t day21() {

#ifdef TEST
    Equipment etest{};
    etest.Damage = 5;
    etest.Armor = 5;
    etest.Cost = 112;
    bool twin = fight(etest);
    return {twin ? etest.Cost : -1,0};
#endif

    std::vector<Item> weapons{
        Item{8,4,0},
        Item{10,5,0},
        Item{25,6,0},
        Item{40,7,0},
        Item{74,8,0},
    };
    std::vector<Item> armor{
        //Item{0,0,0}, // No armor
        Item{13,0,1},
        Item{31,0,2},
        Item{53,0,3},
        Item{75,0,4},
        Item{102,0,5},
    };
    std::vector<Item> rings{
        Item{25,1,0},
        Item{50,2,0},
        Item{100,3,0},
        Item{20,0,1},
        Item{40,0,2},
        Item{80,0,3},
    };

    int wsize = (int)weapons.size();
    int asize = (int)armor.size();
    int rsize = (int)rings.size();

    Equipment best{};
    Equipment worst{};
    // Must pick exactly one weapon
    for (int w = 0; w < wsize; w++) {
        // Don't really need a queue for this. Could just as easily add all equipment
        // combinations to a list and then try each one out.
        std::queue<Equipment> totry;
        totry.push(Equipment{w, weapons[w].Cost, weapons[w].Damage, weapons[w].Armor});
        Equipment current;
        while (!totry.empty()) {
            current = totry.front();
            totry.pop();

            // Fight!
            bool win = fight(current);
            if (win) {
                if (best.Cost == 0 || current.Cost < best.Cost) {
                    best = current;
                }
            } else {
                if (worst.Cost == 0 || current.Cost > worst.Cost) {
                    worst = current;
                }
            }

            // Try the next piece of armour
            if (current.Ring1 < 0 && current.ArmorId < asize - 1) {
                Equipment e{current};
                int aid = current.ArmorId;
                // Remove the old armor values (if any) and add the new
                e.ArmorId = current.ArmorId + 1;
                e.Cost += armor[e.ArmorId].Cost - (aid >= 0 ? armor[aid].Cost : 0);
                e.Damage += armor[e.ArmorId].Damage - (aid >= 0 ? armor[aid].Damage : 0);
                e.Armor += armor[e.ArmorId].Armor - (aid >= 0? armor[aid].Armor : 0);

                totry.push(e); // No rings

                // Add all other combinations of rings to try
                for (int r1 = 0; r1 < rsize; r1++) {
                    // By itself
                    Equipment er1{e};
                    er1.Ring1 = r1;
                    er1.Cost += rings[r1].Cost;
                    er1.Damage += rings[r1].Damage;
                    er1.Armor += rings[r1].Armor;
                    totry.push(er1);

                    for (int r2 = r1 + 1; r2 < rsize; r2++) {
                        // With one other ring
                        Equipment er2{er1};
                        er2.Ring2 = r2;
                        er2.Cost += rings[r2].Cost;
                        er2.Damage += rings[r2].Damage;
                        er2.Armor += rings[r2].Armor;
                        totry.push(er2);
                    }
                }
            }
        }
    }
    return {best.Cost,worst.Cost};
}

bool fight(Equipment equipment) {
    int boss = BossHP;
    int player = PlayerHP;

    while (boss > 0 && player > 0) {
        // player turn
        int attack = equipment.Damage - BossArmor;
        boss -= attack > 0 ? attack : 1;
        if (boss <= 0) break;

        // boss turn
        attack = BossDamage - equipment.Armor;
        player -= attack > 0 ? attack : 1;
    }

    return player > boss;
}
