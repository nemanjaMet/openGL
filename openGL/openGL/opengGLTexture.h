#pragma once
class opengGLTexture
{
public:
	opengGLTexture();
	~opengGLTexture();

	static void PrepareTexturing(bool bEnableLighting);
	void LoadFromFile(CString datoteka, int umanjenje);
	void Select(void);
	void Release(void);

	unsigned int m_ID;
};

