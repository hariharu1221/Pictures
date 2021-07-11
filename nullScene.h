#pragma once
class nullScene :
	public cScene
{
public:
	nullScene();
	virtual ~nullScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void ObRender();
	virtual void UIRender();
	virtual void Release();
};