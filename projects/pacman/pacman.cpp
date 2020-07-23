#include <iostream>

class GhostStrategy
{
public:
    virtual void Execute() = 0;
};

/********************************** Chase *************************************/

class ChaseBehavior
{
public:
    virtual void Execute() = 0;
};

class Pursuit: public ChaseBehavior
{
public:
    void Execute();
};

class CutOff: public ChaseBehavior
{
public:
    void Execute();
};

class Patrol: public ChaseBehavior
{
public:
    void Execute();
};

class Random: public ChaseBehavior
{
public:
    void Execute();
};

/********************************** Scatter ***********************************/

class ScatterBehavior
{
public:
    virtual void Execute() = 0;
};

class TopLeft: public ScatterBehavior
{
public:
    void Execute();
};

class TopRight: public ScatterBehavior
{
public:
    void Execute();
};

class BottomLeft: public ScatterBehavior
{
public:
    void Execute();
};

class BottomRight: public ScatterBehavior
{
public:
    void Execute();
};

/********************************* Frightened *********************************/

class FrightenedBehavior
{
public:
    virtual void Execute() = 0;
};

class Roaming: public FrightenedBehavior
{
public:
    void Execute();
};

/**********************************  *************************************/

class Ghost
{
public:
    void SetBehavior(GhostStrategy *behavior);
private:
    GhostStrategy *m_strategy;
};

int main()
{

    return 0;
}