#include "MenuScene_Alpha.h"
#include "SpriteRendererManager.h"
#include "HelperFunctions.h"
#include "SharedConstants.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Transform.h"

void MenuScene_Alpha::OnStart() {
	ourShader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/voxel.fs").c_str());
    GLuint backgroundTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Sky.png"));
    menuBackground = new GameObject();
    menuBackground->AddComponent<SpriteRenderer*>(new SpriteRenderer(menuBackground));
    menuBackground->GetComponent<SpriteRenderer*>()->SetActiveSprite(new Sprite(backgroundTexture));
    menuBackground->GetComponent<SpriteRenderer*>()->SetActiveShader(ourShader);
    menuBackground->GetComponent<Transform*>()->setScale(GAME_WIDTH);
    menuBackground->GetComponent<Transform*>()->setZ(-2);

    GLuint foregroundTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/ForegroundTrees.png"));
    menuForeground = new GameObject();
    menuForeground->AddComponent<SpriteRenderer*>(new SpriteRenderer(menuForeground));
    menuForeground->GetComponent<SpriteRenderer*>()->SetActiveSprite(new Sprite(foregroundTexture));
    menuForeground->GetComponent<SpriteRenderer*>()->SetActiveShader(ourShader);
    menuForeground->GetComponent<Transform*>()->setScale(GAME_WIDTH);
    menuForeground->GetComponent<Transform*>()->setZ(-1);
    menuForeground->GetComponent<Transform*>()->setY(-getGameHeight()/5.0f);

    GLuint titleTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Title.png"));
    menuTitle = new GameObject();
    menuTitle->AddComponent<SpriteRenderer*>(new SpriteRenderer(menuTitle));
    menuTitle->GetComponent<SpriteRenderer*>()->SetActiveSprite(new Sprite(titleTexture));
    menuTitle->GetComponent<SpriteRenderer*>()->SetActiveShader(ourShader);
    menuTitle->GetComponent<Transform*>()->setScale(GAME_WIDTH / 1.25f);
    menuTitle->GetComponent<Transform*>()->setY(getGameTopY() - getGameHeight() / 4.0f);
}

void MenuScene_Alpha::OnUpdate() {

}

void MenuScene_Alpha::OnEnd() {

}