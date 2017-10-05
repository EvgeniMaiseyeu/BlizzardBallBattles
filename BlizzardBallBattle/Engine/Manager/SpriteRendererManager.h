#include <map>

class SpriteRendererManager {
private:
    SpriteRendererManager *instance;

public:
    typedef pair<int, SpriteRenderer*> spriteRenderers;

    static SpriteRendererManager* getInstance();

    void Subscribe(int id, SpriteRender* spriteRenderer);
    void UnSubscribe(int id);
    void Update(int ticks);
}