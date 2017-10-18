#include "MatchManager.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "HelperFunctions.h"
#include "UserDefinedRenderLayers.h"
#include "Transform.h"
#include "Player.h"
#include "Sender.h"

//Statics must be given definitions
MatchManager* MatchManager::instance;

MatchManager* MatchManager::GetInstance() 
{
	if (instance == NULL)
		instance = new MatchManager();
	return instance;
}

MatchManager::MatchManager()
{

}


MatchManager::~MatchManager()
{

}

bool MatchManager::RegisterCharacter(Battler *character)
{
	if (character->teamID == 1)
	{
		teamOne.push_back(character);
	}
	else if (character->teamID == 2)
	{
		teamTwo.push_back(character);
	}
	else
	{
		return false;
	}

	return true;
}

void MatchManager::StartGame()
{

}

void MatchManager::CreateMap(Shader *ourShader, GLuint snowTexture, GLuint iceTexture)
{
	float width = getGameWidth();
	float height = getGameHeight();
	float leftBounding = getGameLeftX();
	float bottomBounding = getGameBottomY();

	//Setup Tiles
	for (int x = 0; x < width; x++) {
		GLuint textureToUse = snowTexture;
		if (x >= width * 0.4f && x <= width * 0.6f) {
			textureToUse = iceTexture;
		}
		for (int y = 0; y < height; y++) {
			GameObject* tile = new GameObject(false);
			tile->AddComponent<SpriteRenderer*>(new SpriteRenderer(tile));
			SpriteRenderer* spriteRenderer = tile->GetComponent<SpriteRenderer*>();
			spriteRenderer->SetActiveSprite((ISprite*)new Sprite(textureToUse));
			spriteRenderer->SetActiveShader(ourShader);
			spriteRenderer->SetLayer(RENDER_LAYER_BACKGROUND);
			tile->GetComponent<Transform*>()->setPosition(leftBounding + x + 0.5, bottomBounding + y + 0.5, -1.0f);
		}
	}
}

void MatchManager::CreateBattlers(Shader *ourShader, GLuint characterTexture, GLuint spriteSheetTexture)
{
	// Team 1
	// Player
	Battler* playerOne = new Battler(1, ourShader, characterTexture);
	Player* playerOneStats = new Player(playerOne, SDLK_a, SDLK_d,SDLK_w,SDLK_s,SDLK_b);
	playerOne->AddComponent<Player*>(playerOneStats);
	Transform* playerOneTransform = (Transform*)playerOne->GetComponent<Transform*>();
	playerOneTransform->setScale(2.0f);
	playerOneTransform->setPosition(-7, 2);
	RegisterCharacter(playerOne);

	//spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(spriteSheetTexture, 5, 3, 1));
	//playerOneTransform->setRotation(-90.0f); //Spritesheet is 90 degrees off

	//AI
	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		Battler* unit = new Battler(1, ourShader, characterTexture);
		AI* unitAI = new AI(unit);
		unit->AddComponent<AI*>(unitAI);
		RegisterCharacter(unit);
		aiUnits.push_back(unitAI);
	}

	//Team 2
	Battler* playerTwo = new Battler(2, ourShader, characterTexture);
	Player* playerTwoStats = new Player(playerTwo, SDLK_4, SDLK_6, SDLK_8, SDLK_5, SDLK_n);
	playerTwo->AddComponent<Player*>(playerTwoStats);
	Transform* playerTwoTransform = (Transform*)playerTwo->GetComponent<Transform*>();
	playerTwoTransform->setScale(2.0f);
	playerTwoTransform->setPosition(10, 2);
	RegisterCharacter(playerTwo);
	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		Battler* unit = new Battler(2, ourShader, characterTexture);
		AI* unitAI = new AI(unit);
		unit->AddComponent<AI*>(unitAI);
		RegisterCharacter(unit);
		aiUnits.push_back(unitAI);
	}

	// Initialize our AI
	for (int i = 0; i < aiUnits.size(); ++i)
	{
		aiUnits[i]->Init();
	}
}

std::vector<Battler*> MatchManager::GetTeam(int teamID)
{
	if (teamID == 1)
	{
		return teamOne;
	}
	else
	{
		return teamTwo;
	}
}