#pragma once
#include "framework.h"

enum Status
{
    MOVE_ABLE,
    WALL,
    START,
    END
};

class Block
{
private:
    int G;
    int H;
    int F;
    POINT pos;
    Status st;
    Block* parent;

public:
    int GetG() { return G; }
    int GetH() { return H; }
    int GetF() { return F; }
    POINT GetPos() { return pos; }
    Status GetStatus() { return st; }

    void SetG(int g) { G = g; }
    void SetH(int h) { H = h; }
    void SetF() { F = G+H; }
    void SetPos(POINT p) { pos = p; }
    void SetStatus(Status s) { st = s; }

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

