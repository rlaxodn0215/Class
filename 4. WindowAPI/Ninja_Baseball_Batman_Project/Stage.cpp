#include "Stage.h"

Stage::Stage(int stageNum, Animation stageArea, vector<RECT>& limitArea, map<string, Sound*>& bgm,
    map<string, Animation*>& ui, map<string, Animation*>& background, vector<Charactor>& stageMonsters)
{
    m_StageNum = stageNum;
    m_StageArea = stageArea;
    m_LimitArea = limitArea;
    m_BGM = bgm;
    m_Background = background;
    m_UI = ui;
    m_StageMonsters = stageMonsters;
    m_isFinish = false;
}

Stage::~Stage()
{

}

