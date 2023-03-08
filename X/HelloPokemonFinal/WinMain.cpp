#include <XEngine.h>

#include "Camera.h"
#include "TileMap.h"
#include "Link.h"
#include "Pokemon1.h"
#include "Pokemon2.h"
#include "Pokemon3.h"
#include "Fire.h"
#include "ElectroBall.h"

Link link;
Pokemon1 pokemonAI;
Pokemon2 pokemonPlayer;
Pokemon3 pokemonAI2;

float spawnFire = 3.0f;
float spawnTime = 3.0f;

X::TextureId battleBackground = 0;
X::TextureId dialogueBackground = 0;
X::TextureId emberBackground = 0;
X::TextureId electroBallBackground = 0;
X::TextureId startPageBackground = 0;
X::TextureId winPageBackground = 0;
X::TextureId gameOverBackground = 0;

X::SoundId pokemonHeal = 0;
X::SoundId pokemonBattle = 0;
X::SoundId pokemonWin = 0;
X::SoundId pokemonGamePlay = 0;

std::string text1 = "Wild Pikachu Appears...";
std::string text2 = "Wild Electabuzz Appears...";

Fire fire;
ElectroBall electroBall;

int playerHp;
int AIHp;
int AI2Hp;

int runTime = 0;
int runTimeNumber = 6;

enum class GameState
{
	Start,
	Play,
	Battle1,
	Battle2,
	Win,
	GameOver
};

GameState currentState = GameState::Start;

void BeAttacked()
{
	if (pokemonPlayer.IsActive())
	{
		if (electroBall.IsActive())
		{
			const X::Math::Circle pokemonPlayerCircle = pokemonPlayer.GetBoundingCircle();
			const X::Math::Circle eletroBallCircle = electroBall.GetBoundingCircle();

			const float distance = X::Math::Distance(pokemonPlayerCircle.center, eletroBallCircle.center);
			const float radii = pokemonPlayerCircle.radius + eletroBallCircle.radius;

			if (distance <= radii)
			{
				int random = X::Random(0, 10);
				electroBall.Kill();
				int randomAttack = X::Random(10, 15);
				playerHp -= randomAttack;
				if (random <= 3)
				{
					text1 = "Charizard dodges the attack";
					text2 = "Charizard dodges the attack";
					playerHp += randomAttack;
				}
			}
		}
	}
}

void SpawnEletroBall(X::Math::Vector2 velocity)
{
	if (!electroBall.IsActive())
	{
		if (pokemonAI.IsActive())
		{
			const X::Math::Vector2 spawnPosition = pokemonAI.GetPosition();
			electroBall.Fires(spawnPosition, velocity);
		}
		else
		{
			const X::Math::Vector2 spawnPosition2 = pokemonAI2.GetPosition();
			electroBall.Fires(spawnPosition2, velocity);
		}
	}
}

void SpawnFires(X::Math::Vector2 velocity)
{
	if (!fire.IsActive())
	{
		if (pokemonAI.IsActive())
		{
			const X::Math::Vector2 spawnPosition = pokemonPlayer.GetPosition();
			fire.Fires(spawnPosition, velocity);
		}
		else if(pokemonAI2.IsActive())
		{
			const X::Math::Vector2 spawnPosition2 = pokemonPlayer.GetPosition();
			fire.Fires(spawnPosition2, velocity);
		}
	}
}

void ShowPlayerHp()
{
	if (playerHp <= 0)
		playerHp = 0;
	std::string currentHp = "HP: " + std::to_string(playerHp);
	X::Math::Vector2 pos = pokemonPlayer.GetPosition();
	X::DrawScreenText(currentHp.c_str(), pos.x + 50.0f, pos.y - 220.0f, 30.0f, X::Colors::Red);
}

void CheckAttack()
{
	if (pokemonAI.IsActive())
	{
		if (fire.IsActive())
		{
			const X::Math::Circle pokemonAICircle = pokemonAI.GetBoundingCircle();
			const X::Math::Circle fireCircle = fire.GetBoundingCircle();

			const float distance = X::Math::Distance(pokemonAICircle.center, fireCircle.center);
			const float radii = pokemonAICircle.radius + fireCircle.radius;

			if (distance <= radii)
			{
				int random = X::Random(0, 10);
				fire.Kill();
				int randomAttack = X::Random(50, 70);
				AIHp -= randomAttack;
				text1 = "Pikachu uses Eletro Ball!";
				SpawnEletroBall({ -200.0f, 100.0f });
				if (random <= 3)
				{
					text1 = "Pikachu dodges the attack";
					AIHp += randomAttack;
				}
			}
		}
	}
}

