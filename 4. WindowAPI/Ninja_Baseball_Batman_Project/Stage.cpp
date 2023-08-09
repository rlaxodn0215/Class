#include "Stage.h"

Stage::Stage(int stageNum, Animation * stageArea, vector<RECT> limitArea, map<string, shared_ptr<Sound>> bgm,
    map<string, shared_ptr<Animation>> ui, map<string, shared_ptr<Animation>> background, vector<Charactor> stageCharactors)
{
    m_StageNum = stageNum;
    m_StageArea = stageArea;
    m_LimitArea = limitArea;
    m_BGM = bgm;
    m_Background = background;
    m_UI = ui;
    m_StageCharactors = stageCharactors;
}

Stage::~Stage()
{
    if (m_StageArea != NULL)
        delete m_StageArea;
}

