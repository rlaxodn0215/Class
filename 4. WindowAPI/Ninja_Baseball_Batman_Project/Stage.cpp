#include "Stage.h"

Stage::Stage(int stageNum, Sprite* stageArea, vector<RECT>& limitArea, vector<shared_ptr<Charactor>>& monsters,
    map<string, shared_ptr<Sound>>& BGM, map<string, shared_ptr<Animation>>& monstersAni,
    map<string, shared_ptr<Animation>>& uiAni, bool isFinish)
{
    m_StageNum = stageNum;
    m_StageArea = stageArea;
    m_LimitArea = limitArea;
    m_Monsters = monsters;
    m_BGMs = BGM;
    m_MonstersAni = monstersAni;
    m_UIAni = uiAni;
    m_isFinish = isFinish;
}

Stage::~Stage()
{
    if(m_StageArea !=NULL)
        delete m_StageArea;
}

void Stage::ShowUIStage(HWND hWnd, HDC hdc, int timerDefine, int delayTime, TIMERPROC func)
{
    POINT startsceneLot = { 512, 384 };
    m_UIAni["StartScene"]->AniPlay(hWnd, hdc, startsceneLot,
        m_UIAni["StartScene"]->GetFrameCurCount(),2.0f, timerDefine, delayTime, func);
}
