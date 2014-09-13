
class Texture
{
public:
	//load texture from file
	Texture(std::string fileName);
	
	//make texture with width and height and color
	Texture(int width, int height, int red, int green, int blue);

	//make texture from text
	Texture(std::string textureText, unsigned int fontSize, SDL_Color textColor);
	~Texture();

	int getHeight();
	int getWidth();
	void render(int x, int y, int width, int height);

private:
	void loadTexture(int width, int height, int red, int green, int blue);
	void loadTexture(std::string fileName);
	void loadTexture(std::string textureText, SDL_Color textColor);
	void free();

	SDL_Texture* _Texture = nullptr;
	int _Width;
	int _Height;
};

Texture::Texture(std::string fileName)
{
	_Texture = NULL;
	_Width = 0;
	_Height = 0;
	loadTexture(fileName);
}

Texture::Texture(int width, int height, int red, int green, int blue)
{
	_Texture = NULL;
	_Width = width;
	_Height = height;
	loadTexture(width, height, red, green, blue);
}

Texture::Texture(std::string textureText, unsigned int fontSize, SDL_Color textColor)
{
	_Texture = NULL;
	_Width = 0;
	_Height = 0;
	gFont = TTF_OpenFont("res/fonts/00TT.TTF", fontSize);
	loadTexture(textureText, textColor);
}

Texture::~Texture()
{
	free();
}

void Texture::free()
{
	if (_Texture != NULL)
	{
		SDL_DestroyTexture(_Texture);
		_Texture = NULL;
		_Width = 0;
		_Height = 0;
	}
}

void Texture::loadTexture(int width, int height, int red, int green, int blue)
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = nullptr;

	//create image
	loadedSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

	//fill the image with the color
	SDL_FillRect(loadedSurface, NULL, SDL_MapRGB(loadedSurface->format, red, green, blue));

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	//make a texture from the image
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	if (newTexture == NULL)
	{
		printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(loadedSurface);

	_Texture = newTexture;
}

void Texture::loadTexture(std::string fileName)
{
	free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(("./res/textures/" + fileName + ".png").c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", ("./res/textures/" + fileName + ".png").c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", ("./res/textures/" + fileName + ".png").c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			_Width = loadedSurface->w;
			_Height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	_Texture = newTexture;
}

void Texture::loadTexture(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);

	if (loadedSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			_Width = loadedSurface->w;
			_Height = loadedSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	_Texture = newTexture;
}

void Texture::render(int x, int y, int width, int height)
{
	if (_Texture != nullptr)
	{
		SDL_Rect renderRect = { x, y, width, height };
		SDL_RenderCopy(gRenderer, _Texture, NULL, &renderRect);
	}
}

int Texture::getHeight()
{
	return _Height;
}

int Texture::getWidth()
{
	return _Width;
}