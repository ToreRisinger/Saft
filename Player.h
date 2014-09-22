class Player
{
public:
	Player(Level* level);
	~Player();

	void render();
	void update();
	void input(Input* input);
	void init();
	bool isDead();

	int getX();
	int getY();

	enum jumpDirection
	{
		UP,
		LEFT,
		RIGHT
	};

private:
	void collision();

	Level* level = nullptr;
	Texture* texture = nullptr;
	int speed;
	int airSpeed;
	int x;
	int y;
	double gravity;
	int width;
	int height;
	double yVel;
	double xVel;
	double jumpPower;
	bool dead;
	bool onFloor;
	bool canJump;
	bool doubleJump;
	jumpDirection jumpDir;
};

Player::Player(Level* l)
{
	level = l;
	texture = new Texture("default_texture");
	init();
}

Player::~Player()
{
	delete texture;
}

void Player::init()
{
	speed = 10;
	airSpeed = 5;
	gravity = 0.4;
	jumpPower = 8;
	doubleJump = true;

	width = 16;
	height = 16;
	x = 304;
	y = 100;
	xVel = 0;
	yVel = 0;
	dead = false;
	onFloor = false;
	canJump = false;
	jumpDir = UP;
}

void Player::render()
{
	texture->render(304, y-height, width, height);
}

void Player::update()
{
	yVel = yVel - gravity;

	collision();

	y = y - yVel;
	x = x + xVel;

	if (y > 530) dead = true;
}

void Player::input(Input* input)
{
	if (onFloor) xVel = 0;

	if (input->getKey(SDL_SCANCODE_RIGHT) || input->getKey(SDL_SCANCODE_D))
	{
		if (onFloor) xVel += speed;
		else if (jumpDir == RIGHT) xVel = speed;
		else if (jumpDir == LEFT)
		{
			xVel = airSpeed;
			jumpDir = UP;
		}
		else if (jumpDir == UP) xVel = airSpeed;
	}

	if (input->getKey(SDL_SCANCODE_LEFT) || input->getKey(SDL_SCANCODE_A))
	{
		if (onFloor) xVel += -speed;
		else if (jumpDir == RIGHT)
		{
			xVel = -airSpeed;
			jumpDir = UP;
		}
		else if (jumpDir == LEFT) xVel = -speed;
		else if (jumpDir == UP) xVel = -airSpeed;
	}

	if (input->getKeyPressed(SDL_SCANCODE_UP) || input->getKeyPressed(SDL_SCANCODE_W) || input->getKeyPressed(SDL_SCANCODE_SPACE))
	{
		if (doubleJump || canJump)
		{
			yVel = jumpPower;
			if (xVel > 0) jumpDir = RIGHT;
			else if (xVel < 0) jumpDir = LEFT;
			else if (xVel == 0) jumpDir = UP;
		}
	}
}

void Player::collision()
{
	if (level->playerCollision(x, y, xVel, yVel, width, height))
	{
		canJump = true;
		onFloor = true;
	}
	else
	{
		if (onFloor == true)
		{
			if (xVel > 0) jumpDir = RIGHT;
			else if (xVel < 0) jumpDir = LEFT;
			else if (xVel == 0) jumpDir = UP;
		}
			
		onFloor = false;
		canJump = false;
	}
}

bool Player::isDead()
{
	return dead;
}

int Player::getX()
{
	return x;
}
int Player::getY()
{
	return y;
}