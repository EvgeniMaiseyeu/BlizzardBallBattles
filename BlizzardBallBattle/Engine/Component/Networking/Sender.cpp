#include "Sender.h"

Sender::Sender(GameObject* gameObject, std::string ID) : Component(gameObject) {
    this->ID = ID;
}

void Sender::SendUpdate() { //This may be an issue, passing pointers to things on the stack
    std::map<std::string, std::string> payload;
    Transform* transform = gameObject->GetComponent<Transform*>();
    payload["x"] = std::to_string(transform->getX() + 1.0f);
    payload["y"] = std::to_string(transform->getY());
    payload["rotation"] = std::to_string(transform->getRotation());
    payload["scale"] = std::to_string(transform->getScale());
    //std::cout << "SEND EVENT: " << this->ID + ":UPDATE" << std::endl;
    NetworkingManagerTemp::GetInstance()->PrepareMessageForSending(this->ID + "|UPDATE", payload);
}