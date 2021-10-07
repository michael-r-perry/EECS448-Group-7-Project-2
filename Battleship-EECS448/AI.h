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
        void HandleResult(char result);

    private:
        std::tuple<int, int> easyShoot();
        std::tuple<int, int> mediumShoot();
        std::tuple<int, int> hardShoot();
        std::tuple<int, int> hardShootHelper();
        void flipDirection();
        bool isValidCoords(int row, int col);
        char m_difficulty;
        bool m_randomShoot;
        bool m_searching;
        bool m_firstDirection;
        int m_direction;
        std::tuple<int, int> m_directions[4];
        int rowOrig;
        int colOrig;
        int rowMark;
        int colMark;
};
#endif
