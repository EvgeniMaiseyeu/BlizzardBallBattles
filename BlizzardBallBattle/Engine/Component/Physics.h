#pragma once

#include "Vector2.h"
#include "GameObject.h"
#include "Transform.h"

class Physics : public Component {
private:
	Transform* transform;
	float _snowDrag; //this is the slow factor from when the player or ai is hit or maybe even weather
	float _drag; //this is the slow factor for projectiles ( and maybe for players on a different map such as an ice field )
	float _velDrag; //this is drag for slowing down when letting go of the key
	bool _applyingForce; //set to true when holding key down for player movement, otherwise set to false and obj will slow down
	Vector2* _velocity;
	Vector2* _aVelocity;
public:
	Physics(GameObject* gamObject);
	~Physics();

	//__declspec (property (put = setVelocity, get = getVelocity)) float velocity;
	void setVelocity(Vector2* value);
	Vector2* getVelocity();
	
	void setAngularVelocity(Vector2* value);
	Vector2* getAngularVelocity();
	
	void setApplyingForce(bool value);
	bool getApplyingForce();

	void setSnowDrag(float value);
	float getSnowDrag();
	void addSnowDrag(float value);

	void setDrag(float value);
	float getDrag();
	void addDrag(float value);
		
	void setVelDrag(float value);
	float getVelDrag();
	void addVelDrag(float value);

	void OnStart(){};
	void OnUpdate(int ticks);
	void OnEnd(){};
};