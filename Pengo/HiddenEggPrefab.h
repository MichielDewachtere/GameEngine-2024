﻿#ifndef HIDDENEGGPREFAB_H
#define HIDDENEGGPREFAB_H

#include <Prefab.h>

class HiddenEggPrefab final : public real::Prefab
{
public:
	explicit HiddenEggPrefab(real::GameObject* pOwner);
	explicit HiddenEggPrefab(real::Scene* pScenes);
	virtual ~HiddenEggPrefab() override = default;

	HiddenEggPrefab(const HiddenEggPrefab& other) = delete;
	HiddenEggPrefab& operator=(const HiddenEggPrefab& rhs) = delete;
	HiddenEggPrefab(HiddenEggPrefab&& other) = delete;
	HiddenEggPrefab& operator=(HiddenEggPrefab&& rhs) = delete;

protected:
	void Init() const;
};

#endif // HIDDENEGGPREFAB_H