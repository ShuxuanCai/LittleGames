#include <XEngine.h>

#include "Fighter.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Boss.h"
#include "BossBullets.h"

//Game setup
X::SoundId shootSound = 0;
X::SoundId backGroundSound = 0;
X::SoundId diedSound = 0;
X::SoundId bulletOnBossSound = 0;
X::SoundId bossBulletSound = 0;

//Set Background Page
X::TextureId startBackground = 0;
X::TextureId menuBackground = 0;
X::TextureId background = 0;

//Fighter
Fighter fighter;

//Bullets
constexpr int maxBullets = 30;
Bullet bullets[maxBullets];
int currentBulletIndex = 0;

//Boss Bullets
constexpr int maxBossBullets = 10;
BossBullets bossBullets[maxBossBullets];
int currentBossBulletsIndex = 0;
float bossBulletsSpawnDelay = 0.0f;

//Enemies
constexpr int maxEnemies = 100;
Enemy enemies[maxEnemies];
int currentEnemyIndex = 0;
float enemySpawnDelay = 0.0f;

//Boss
Boss boss;
int hp = 100;

//Score
int score = 0;

//Life
int life = 3;

//Bullets to boss
int count = 0;

//States
enum class GameState
{
	Start,
	Menu,
	Play,
	Pause,
	EndWin,
	EndLost
};

GameState currentState = GameState::Start;

void SpawnEnemy()
{
	if (!enemies[currentEnemyIndex].IsActive())
	{
		const float spawnX = static_cast<float>(X::GetScreenWidth()) * X::RandomFloat(0.1f, 0.9f);
		const float spawnY = -100.0f;
		enemies[currentEnemyIndex].Spawn({ spawnX,spawnY });

		currentEnemyIndex++;
		if (currentEnemyIndex == maxEnemies)
		{
			currentEnemyIndex = 0;
		}
	}
}

void SpawnBoss()
{
	if (!boss.IsActive())
	{
		boss.Spawn({ 400.0f, 110.0f });
	}
}

void SpawnBossBullets(const X::Math::Vector2& velocity)
{
	if (!bossBullets[currentBossBulletsIndex].IsActive())
	{
		const X::Math::Vector2 spawnPosition = boss.GetPosition();

		bossBullets[currentBossBulletsIndex].Fire(spawnPosition, velocity);

		currentBossBulletsIndex++;
		if (currentBossBulletsIndex == maxBossBullets)
		{
			currentBossBulletsIndex = 0;
		}
	}
}

void FireBullet(const X::Math::Vector2& velocity)
{
	if (!bullets[currentBulletIndex].IsActive())
	{
		const X::Math::Vector2 spawnPosition = fighter.GetPosition();

		bullets[currentBulletIndex].Fire(spawnPosition, velocity);

		currentBulletIndex++;
		if (currentBulletIndex == maxBullets)
		{
			currentBulletIndex = 0;
		}
	}
}

void CheckCollision()
{
	for (int i = 0; i < maxEnemies; ++i)
	{
		Enemy& currentEnemy = enemies[i];
		if (enemies[i].IsActive())
		{
			for (int j = 0; j < maxBullets; ++j)
			{
				Bullet& currentBullet = bullets[j];
				if (bullets[j].IsActive())
				{
					const X::Math::Circle enemyCircle = currentEnemy.GetBoundingCircle();
					const X::Math::Circle bulletCircle = currentBullet.GetBoundingCircle();

					const float distance = X::Math::Distance(enemyCircle.center, bulletCircle.center);
					const float radii = enemyCircle.radius + bulletCircle.radius;

					if (distance <= radii)
					{
						//Collision detected! Kill the enemy and the bullet!
						currentEnemy.Kill();
						currentBullet.Kill();

						break;
					}
				}
			}
		}
	}
}

void CheckCollionBossBulletFighter()
{
	for (int j = 0; j < maxBossBullets; ++j)
	{
		BossBullets& currentBossBullet = bossBullets[j];
		if (bossBullets[j].IsActive())
		{
			const X::Math::Circle fighterCircle = fighter.GetBoundingCircle();
			const X::Math::Circle bossBulletCircle = currentBossBullet.GetBoundingCircle();

			const float distance = X::Math::Distance(bossBulletCircle.center, fighterCircle.center);
			const float radii = bossBulletCircle.radius + fighterCircle.radius;

			if (distance <= radii)
			{
				currentBossBullet.Kill();
				fighter.Kill();
				X::PlaySoundOneShot(diedSound);
				life--;
			}
		}
	}
}

