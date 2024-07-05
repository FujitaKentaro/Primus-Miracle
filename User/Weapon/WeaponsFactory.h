#pragma once
#pragma warning(push)
#pragma warning(disable: 4514)

#include<string>
#pragma warning(pop)

class Weapon;

/// <summary>
/// 仮想ウェポン工場
/// </summary>
class WeaponsFactory
{
public:
	 ~WeaponsFactory() = default;

	 Weapon* CleateScene(const std::string& sceneName);
};

