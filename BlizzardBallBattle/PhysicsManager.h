#pragma once

class PhysicsManager {
private:
	static PhysicsManager* instance;
public:
	static PhysicsManager* GetInstance();
	void update();
};