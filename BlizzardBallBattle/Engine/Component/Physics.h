#pragma once

#include "Component.h"

//#define PROPERTY(t,n) __declspec( property (put = property__set_##n, get = property__get_##n)) t n;\
//	typedef t property__tmp_type_##n
//#define READONLY_PROPERTY(t,n) __declspec( property (get = property__get_##n) ) t n;\
//	typedef t property__tmp_type_##n
//#define WRITEONLY_PROPERTY(t,n) __declspec( property (put = property__set_##n) ) t n;\
//	typedef t property__tmp_type_##n
//#define GET(n) property__tmp_type_##n property__get_##n() 
//#define SET(n) void property__set_##n(const property__tmp_type_##n& value)   


class Physics : public Component {
private:
	float _velocity;
public:
	Physics(GameObject* gamObject);
	~Physics();

	//__declspec (property (put = setVelocity, get = getVelocity)) float velocity;
	void setVelocity(float value) {
		_velocity = value;
	}

	float getVelocity() {
		return _velocity;
	}
	/* testing properties
	PROPERTY(float, velocity);
	GET(velocity)
	{
		return _velocity;
	}
	SET(velocity) {
		_velocity = value;
	}

	*/
	void OnStart(){};
	void OnUpdate(int ticks){};
	void OnEnd(){};

};