class SpriteRenderer {
public:
    Sprite sprite;
    Texture texture;
    SpriteRenderer(Entity* entity) {
        this.entity = entity;
        SpriteRendererManager.subscribe(entity.id, this)
    }

    render() {
        Transform transform = entity.getComponent<Transform>();
        if (transform == null)
            SpriteRendererManager.unsubscribe(entity.id);
        render()
    }
private:
    Entity entity;
}