#include "MatchManager.h"
#include "SpriteRendererManager.h"
#include "Player.h"

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
	Shader ourShader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());

	MatchManager::CreateMap(&ourShader);
	MatchManager::CreateBattlers(&ourShader);
}

void MatchManager::CreateMap(Shader *shader)
{
	//Sprites for testing d
	GLuint iceTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/IceTile.png"));
	GLuint snowTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/SnowTile.png"));
	//Shader ourShader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());

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
			GameObject* tile = new GameObject();
			tile->AddComponent<SpriteRenderer*>(new SpriteRenderer(tile));
			SpriteRenderer* spriteRenderer = tile->GetComponent<SpriteRenderer*>();
			spriteRenderer->SetActiveTexture(textureToUse);
			spriteRenderer->SetActiveShader(shader);
			tile->GetComponent<Transform*>()->setPosition(leftBounding + x + 0.5, bottomBounding + y + 0.5);
		}
	}
}

void MatchManager::CreateBattlers(Shader *shader)
{
	GLuint characterTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));

	//chensPlayer1 = new Player(&ourShader, texture);
	//Transform* transform = (Transform*)chensPlayer1->GetComponent<Transform*>();
	//transform->setPosition(-7, 2);
	//InputManager* inputManager = InputManager::GetInstance();
	//transform->setScale(3.0f);

	//snowBall1 = new Player(&ourShader, iceTexture);
	//transform = (Transform*)snowBall1->GetComponent<Transform*>();
	//transform->setPosition(-7, 0);
	//inputManager = InputManager::GetInstance();
	//transform->setScale(1.0f);

	////GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character2.png"));
	//chensPlayer2 = new Player(&ourShader, texture2);
	//transform = (Transform*)chensPlayer2->GetComponent<Transform*>();
	//transform->setPosition(10, 2);
	//inputManager = InputManager::GetInstance();
	//transform->setScale(3.0f);

	//snowBall2 = new Player(&ourShader, iceTexture);
	//transform = (Transform*)snowBall2->GetComponent<Transform*>();
	//transform->setPosition(10, 0);
	//inputManager = InputManager::GetInstance();
	//transform->setScale(1.0f);

	// Team 1
	// Player
	Battler* playerOne = new Battler(1, shader, characterTexture);
	Player* playerOneStats = new Player();
	Transform* playerOneTransform = (Transform*)playerOne->GetComponent<Transform*>();
	playerOneTransform->setPosition(-7, 2);
	playerOneTransform->setScale(3.0f);
	playerOne->AddComponent<Player*>(playerOneStats);
	RegisterCharacter(playerOne);
	//AI
	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		Battler* unit = new Battler(1, shader, characterTexture);
		AI* unitAI = (AI*)new Component(unit);
		unit->AddComponent<AI*>(unitAI);
		RegisterCharacter(unit);
		aiUnits.push_back(unitAI);
	}

	//Team 2
	Battler* playerTwo = new Battler(2, shader, characterTexture);
	Player* playerTwoStats = new Player();
	Transform* playerTwoTransform = (Transform*)playerOne->GetComponent<Transform*>();
	playerOneTransform->setPosition(10, 2);
	playerOneTransform->setScale(3.0f);
	playerTwo->AddComponent<Player*>(playerTwoStats);
	RegisterCharacter(playerTwo);

	for (int i = 0; i < TEAM_SIZE - 1; ++i)
	{
		Battler* unit = new Battler(2, shader, characterTexture);
		AI* unitAI = (AI*)new Component(unit);
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