void CheckAttack2()
{
	if (pokemonAI2.IsActive())
	{
		if (fire.IsActive())
		{
			const X::Math::Circle pokemonAI2Circle = pokemonAI2.GetBoundingCircle();
			const X::Math::Circle fireCircle = fire.GetBoundingCircle();

			const float distance = X::Math::Distance(pokemonAI2Circle.center, fireCircle.center);
			const float radii = pokemonAI2Circle.radius + fireCircle.radius;

			if (distance <= radii)
			{
				int random = X::Random(0, 10);
				fire.Kill();
				int randomAttack = X::Random(50, 70);
				AI2Hp -= randomAttack;
				text2 = "Electabuzz uses Eletro Ball!";
				SpawnEletroBall({ -200.0f, 100.0f });
				if (random <= 3)
				{
					text2 = "Electabuzz dodges the attack";
					AI2Hp += randomAttack;
				}
			}
		}
	}
}

void ShowAIHp()
{
	CheckAttack();
	if (AIHp <= 0)
		AIHp = 0;
	std::string currentHp = "HP: " + std::to_string(AIHp);
	X::Math::Vector2 pos = pokemonAI.GetPosition();
	X::DrawScreenText(currentHp.c_str(), pos.x + 10.0f, pos.y - 170.0f, 30.0f, X::Colors::Red);
}

void ShowAI2Hp()
{
	CheckAttack2();
	if (AI2Hp <= 0)
		AI2Hp = 0;
	std::string currentHp = "HP: " + std::to_string(AI2Hp);
	X::Math::Vector2 pos = pokemonAI2.GetPosition();
	X::DrawScreenText(currentHp.c_str(), pos.x + 10.0f, pos.y - 170.0f, 30.0f, X::Colors::Red);
}

void ShowNumber()
{
	std::string number = "Number of mushroom: " + std::to_string(link.number) + "/3";
	X::DrawScreenText(number.c_str(), 50.0f, 50.0f, 30.0f, X::Colors::Red);
}

void RunTime()
{
	std::string run = "Run time: " + std::to_string(runTime) + "/7";
	X::DrawScreenText(run.c_str(), 50.0f, 100.0f, 30.0f, X::Colors::Red);
}

void Heal()
{
	std::string run = "Press R to heal Pokemon";
	X::DrawScreenText(run.c_str(), 50.0f, 150.0f, 30.0f, X::Colors::Red);
}

void GameInit()
{
	Camera::StaticInitialize();

	link.Load();
	link.SetPosition({ 300.0f,300.0f });
	
	fire.Load();
	electroBall.Load();

	pokemonAI.Load();
	pokemonAI2.Load();
	pokemonPlayer.Load();

	spawnFire = 3.0f;
	spawnTime = 3.0f;

	TileMap::StaticInitialize();
	TileMap::Get().Load("level_01.txt", "tileset_01.txt");

	battleBackground = X::LoadTexture("BattleBackground.png");
	dialogueBackground = X::LoadTexture("dia.png");
	startPageBackground = X::LoadTexture("startPage.jpg");
	winPageBackground = X::LoadTexture("winPage.jpg");
	gameOverBackground = X::LoadTexture("GameOver.jpg");

	pokemonHeal = X::LoadSound("pokemon_heal.wav");
	pokemonBattle = X::LoadSound("pokemon_battle.wav");
	pokemonWin = X::LoadSound("pokemon_win.wav");
	pokemonGamePlay = X::LoadSound("pokemon_gameplay.wav");

	playerHp = pokemonPlayer.GetHp();
	AIHp = pokemonAI.GetHp();
}

void GameStateStart(float deltaTime)
{
	link.SetPosition({ 300.0f,300.0f });
	link.result = false;
	link.number = 0;
	runTime = 0;
	playerHp = 100;

	TileMap::Get().Load("level_01.txt", "tileset_01.txt");

	X::DrawSprite(startPageBackground, { 0.0f, 0.0f }, 0.0f, X::Pivot::TopLeft);
	X::DrawScreenText("PRESS ENTER TO PLAY", 400.0f, 500.0f, 50.0f, X::Colors::Red);
	
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		currentState = GameState::Play;
	}
}