bool BulletsToBoss()
{
	for (int j = 0; j < maxBullets; ++j)
	{
		Bullet& currentBullet = bullets[j];
		if (bullets[j].IsActive())
		{
			if (boss.IsActive())
			{
				const X::Math::Circle bulletCircle = currentBullet.GetBoundingCircle();
				const X::Math::Circle bossCircle = boss.GetBoundingCircle();

				const float distance = X::Math::Distance(bulletCircle.center, bossCircle.center);
				const float radii = bulletCircle.radius + bossCircle.radius;

				if (distance <= radii)
				{
					currentBullet.Kill();
					++count;
					hp -= 10;
					X::PlaySoundOneShot(bulletOnBossSound);
					return true;
				}
			}
		}
	}
}

void CheckCollionBetweenBullets()
{
	for (int i = 0; i < maxBullets; ++i)
	{
		Bullet& currentBullet = bullets[i];
		if (bullets[i].IsActive())
		{
			for (int j = 0; j < maxBossBullets; ++j)
			{
				BossBullets& currentBossBullet = bossBullets[j];
				if (bossBullets[j].IsActive())
				{
					const X::Math::Circle bulletCircle = currentBullet.GetBoundingCircle();
					const X::Math::Circle bossBulletCircle = currentBossBullet.GetBoundingCircle();

					const float distance = X::Math::Distance(bossBulletCircle.center, bulletCircle.center);
					const float radii = bossBulletCircle.radius + bulletCircle.radius;

					if (distance <= radii)
					{
						//Collision detected! Kill the bullet and the boss bullet!
						currentBossBullet.Kill();
						currentBullet.Kill();

						break;
					}
				}
			}
		}
	}		
}

void FighterDead()
{
	for (int i = 0; i < maxEnemies; ++i)
	{
		Enemy& currentEnemy = enemies[i];
		if (enemies[i].IsActive())
		{
			const X::Math::Circle enemyCircle = currentEnemy.GetBoundingCircle();
			const X::Math::Circle fighterCircle = fighter.GetBoundingCircle();

			const float distance = X::Math::Distance(enemyCircle.center, fighterCircle.center);
			const float radii = enemyCircle.radius + fighterCircle.radius;

			if (distance <= radii)
			{
				currentEnemy.Kill();
				fighter.Kill();
				X::PlaySoundOneShot(diedSound);
				life--;
			}
		}
	}
}

bool CheckDistance()
{
	for (int i = 0; i < maxEnemies; ++i)
	{
		Enemy& currentEnemy = enemies[i];
		if (enemies[i].IsActive())
		{
			for (int j = 0; j < maxBullets; ++j)
			{
				Bullet& currentBullet = bullets[j];
				if (bullets[j].IsActive())
				{
					const X::Math::Circle enemyCircle = currentEnemy.GetBoundingCircle();
					const X::Math::Circle bulletCircle = currentBullet.GetBoundingCircle();

					const float distance = X::Math::Distance(enemyCircle.center, bulletCircle.center);
					const float radii = enemyCircle.radius + bulletCircle.radius;

					if (distance <= radii)
					{
						return true;
					}
				}
			}
		}
	}
}

void ShowScore()
{
	if (CheckDistance() == true || BulletsToBoss() == true)
	{
		score += 10;
	}

	std::string currentScore = "Score: " + std::to_string(score);
	X::DrawScreenText(currentScore.c_str(), 1000.0f, 30.0f, 30.0f, X::Colors::White);
}

void ShowLife()
{
	std::string currentLife = "Life: " + std::to_string(life);
	X::DrawScreenText(currentLife.c_str(), 1000.0f, 80.0f, 30.0f, X::Colors::White);
}

void GameInit()
{
	//Game setup
	X::SetBackgroundColor(X::Colors::Aqua);
	X::ShowSystemCursor(false);
	shootSound = X::LoadSound("photongun1.wav");
	backGroundSound = X::LoadSound("megamanx_title.wav");
	diedSound = X::LoadSound("explosion.wav");
	bulletOnBossSound = X::LoadSound("megamanx_blast.wav");
	bossBulletSound = X::LoadSound("megamanx_shot.wav");
	background = X::LoadTexture("space_menu.jpg");
	menuBackground = X::LoadTexture("space_background.jpg");
	startBackground = X::LoadTexture("start_page_background.jpg");

	//GameObject setup
	fighter.Load();
	boss.Load();

	for (int i = 0; i < maxBullets; ++i)
	{
		bullets[i].Load();
	}

	for (int i = 0; i < maxEnemies; ++i)
	{
		enemies[i].Load();
	}

	for (int i = 0; i < maxBossBullets; ++i)
	{
		bossBullets[i].Load();
	}
}

