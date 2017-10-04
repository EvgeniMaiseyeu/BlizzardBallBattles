class InputManager {
public:
    Keys[] keys;
    void SubscribeKey(int key) {
        keys.push(key)
    }

    void UnSubscribeKey(int key) {
        keys.remove(key);
    }

    void Update() { 
        while (SDL_PollEvent(&event)) {
            if (!HandlePolledEvent(event)) {
                gameLoop = false;
            }
        }
    }

    bool HandlePolledEvent(SDL_Event event) {
          keys[event.key.keysym.sym]
      }
}