#pragma once

#include "Bullet.h"

class Player {
 public:
  virtual ~Player();
  Player(std::vector<Texture> &textures, int UP = 22, int DOWN = 18,
         int LEFT = 0, int RIGHT = 3, int SHOOT = 57);

  // Accessors
  inline std::vector<Bullet> &getBullets() { return this->bullets; }
  inline const Vector2f &getPosition() const {
    return this->sprite.getPosition();
  }
  inline const String getHpAsString() const {
    return std::to_string(this->hp) + "/" + std::to_string(this->hpMax);
  }

  // Functions
  void UpdateAccessories();
  void Combat();
  void Movement();
  void Update(Vector2u windowBounds);
  void Draw(RenderTarget &target);

  static unsigned players;

 private:
  unsigned playerNr;

  Vector2f playerCenter;

  int shootTimer;
  int shootTimerMax;
  int damageTimer;
  int damageTimerMax;

  Sprite sprite;
  RectangleShape hitBox;

  // Accessories
  Sprite mainGunSprite;

  std::vector<Bullet> bullets;
  Texture *laserTexture;
  Texture *missile01Texture;
  Texture *missile02Texture;

  int controls[5];
  Vector2f currentVelocity;
  float maxVelocity;
  float acceleration;
  Vector2f direction;
  float stabilizerForce;

  int level;
  int exp;
  int expNext;

  int hp;
  int hpMax;

  int damage;
  int damageMax;

  int score;

  // Upgrades
  int currentWeapon;

  int mainGunLevel;
  bool dualMissiles01;
  bool dualMissiles02;
};