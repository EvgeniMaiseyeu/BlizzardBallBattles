class SpriteRenderer {
public:
    Sprite sprite;
    Texture texture;
    SpriteRenderer(Entity* entity) {
        super(entity);
        SpriteRendererManager.subscribe(entity.id, this)
    }

    void render() {
        Transform transform = entity.getComponent<Transform>();
        if (transform == null)
            SpriteRendererManager.unsubscribe(entity.id);
        //render code
    }
private:
    Entity entity;
}