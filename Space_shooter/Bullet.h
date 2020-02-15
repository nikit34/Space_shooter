#include"SFML\Graphics.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include<iostream>

using namespace sf;

class Bullet
{
public:
	Bullet(Texture *texture, Vector2f position, 
		Vector2f maxVelocity = Vector2f(15.f, 0.f));
	virtual ~Bullet();

	// Accessors
	inline const FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline const Vector2f getPosition() const { return this->sprite.getPosition(); }

	
	// Functions
	void Movement();
	void Update();
	void Draw(RenderTarget &target);

private:
	Texture *texture;
	Sprite sprite;

	Vector2f maxVelocity;
};
 