#pragma once
class Boss;
class IBossState
{
protected:
	static Boss* _boss;

public:

	IBossState();
	virtual ~IBossState();
	/// 初期化を行う
	virtual void Initialize() = 0;
	/// 更新を行う
	virtual void Update() = 0;
};

