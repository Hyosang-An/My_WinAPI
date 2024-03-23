#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator() :
    m_CurAnimation(nullptr),
    m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
    Safe_Del_Map(m_mapAnimation);
}

void CAnimator::finaltick()
{
    if (m_CurAnimation != nullptr)
    {
        if (m_CurAnimation->IsFinished() && m_bRepeat)
        {
            m_CurAnimation->Reset();
        }

        m_CurAnimation->finaltick();
    }
}

void CAnimator::render()
{
    if (m_CurAnimation != nullptr)
        m_CurAnimation->render();
}

CAnimation* CAnimator::CreateAnimation(const wstring& _AnimName, CTexture* _Atlas, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
    // ������ �̸��� Animation�� �̹� Animator�� �ִ� ���
    CAnimation* pAnim = FindAnimation(_AnimName);
    assert(pAnim == nullptr);

    // Animation ��ü ����
    pAnim = new CAnimation;
    pAnim->Create(_Atlas, _StartPos, _SliceSize, _FrameCount, _FPS);
    pAnim->SetName(_AnimName);
    pAnim->m_Animator = this;
    
    m_mapAnimation.insert(make_pair(_AnimName, pAnim));

    return pAnim;
}

CAnimation* CAnimator::FindAnimation(const wstring& _AnimName)
{
    const auto& iter = m_mapAnimation.find(_AnimName);
    if (iter == m_mapAnimation.end())
        return nullptr;

    return iter->second;
}

void CAnimator::LoadAnimation(wstring _strRelativeFilePath)
{
    // _strRelativeFilePath�� �� �տ� "\"�� ������ �߰�
    if (!_strRelativeFilePath.empty() && _strRelativeFilePath[0] != L'\\')
    {
        _strRelativeFilePath = L"\\" + _strRelativeFilePath;
    }

    CAnimation* pAnim = new CAnimation;
    if FAILED(pAnim->Load(_strRelativeFilePath))
    {
        delete pAnim;
        LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� �ε� ����");
        return;
    }

    if (FindAnimation(pAnim->GetName()) != nullptr)
    {
        delete pAnim;
        LOG(LOG_TYPE::DBG_ERROR, L"�ߺ��� �ִϸ��̼� �̸�");
        return;
    }

    pAnim->m_Animator = this;
    m_mapAnimation.insert(make_pair(pAnim->GetName(), pAnim));
}

void CAnimator::Play(const wstring& _AnimName, bool _Repeat)
{
    auto foundAnim = FindAnimation(_AnimName);

    if (foundAnim == nullptr)
    {
        LOG(LOG_TYPE::DBG_ERROR, L"Play�� �ִϸ��̼��� ã�� �� ����");
        return;
    }

    if (foundAnim == m_CurAnimation)
        return;

    m_CurAnimation = foundAnim;

    m_CurAnimation->Reset();
    m_bRepeat = _Repeat;
}


