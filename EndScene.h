#pragma once
class EndScene :
	public cScene
{
public:

	EndScene();
	virtual ~EndScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void UIRender();
	virtual void Release();
};