void GameStatePlay(float deltaTime)
{
	link.probability = 0.0f;
	spawnTime = 3.0f;
	AIHp = 100;
	AI2Hp = 100;
	electroBall.Kill();
	fire.Kill();

	X::PlaySoundLoop(pokemonGamePlay);

	TileMap::Get().Update(deltaTime);
	link.Update(deltaTime);

	Camera::Get().SetViewBound(TileMap::Get().GetBound());
	Camera::Get().SetViewPosition(link.GetPosition());

	TileMap::Get().Render();
	link.Render();

	ShowNumber();
	RunTime();
	Heal();

	if (X::IsKeyDown(X::Keys::R))
	{
		playerHp = 100;
		X::PlaySoundOneShot(pokemonHeal);
	}

	if (link.probability > 99.0f && link.probability < 99.5f)
	{
		X::StopSoundLoop(pokemonGamePlay);
		currentState = GameState::Battle1;
	}

	if (link.probability >= 99.5f)
	{
		X::StopSoundLoop(pokemonGamePlay);
		currentState = GameState::Battle2;
	}

	if (link.result == true && link.number == 3)
	{
		X::DrawSprite(dialogueBackground, { 1280.0f, 720.0f }, 0.0f, X::Pivot::BottomRight);
		X::DrawScreenText("Congratulate! You found 3 mushroom! You win!", 500.0f, 500.0f, 30.0f, X::Colors::Blue);
		spawnFire -= deltaTime;
		if (spawnFire <= 0.0f)
		{
			currentState = GameState::Win;
		}
	}
}

void GameStateBattle1(float deltaTime)
{
	X::DrawSprite(battleBackground, { 0.0f, 0.0f }, 0.0f, X::Pivot::TopLeft);
	X::PlaySoundLoop(pokemonBattle);

	pokemonAI.Update(deltaTime);
	pokemonAI.Render();

	fire.Update(deltaTime);
	fire.Render();

	electroBall.Update(deltaTime);
	electroBall.Render();

	pokemonPlayer.Update(deltaTime);
	pokemonPlayer.Render();

	pokemonAI.Spawn({ 950.0f, 180.0f });
	pokemonPlayer.Spawn({ 350.0f, 450.0f });

	X::DrawSprite(dialogueBackground, { 1280.0f, 720.0f }, 0.0f, X::Pivot::BottomRight);
	X::DrawScreenText(text1.c_str(), 500.0f, 500.0f, 30.0f, X::Colors::White);

	ShowAIHp();
	ShowPlayerHp();

	if (X::IsKeyDown(X::Keys::J))
	{
		text1 = "1. FIGHT 2. RUN";
	}

	if (!electroBall.IsActive())
	{
		if (X::IsKeyDown(X::Keys::ONE))
		{
			text1 = "Charizard uses ember!";
			SpawnFires({ 200.0f, -100.0f });
			CheckAttack();
		}
	}
		
	BeAttacked();

	if (AIHp <= 0)
	{
		X::StopSoundLoop(pokemonBattle);
		text1 = "Pikachu is Fainting, you win!";
		X::PlaySoundLoop(pokemonWin);
		pokemonAI.Kill();
		fire.Kill();
		electroBall.Kill();
		spawnTime -= deltaTime;
		if (spawnTime <= 0.0f)
		{
			X::StopSoundLoop(pokemonWin);
			currentState = GameState::Play;
		}
	}

	if (playerHp <= 0)
	{
		text1 = "Charizard is Fainting, you lose!";
		pokemonPlayer.Kill();
		fire.Kill();
		electroBall.Kill();
		spawnTime -= deltaTime;
		if (spawnTime <= 0.0f)
		{
			currentState = GameState::GameOver;
		}
	}

	if (X::IsKeyPressed(X::Keys::TWO) && runTime > runTimeNumber)
	{
		text1 = "You have run away 7 times, you can't run away.";
	}

	if (X::IsKeyPressed(X::Keys::TWO) && runTime <= runTimeNumber)
	{
		runTime++;
		currentState = GameState::Play;
		X::StopSoundLoop(pokemonBattle);
	}
}