void GameStateStart(float deltaTime)
{
	X::DrawSprite(startBackground, { 0.0f, 0.0f }, 0.0f, X::Pivot::TopLeft);
	X::DrawScreenText("SPACE SHOOTER", 360.0f, 50.0f, 80.0f, X::Colors::White);
	X::DrawScreenText("PRESS ENTER TO PLAY", 380.0f, 180.0f, 50.0f, X::Colors::Red);
	X::DrawScreenText("MENU: M", 580.0f, 280.0f, 30.0f, X::Colors::White);

	hp = 100;
	score = 0;
	life = 3;
	count = 0;
	
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		currentState = GameState::Play;
	}

	if (X::IsKeyPressed(X::Keys::M))
	{
		currentState = GameState::Menu;
	}
}

void GameStateMenu(float deltaTime)
{
	X::DrawSprite(menuBackground, { 0.0f, 0.0f }, 0.0f, X::Pivot::TopLeft);
	X::DrawScreenText("MOVE : W, A, S, D", 10.0f, 50.0f, 40.0f, X::Colors::White);
	X::DrawScreenText("SHOOT: SPACE", 10.0f, 150.0f, 40.0f, X::Colors::White);
	X::DrawScreenText("PAUSE: TAB", 10.0f, 250.0f, 40.0f, X::Colors::White);
	X::DrawScreenText("BACKGROUND ON/OFF: O/P", 10.0f, 350.0f, 40.0f, X::Colors::White);
	X::DrawScreenText("PRESS ENTER TO PLAY", 10.0f, 500.0f, 80.0f, X::Colors::Red);
	
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		currentState = GameState::Play;
	}
}

void GameStatePlay(float deltaTime)
{
	X::DrawSprite(background, { 0.0f, 0.0f }, 0.0f, X::Pivot::TopLeft);

	if (X::IsKeyPressed(X::Keys::P))
	{
		X::StopSoundLoop(backGroundSound);
	}

	if (X::IsKeyPressed(X::Keys::O))
	{
		X::PlaySoundLoop(backGroundSound);
	}

	X::DrawScreenText("HelloSpaceShooter!", 10.0f, 10.0f, 30.0f, X::Colors::White);

	for (int i = 0; i < maxBullets; ++i)
	{
		bullets[i].Update(deltaTime);
		bullets[i].Render();
	}

	for (int i = 0; i < maxEnemies; ++i)
	{
		enemies[i].Update(deltaTime);
		enemies[i].Render();
	}

	for (int i = 0; i < maxBossBullets; ++i)
	{
		bossBullets[i].Update(deltaTime);
		bossBullets[i].Render();
	}

	fighter.Update(deltaTime);
	fighter.Render();

	//Fire
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		FireBullet({ 0.0f, -600.0f });
		X::PlaySoundOneShot(shootSound);
	}

	//Spawn enemies
	enemySpawnDelay -= deltaTime;
	if (enemySpawnDelay <= 0.0f)
	{
		SpawnEnemy();

		// Reset the spawn delay
		enemySpawnDelay = X::RandomFloat(0.5f, 1.5f);
	}

	ShowScore();
	ShowLife();

	CheckCollision();
	CheckCollionBetweenBullets();

	if (score >= 100)
	{
		if (X::IsKeyPressed(X::Keys::SPACE))
		{
			FireBullet({ -100.0f, -600.0f });
			FireBullet({ 100.0f, -600.0f });

			X::PlaySoundOneShot(shootSound);
		}
	}

	if (score >= 200)
	{
		fighter.mMoveSpeed = 600.0f;
	}

	if (fighter.IsActive() == false)
	{
		fighter.Spawn({ 640.0f, 500.0f });
	}

	if (score >= 50)
	{
		boss.Update(deltaTime);
		boss.Render();
		SpawnBoss();

		float x = boss.GetPosition().x - 40.0f;
		float y = boss.GetPosition().y;
		std::string currentHP = "HP: " + std::to_string(hp);
		X::DrawScreenText(currentHP.c_str(), x, y, 30.0f, X::Colors::Red);

		for (int i = 0; i < maxBossBullets; ++i)
		{
			bossBullets[i].Update(deltaTime);
			bossBullets[i].Render();
		}

		bossBulletsSpawnDelay -= deltaTime;
		if (bossBulletsSpawnDelay <= 0.0f)
		{
			SpawnBossBullets({ 0.0f, 200.0f });
			SpawnBossBullets({ -200.0f, 200.0f });
			SpawnBossBullets({ 200.0f, 200.0f });
			SpawnBossBullets({ -400.0f, 200.0f });
			SpawnBossBullets({ 400.0f, 200.0f });
			X::PlaySoundOneShot(bossBulletSound);
			bossBulletsSpawnDelay = 1.0f;
		}

		if (count >= 10)
		{
			boss.Kill();
			currentState = GameState::EndWin;
		}
	}

	if (X::IsKeyPressed(X::Keys::TAB))
	{
		currentState = GameState::Pause;
	}

	FighterDead();
	CheckCollionBossBulletFighter();

	if (life <= 0)
	{
		currentState = GameState::EndLost;
	}
}

