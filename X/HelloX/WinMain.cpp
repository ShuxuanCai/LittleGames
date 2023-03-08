#include <XEngine.h>

X::TextureId textureId1 = 0;
X::TextureId textureId2 = 0;
X::Math::Vector2 position1;
X::Math::Vector2 position2;
X::Math::Vector2 velocity1;
X::Math::Vector2 velocity2;
//float moveSpeed = 0.0f;

void GameInit()
{
	//Load a texture - this uses the correct file path already
	//from the assets folder, use whatever image you want
	textureId1 = X::LoadTexture("mario.png"); // Load mario image
	textureId2 = X::LoadTexture("pikachu.png"); // Load pikachu image

	//Init starting values
	position1 = { 300.0f, 400.0f };
	position2 = { 800.0f, 400.0f };
	//moveSpeed = 300.0f;
	velocity1 = { 150.0f, -150.0f };
	velocity2 = { -200.0f, -200.0f };
}

//void MoveWithWASD(float deltaTime)
//{
//	//Up
//	if (X::IsKeyDown(X::Keys::W))
//	{
//		position.y -= moveSpeed * deltaTime;
//	}
//
//	//Left
//	if (X::IsKeyDown(X::Keys::A))
//	{
//		position.x -= moveSpeed * deltaTime;
//	}
//
//	//Down
//	if (X::IsKeyDown(X::Keys::S))
//	{
//		position.y += moveSpeed * deltaTime;
//	}
//
//	//Right
//	if (X::IsKeyDown(X::Keys::D))
//	{
//		position.x += moveSpeed * deltaTime;
//	}
//}

bool GameLoop(float deltaTime)
{
	////Movement
	//MoveWithWASD(deltaTime);

	//Move init of Mario
	position1 += velocity1 * deltaTime;
	//Move init of Pikachu
	position2 += velocity2 * deltaTime;

	//Screen bounds
	const uint32_t screenWidth = X::GetScreenWidth();
	const uint32_t screenHeight = X::GetScreenHeight();
	const float halfMarioWidth = X::GetSpriteWidth(textureId1) / 2.0f;
	const float halfMarioHeight = X::GetSpriteHeight(textureId1) / 2.0f;
	const float halfPikachuWidth = X::GetSpriteWidth(textureId2) / 2.0f;
	const float halfPikachuHeight = X::GetSpriteHeight(textureId2) / 2.0f;

	//Right side of screen of Mario
	if (position1.x > screenWidth - halfMarioWidth)
	{
		position1.x = screenWidth - halfMarioWidth;
		velocity1.x = -150.0f;
	}

	//Right side of screen of Pikachu
	if (position2.x > screenWidth - halfPikachuWidth)
	{
		position2.x = screenWidth - halfPikachuWidth;
		velocity2.x = -200.0f;
	}

	//Left side of screen of Mario
	if (position1.x < halfMarioWidth)
	{
		position1.x = halfMarioWidth;
		velocity1.x = 150.0f;
	}

	//Left side of screen of Pikachu
	if (position2.x < halfPikachuWidth)
	{
		position2.x = halfPikachuWidth;
		velocity2.x = 200.0f;
	}

	//Bottom side of screen of Mario
	if (position1.y > screenHeight - halfMarioHeight)
	{
		position1.y = screenHeight - halfMarioHeight;
		velocity1.y = -150.0f;
	}

	//Bottom side of screen of Pikachu
	if (position2.y > screenHeight - halfPikachuHeight)
	{
		position2.y = screenHeight - halfPikachuHeight;
		velocity2.y = -200.0f;
	}

	//Top side of screen of Mario
	if (position1.y < halfMarioHeight)
	{
		position1.y = halfMarioHeight;
		velocity1.y = 150.0f;
	}

	//Top side of screen of Pikachu
	if (position2.y < halfPikachuHeight)
	{
		position2.y = halfPikachuHeight;
		velocity2.y = 200.0f;
	}

	//HomeWork:
	// Make this texture move by itself and bounce off the border.
	// Once it hits the border, it should reverse direction.
	// Extra challenge: make two separate sprites do this! Start in two different locations
	//                  with different speeds!
	// Hint: use "X::Math::Vector2 velocity" , and "position += velocity * deltaTime;"
	// For handing in - only include source files required(.cpp/.h files)


	//Rendering
	X::DrawSprite(textureId1, position1);
	X::DrawSprite(textureId2, position2);

	//Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{

}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;
}