#include "Player.h"
#include "transform.h"

Player::Player(Shader* shader, GLuint textureBufferID) {
	AddComponent<SpriteRenderer*>(new SpriteRenderer(this));
	SpriteRenderer* renderer = (SpriteRenderer*)GetComponent<Transform*>();
	renderer->SetActiveShader(shader);
	renderer->SetActiveTexture(textureBufferID);
}

void Player::PressedDown() {
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addY(-0.2f);

}

void Player::PressedRight() {
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addX(0.2f);

}

void Player::PressedUp() {
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addY(0.2f);

}

void Player::PressedLeft() {
	Transform* transform = (Transform*)GetComponent<Transform*>();
	transform->addX(-0.2f);

}