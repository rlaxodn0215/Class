#pragma once
#include "framework.h"

enum Status
{
    MOVE_ABLE,
    WALL,
    START,
    END,
};

enum LIST
{
    NONE,
    OPEN_LIST,
    CLOSE_LIST,
    PATH
};

class Block
{
private:
    int G;
    int H;
    int F;
    POINT pos;
    Status st;
    LIST lt;
    Block* parent;

public:
    int GetG() { return G; }
    int GetH() { return H; }
    int GetF() { return F; }
    POINT GetPos() { return pos; }
    Status GetStatus() { return st; }
    LIST GetList() { return lt; }
    Block* GetParent() { return parent; }

    void SetG(int g) { G = g; }
    void SetH(int h) { H = h; }
    void SetF() { F = G+H; }
    void SetPos(POINT p) { pos = p; }
    void SetStatus(Status s) { st = s; }
    void SetList(LIST l) { lt = l; }
    void SetParent(Block* b) { parent = b; }

    Block();
    Block(int g, int h, int f, POINT p, Status s);
    ~Block() {};

    bool operator>(const Block& other) const
    {
        if (F > other.F)
        {
            return true;
        }

        else if (F == other.F)
        {
            if (H>other.H)
            {
                return true;
            }

            else
            {
                return false;;
            }
        }

        else
        {
            return false;
        }

    }
    bool operator<(const Block& other) const 
    { 
        if (F < other.F)
        {
            return true;
        }

        else if (F == other.F)
        {
            if (H < other.H)
            {
                return true;
            }

            else
            {
                return false;;
            }
        }

        else
        {
            return false;
        }
    }
};


Block::Block()
{
    G = H = F = 0;
    pos = { 0,0 };
}

Block::Block(int g, int h, int f, POINT p, Status t)
{
    G = g;
    H = h;
    F = f;

    pos = p;
    st = t;
    lt = NONE;

}

