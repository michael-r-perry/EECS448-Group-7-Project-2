#ifndef AI_H
#define AI_H
class AI
{
  public:
     char selectOrientation();
     std::tuple<int, int> placeShip(char orientation);
     std::tuple<int, int> Shoot();
  private:
    void easyShoot();
    void mediumShoot();
    void hardShoot();
};
#endif