void GameStatePause(float deltaTime)
{
	X::SetBackgroundColor(X::Colors::Black);
	X::DrawScreenText("PAUSE", 520.0f, 290.0f, 100.0f, X::Colors::White);
	X::StopSoundLoop(backGroundSound);
	std::string currentScore = "Score: " + std::to_string(score);
	X::DrawScreenText(currentScore.c_str(), 1000.0f, 30.0f, 30.0f, X::Colors::White);
	std::string currentLife = "Life: " + std::to_string(life);
	X::DrawScreenText(currentLife.c_str(), 1000.0f, 80.0f, 30.0f, X::Colors::White);
	X::DrawScreenText("HelloSpaceShooter!", 10.0f, 10.0f, 30.0f, X::Colors::White);

	if (X::IsKeyPressed(X::Keys::TAB))
	{
		currentState = GameState::Play;
	}
}

void GameStateEndWin(float deltaTime)
{
	for (int i = 0; i < maxBossBullets; ++i)
	{
		bossBullets[i].Kill();
	}

	for (int i = 0; i < maxBullets; ++i)
	{
		bullets[i].Kill();
	}

	for (int i = 0; i < maxEnemies; ++i)
	{
		enemies[i].Kill();
	}

	boss.Kill();

	X::SetBackgroundColor(X::Colors::Black);
	X::DrawScreenText("WIN!", 550.0f, 200.0f, 100.0f, X::Colors::Red);
	std::string currentScore = "Your Score is " + std::to_string(score);
	X::DrawScreenText(currentScore.c_str(), 470.0f, 400.0f, 40.0f, X::Colors::White);
	X::DrawScreenText("RESTART: ENTER", 500.0f, 500.0f, 40.0f, X::Colors::White);
	X::DrawScreenText("EXIT: ESCAPE", 510.0f, 600.0f, 40.0f, X::Colors::White);

	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		currentState = GameState::Start;
	}

}

void GameStateEndLost(float deltaTime)
{
	for (int i = 0; i < maxBossBullets; ++i)
	{
		bossBullets[i].Kill();
	}

	for (int i = 0; i < maxBullets; ++i)
	{
		bullets[i].Kill();
	}

	for (int i = 0; i < maxEnemies; ++i)
	{
		enemies[i].Kill();
	}

	boss.Kill();

	X::SetBackgroundColor(X::Colors::Black);
	X::DrawScreenText("Game Over!", 400.0f, 200.0f, 100.0f, X::Colors::Red);
	std::string currentScore = "Your Score is " + std::to_string(score);
	X::DrawScreenText(currentScore.c_str(), 470.0f, 400.0f, 40.0f, X::Colors::White);
	X::DrawScreenText("RESTART: ENTER", 500.0f, 500.0f, 40.0f, X::Colors::White);
	X::DrawScreenText("EXIT: ESCAPE", 510.0f, 600.0f, 40.0f, X::Colors::White);
	
	if (X::IsKeyPressed(X::Keys::ENTER))
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
	case GameState::Menu:
		GameStateMenu(deltaTime);
		break;
	case GameState::Play:
		GameStatePlay(deltaTime);
		break;
	case GameState::Pause:
		GameStatePause(deltaTime);
		break;
	case GameState::EndWin:
		GameStateEndWin(deltaTime);
		break;
	case GameState::EndLost:
		GameStateEndLost(deltaTime);
		break;
	default:
		break;
	}

	//Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	fighter.Unload();
	boss.Unload();

	for (int i = 0; i < maxBullets; ++i)
	{
		bullets[i].Unload();
	}

	for (int i = 0; i < maxEnemies; ++i)
	{
		enemies[i].Unload();
	}

	for (int i = 0; i < maxBossBullets; ++i)
	{
		bossBullets[i].Unload();
	}
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