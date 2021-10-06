#ifndef AI_H
#define AI_H

#include <tuple>

class AI
{
    public:
        AI();
        void setDifficulty(char difficulty);
        char selectOrientation();
        std::tuple<int, int> placeShip(char orientation, int counter);
        std::tuple<int, int> Shoot();

    private:
        std::tuple<int, int> easyShoot();
        std::tuple<int, int> mediumShoot();
        std::tuple<int, int> hardShoot();
        std::tuple<int, int> hardShootHelper();
        char m_difficulty;
        bool m_randomShoot;
        bool m_searching;
        int rowMarker;
        int colMarker;
};
#endif
