#include "Receiver.h"


Receiver::Receiver(GameObject* gameObject, std::string netID) : Component(gameObject) {
    this->netID = netID;
    //Add to map of type "event", key "id"
        std::cout << "RECEIVER SUBSCRIBBED" << std::endl;

    MessageManager::Subscribe(netID + "|UPDATE",  [](std::map<std::string, void*> data) -> void {
        float x = std::stof(*(std::string*)data["scale"]);
        float y = std::stof(*(std::string*)data["y"]);
        float z = std::stof(*(std::string*)data["z"]);
        float angle = std::stof(*(std::string*)data["rotation"]);
        float scale = std::stof(*(std::string*)data["scale"]);
        Receiver* self = (Receiver*)data["this"];
        std::cout << "PLAYER 2::X TO SET :" << x + 1.0f << "::Y TO SET : " << y << "::ANGLE TO SET :" << angle << std::endl;
        Transform* transform = self->gameObject->GetComponent<Transform*>();
        transform->setPosition(x + 1.0f, y, z );
        transform->setRotation(angle);
        transform->setScale(scale);
    }, this);

    MessageManager::Subscribe(netID + ":CREATE", [](std::map<std::string, void*> data) -> void {
      std::cout << " CREATE OBJECT CALLED " << std::endl;
    }, this);
}

Receiver::~Receiver() {
    //Unsubscribe
}