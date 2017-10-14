#include "Receiver.h"


Receiver::Receiver(GameObject* gameObject, std::string netID) : Component(gameObject) {
    this->netID = netID;
    //Add to map of type "event", key "id"
        std::cout << "RECEIVER SUBSCRIBBED" << std::endl;

    MessageManager::Subscribe(netID + "|UPDATE",  [](std::map<std::string, void*> data) -> void {
        std::cout << "RECEIVED WTF" << std::endl;
        float* x = (float*)data["x"];
        float* y = (float*)data["y"];
        float* angle = (float*)data["rotation"];
        float* scale = (float*)data["scale"];
        Receiver* this2 = (Receiver*)data["this"];
        //std::cout << "Update(): " << (*x) << " " << (*y) << " " << (*angle) << " " < (*scale) << " " << std::endl;
        Transform* transform = this2->gameObject->GetComponent<Transform*>();
        transform->setPosition(*x, *y );
        transform->setRotation(*angle);
        transform->setScale(*scale);
    }, this);

    MessageManager::Subscribe(netID + ":CREATE", [](std::map<std::string, void*> data) -> void {
      std::cout << " CREATE OBJECT CALLED " << std::endl;
    }, this);
}

Receiver::~Receiver() {
    //Unsubscribe
}
