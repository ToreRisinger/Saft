
class Texture
{
public:
	Texture(std::string fileName);
	~Texture();

	bool loadTexture(std::string fileName);
	void free();
	int getHeight();
	int getWidth();
	void render(int x, int y, int width, int height);

private:
	SDL_Texture* m_Texture = nullptr;
	int m_Width;
	int m_Height;
};