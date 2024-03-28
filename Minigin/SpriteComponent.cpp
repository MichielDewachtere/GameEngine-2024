#include "SpriteComponent.h"

#include "GameObject.h"
#include "GameTime.h"

dae::SpriteComponent::SpriteComponent(GameObject* pOwner, SpriteSheet spriteSheet)
	: DrawableComponent(pOwner)
	, m_SpriteSheet(std::move(spriteSheet))
{
	m_TimePerAnimation = m_SpriteSheet.timePerAnimation;

	GetOwner()->GetTransform()->worldPosChanged.AddObserver(this);

	m_RenderPos = GetOwner()->GetTransform()->GetWorldPosition();

	m_Rect.z = m_SpriteSheet.pTexture->GetSize().x / m_SpriteSheet.columns;
	m_Rect.w = m_SpriteSheet.pTexture->GetSize().y / m_SpriteSheet.rows;
}

dae::SpriteComponent::~SpriteComponent()
{
	GetOwner()->GetTransform()->worldPosChanged.RemoveObserver(this);
}

void dae::SpriteComponent::Update()
{
	if (m_Pause || m_Stop)
	{
		m_IsAnimationPlaying = false;
		return;
	}

	m_AccuTime += GameTime::GetInstance().GetElapsed();

	if (m_AccuTime > m_TimePerAnimation)
	{
		//UpdateCurrIdx
		++m_CurrIdx;

		if (m_PlaySelectedIdcs == false)
		{
			if (m_CurrIdx > m_EndIdx)
			{
				++m_AccuLoops;

				if (m_Loops != -1 && m_AccuLoops > m_Loops)
				{
					m_AccuLoops = 0;
					m_Stop = true;
					m_CurrIdx = m_EndIdx;
					m_TimePerAnimation = m_SpriteSheet.timePerAnimation;
				}
				else
					m_CurrIdx = m_StartIdx;
			}

			//Move rect
			m_Rect.x = (m_CurrIdx % m_SpriteSheet.columns) * m_Rect.z;
			m_Rect.y = (m_CurrIdx / m_SpriteSheet.columns) * m_Rect.w;
		}
		else
		{
			if (m_CurrIdx >= static_cast<int>(m_SelectedIdcs.size()))
			{
				++m_AccuLoops;

				if (m_Loops != -1 && m_AccuLoops > m_Loops)
				{
					m_Stop = true;
				}

				m_CurrIdx = 0;
			}

			m_Rect.x = (m_SelectedIdcs[m_CurrIdx] % m_SpriteSheet.columns) * m_Rect.z;
			m_Rect.y = (m_SelectedIdcs[m_CurrIdx] / m_SpriteSheet.columns) * m_Rect.w;
		}

		m_AccuTime = 0.f;
	}
}

void dae::SpriteComponent::Render()
{
	const auto scale = GetOwner()->GetTransform()->GetScale();

	glm::ivec4 dstRect;
	dstRect.x = static_cast<int>(m_RenderPos.x);
	dstRect.y = static_cast<int>(m_RenderPos.y);
	dstRect.z = m_Rect.z * static_cast<int>(scale.x);
	dstRect.w = m_Rect.w * static_cast<int>(scale.y);

	Renderer::GetInstance().RenderSprite(*m_SpriteSheet.pTexture, m_Rect, dstRect, 0, { 0,0 }, m_Flip);
}

void dae::SpriteComponent::HandleEvent(TransformEvent, const glm::vec2& pos)
{
	m_RenderPos = pos;
}

void dae::SpriteComponent::OnSubjectDestroy()
{
	GetOwner()->GetTransform()->worldPosChanged.RemoveObserver(this);
}

void dae::SpriteComponent::SelectSprite(int idx)
{
	m_Pause = true;

	m_Rect.x = (idx % m_SpriteSheet.columns) * m_Rect.z;
	m_Rect.y = (idx / m_SpriteSheet.columns) * m_Rect.w;
}

void dae::SpriteComponent::PlayAnimation(int startIdx, int endIdx, int loops, float timePerAnimation)
{
	m_AccuTime = m_SpriteSheet.timePerAnimation;
	//m_AccuTime = 0.f;

	if (timePerAnimation == 0)
		m_TimePerAnimation = m_SpriteSheet.timePerAnimation;
	else
		m_TimePerAnimation = timePerAnimation;

	m_StartIdx = startIdx;
	m_EndIdx = endIdx;
	m_CurrIdx = m_StartIdx;

	m_AccuLoops = 0;
	m_Loops = loops;

	m_PlaySelectedIdcs = false;

	m_Pause = false;
	m_Stop = false;
	m_IsAnimationPlaying = true;

	m_Flip = RenderFlip::none;
}

void dae::SpriteComponent::PlayAnimation(const std::vector<int>& idcs, int loops, float timePerAnimation)
{
	m_PlaySelectedIdcs = true;
	m_SelectedIdcs = idcs;

	if (timePerAnimation == 0)
		m_TimePerAnimation = m_SpriteSheet.timePerAnimation;
	else
		m_TimePerAnimation = timePerAnimation;

	m_Loops = loops;

	m_CurrIdx = 0;

	m_Pause = false;
	m_Stop = false;
	m_IsAnimationPlaying = true;

	m_Flip = RenderFlip::none;
}

void dae::SpriteComponent::UpdateAnimation(int startIdx, int endIdx, int loops, float timePerAnimation)
{
	m_AccuTime = 0.f;

	if (timePerAnimation == 0)
		m_TimePerAnimation = m_SpriteSheet.timePerAnimation;
	else
		m_TimePerAnimation = timePerAnimation;

	m_StartIdx = startIdx;
	m_EndIdx = endIdx;
	m_CurrIdx = m_StartIdx;

	m_Loops = loops;
}

void dae::SpriteComponent::Pause(bool value)
{
	m_Pause = value;
}

void dae::SpriteComponent::Stop(bool value)
{
	m_Stop = value;

	if (m_Stop)
		m_IsAnimationPlaying = false;
}

void dae::SpriteComponent::FlipTexture(RenderFlip flip)
{
	m_Flip = flip;
}

glm::ivec2 dae::SpriteComponent::GetSpriteSheetSize() const
{
	return m_SpriteSheet.pTexture->GetSize();
}

glm::ivec2 dae::SpriteComponent::GetSpriteSize() const
{
	return glm::ivec2(m_Rect.z, m_Rect.w);
}