void GameStateBattle2(float deltaTime)
{
	X::DrawSprite(battleBackground, { 0.0f, 0.0f }, 0.0f, X::Pivot::TopLeft);
	X::PlaySoundLoop(pokemonBattle);

	pokemonAI2.Update(deltaTime);
	pokemonAI2.Render();

	fire.Update(deltaTime);
	fire.Render();

	electroBall.Update(deltaTime);
	electroBall.Render();

	pokemonPlayer.Update(deltaTime);
	pokemonPlayer.Render();

	pokemonAI2.Spawn({ 950.0f, 180.0f });
	pokemonPlayer.Spawn({ 350.0f, 450.0f });

	X::DrawSprite(dialogueBackground, { 1280.0f, 720.0f }, 0.0f, X::Pivot::BottomRight);
	X::DrawScreenText(text2.c_str(), 500.0f, 500.0f, 30.0f, X::Colors::White);

	ShowAI2Hp();
	ShowPlayerHp();

	if (X::IsKeyDown(X::Keys::J))
	{
		text2 = "1. FIGHT 2. RUN";
	}

	if (!electroBall.IsActive())
	{
		if (X::IsKeyDown(X::Keys::ONE))
		{
			text2 = "Charizard uses ember!";
			SpawnFires({ 200.0f, -100.0f });
			CheckAttack2();
		}
	}

	BeAttacked();

	if (AI2Hp <= 0)
	{
		X::StopSoundLoop(pokemonBattle);
		text2 = "Electabuzz is Fainting, you win!";
		X::PlaySoundLoop(pokemonWin);
		pokemonAI2.Kill();
		fire.Kill();
		electroBall.Kill();
		spawnTime -= deltaTime;
		if (spawnTime <= 0.0f)
		{
			X::StopSoundLoop(pokemonWin);
			currentState = GameState::Play;
		}
	}

	if (playerHp <= 0)
	{
		text2 = "Charizard is Fainting, you lose!";
		pokemonPlayer.Kill();
		fire.Kill();
		electroBall.Kill();
		spawnTime -= deltaTime;
		if (spawnTime <= 0.0f)
		{
			currentState = GameState::GameOver;
		}
	}

	if (X::IsKeyPressed(X::Keys::TWO) && runTime > runTimeNumber)
	{
		text2 = "You have run away 7 times, you can't run away.";
	}

	if (X::IsKeyPressed(X::Keys::TWO) && runTime <= runTimeNumber)
	{
		runTime++;
		currentState = GameState::Play;
		X::StopSoundLoop(pokemonBattle);
	}
}

void GameStateWinPage(float deltaTime)
{
	X::DrawSprite(winPageBackground, { 0.0f, 0.0f }, 0.0f, X::Pivot::TopLeft);

	X::DrawScreenText("Restart: ENTER", 600.0f, 400.0f, 30.0f, X::Colors::Red);
	X::DrawScreenText("EIXT: ESCAPE", 610.0f, 500.0f, 30.0f, X::Colors::Red);
	if (X::IsKeyDown(X::Keys::ENTER))
	{
		currentState = GameState::Start;
	}
}

void GameStateGameOver(float deltaTime)
{
	X::DrawSprite(gameOverBackground, { 0.0f, 0.0f }, 0.0f, X::Pivot::TopLeft);

	X::DrawScreenText("Restart: ENTER", 550.0f, 600.0f, 30.0f, X::Colors::Red);
	X::DrawScreenText("EIXT: ESCAPE", 560.0f, 650.0f, 30.0f, X::Colors::Red);
	if (X::IsKeyDown(X::Keys::ENTER))
	{
		currentState = GameState::Start;
	}
}

bool GameLoop(float deltaTime)
{
	switch (currentState)
	{
	case GameState::Start:
		GameStateStart(deltaTime);
		break;
	case GameState::Play:
		GameStatePlay(deltaTime);
		break;
	case GameState::Battle1:
		GameStateBattle1(deltaTime);
		break;
	case GameState::Battle2:
		GameStateBattle2(deltaTime);
		break;
	case GameState::Win:
		GameStateWinPage(deltaTime);
		break;
	case GameState::GameOver:
		GameStateGameOver(deltaTime);
		break;
	default:
		break;
	}

	// Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	TileMap::Get().Unload();
	TileMap::StaticTerminate();

	link.Unload();

	Camera::StaticTerminate();

	pokemonAI.Unload();
	pokemonAI2.Unload();
	pokemonPlayer.Unload();

	fire.Unload();
	electroBall.Unload();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;
}