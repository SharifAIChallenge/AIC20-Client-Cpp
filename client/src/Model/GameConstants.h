#ifndef AIC20_CLIENT_CPP_GAMECONSTANTS_H
#define AIC20_CLIENT_CPP_GAMECONSTANTS_H


class GameConstants {
public:
    GameConstants() = default;

    ~GameConstants() = default;

    int getMaxAp() const;

    int getApAddition() const;

    int getMaxTurns() const;

    int getTurnTimeout() const;

    int getPickTimeout() const;

    int getTurnsToUpgrade() const;

    int getTurnsToSpell() const;

    int getDamageUpgradeAddition() const;

    int getRangeUpgradeAddition() const;

    int getDeckSize() const;

    int getHandSize() const;

private:
    int max_ap_;
    int ap_addition_;
    int max_turns_;
    int turn_timeout_;
    int pick_timeout_;
    int turns_to_upgrade_;
    int turns_to_spell_;
    int damage_upgrade_addition_;
    int range_upgrade_addition_;
    int deck_size_;
    int hand_size_;

    friend class InitMessage;
    friend class Game;
};


#endif //AIC20_CLIENT_CPP_GAMECONSTANTS_H
