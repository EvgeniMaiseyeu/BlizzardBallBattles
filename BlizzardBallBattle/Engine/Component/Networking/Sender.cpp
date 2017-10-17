#include "Sender.h"

Sender::Sender(GameObject* gameObject, std::string ID) : Component(gameObject) {
    this->ID = ID;
}

void Sender::SendUpdate() { //This may be an issue, passing pointers to things on the stack
    std::map<std::string, std::string> payload;
    Transform* transform = gameObject->GetComponent<Transform*>();
    payload["x"] = std::to_string(transform->getX());
    payload["y"] = std::to_string(transform->getY());
    payload["z"] = std::to_string(transform->getZ());
    payload["rotation"] = std::to_string(transform->getRotation());
    payload["scale"] = std::to_string(transform->getScale());
    NetworkingManagerTemp::GetInstance()->PrepareMessageForSending(this->ID + "|UPDATE", payload);
}