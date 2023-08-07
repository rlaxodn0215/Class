#include "Stage.h"

Stage::Stage(int stageNum, Sprite * stageArea, vector<RECT>& limitArea, vector<shared_ptr<Charactor>>& monsters,
    map<string,shared_ptr<Sound>> & BGM, map<string,shared_ptr<Animation>> & Anis, bool isFinish)
{
    m_StageNum = stageNum;
    m_StageArea = stageArea;
    m_LimitArea = limitArea;
    m_Monsters = monsters;
    m_BGMs = BGM;
    m_Animations = Anis;
    m_isFinish = isFinish;
}

Stage::~Stage()
{
    if(m_StageArea !=NULL)
        delete m_StageArea;
}

BOOL Stage::StageStart()
{
    return 0;
}

BOOL Stage::StageEnd()
{
    return 0;
}
