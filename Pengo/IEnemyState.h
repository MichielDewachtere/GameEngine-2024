#ifndef IENEMYSTATE_H
#define IENEMYSTATE_H

namespace real
{
	class GameObject;
}

class IEnemyState
{
public:
	explicit IEnemyState(real::GameObject* pOwner) : m_pOwner(pOwner) {}
	virtual ~IEnemyState() = default;

	IEnemyState(const IEnemyState& other) = delete;
	IEnemyState& operator=(const IEnemyState& rhs) = delete;
	IEnemyState(IEnemyState&& other) = delete;
	IEnemyState& operator=(IEnemyState&& rhs) = delete;

	virtual void Enter() {}
	virtual IEnemyState* Update() { return nullptr; }
	virtual void Exit() {}

protected:
	real::GameObject* GetOwner() const { return m_pOwner; }
private:
	real::GameObject* m_pOwner;
};

#endif // IENEMYSTATE_H