class SpriteRendererManager() {
public:
    void Subscribe(int id, SpriteRender* spriteRenderer) {
        spriteRenderers.push(id, spriteRenderer)
    }
    void UnSubscribe(int id) {
        spriteRenderers.remove(id);
    }
    void Update() {
        foreach(spriteRenderer in spriteRenderers)
            spriteRenderer.render();
    }
}