#ifndef AIC20_CLIENT_CPP_GAMECONSTANTS_H
#define AIC20_CLIENT_CPP_GAMECONSTANTS_H


class GameConstants {
public:
    GameConstants() = default;

    ~GameConstants() = default;

    int maxAp();

    int maxTurns();

    int turnTimeout();

    int pickTimeout();

    int turnsToUpgrade();

    int turnsToSpell();

    int damageUpgradeAddition();

    int rangeUpgradeAddition();

private:
    int max_ap_;
    int max_turns_;
    int turn_timeout_;
    int pick_timeout_;
    int turns_to_upgrade_;
    int turns_to_spell_;
    int damage_upgrade_addition_;
    int range_upgrade_addition_;

};


#endif //AIC20_CLIENT_CPP_GAMECONSTANTS_H
