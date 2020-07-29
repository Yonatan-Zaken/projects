#include <iostream>
#include <map>
#include <utility>

#include "utility.hpp"
#include "singleton.hpp"

using namespace ilrd;

/****************************** Change Dispenser ******************************/

class ChangeDispenser
{
public:
    explicit ChangeDispenser(int dispenseVal):
        m_dispenseVal(dispenseVal)
    {
    }

    void SetNext(ChangeDispenser *nextDispenser)
    {
        ChangeDispenser *lastDispenser = this;

        while (lastDispenser->m_next != nullptr)
        {
            lastDispenser = lastDispenser->m_next;
        }
        
        lastDispenser->m_next = nextDispenser;
    }

    void Handle(int ammount)
    {
        int counter = 0;
        if (ammount >= m_dispenseVal)
        {
            while (1 > (ammount / m_dispenseVal))
            {
                ++counter;
                ammount -= m_dispenseVal;
            }
        }
        
        Dispense(counter);

        if (m_next != nullptr)
        {
            m_next->Handle(ammount);
        }
        
    }

    virtual void Dispense(int ammount);

protected:
    ChangeDispenser *m_next;
    int m_dispenseVal;
};

class Dispense200: public ChangeDispenser
{
public:
    void Dispense(int counter)
    {
        std::cout << "Number of 200 bills: " << counter << "\n";
    }
};  

class Dispense100: public ChangeDispenser
{
public:
    void Dispense(int counter)
    {
        std::cout << "Number of 100 bills: " << counter << "\n";
    }
};

class Dispense50: public ChangeDispenser
{
public:
    void Dispense(int counter)
    {
        std::cout << "Number of 50 bills: " << counter << "\n";
    }
};

/************************************ ATM *************************************/

class Context
{
public:
    class ATMState;
    //class WaitForCard;
    explicit Context()
    //:    m_currState(Singleton<WaitForCard>::GetInstance())
    {
        m_currState = Singleton<WaitForCard>::GetInstance();
    }

    void SetState(ATMState* state)
    {
        m_currState = state;
    }

    void AddClient(int pinNum, int cashAmount)
    {
        m_clientMap[pinNum] = cashAmount;
    }

    bool IsValidPin(int pin)
    {
        std::map<int, int>::iterator it;
        if (m_clientMap.end() != (it = m_clientMap.find(pin)))
        {
            return true;
        }
        
        return false;
    }

private:
    ATMState *m_currState;
    std::map<int, int> m_clientMap;
};

class ATMState
{
public:
    virtual ~ATMState() {}
    virtual void InsertCard(Context& context) = 0;
    virtual void EjectCard(Context& context) = 0;
    virtual void EnterPin(Context& context, int pin) = 0;
    virtual void ChooseTransaction(Context& context, int ammount) = 0;
private:
};

class WaitForCard: public ATMState
{
public:
    void InsertCard(Context& context)
    {
        std::cout << "Welcome, please enter your pin...\n";
        context.SetState(Singleton<EnterPin>::GetInstance());
    }

    void EjectCard(Context& context)
    {
        std::cout << "No card inserted...\n";
    }

    void EnterPin(Context& context, int pin)
    {
        std::cout << "Please enter card first...\n";
        context.SetState(this);
    }

    void ChooseTransaction(Context& context, int ammount)
    {
        std::cout << "Please enter card first...\n";
        context.SetState(this);
    }

private:
    explicit WaitForCard();
    friend class Singleton<WaitForCard>;
};

class WaitForPin: public ATMState
{
public:
    void InsertCard(Context& context)
    {
        std::cout << "Processing other request...\n";
        context.SetState(this);
    }

    void EjectCard(Context& context)
    {
        context.SetState(Singleton<WaitForCard>::GetInstance());
    }

    void EnterPin(Context& context, int pin)
    {
        if (true == context.IsValidPin(pin))
        {
            std::cout << "Choose transaction...\n";
            context.SetState(Singleton<ChooseTransaction>::GetInstance());
        }

        else
        {
            std::cout << "Wrong pin, please try again...\n";
        }
    }

    void ChooseTransaction(Context& context, int ammount)
    {
        std::cout << "Enter Pin...\n";
        context.SetState(this);
    }
    
private:
    explicit InsertCard();
    friend class Singleton<InsertCard>;
};

class WaitForTransaction: public ATMState
{
public:
    void InsertCard(Context& context)
    {
        std::cout << "Processing other request...\n";
    }
    
    void EjectCard(Context& context)
    {
        context.SetState(Singleton<WaitForCard>::GetInstance());
    }

    void EnterPin(Context& context, int pin)
    {
        std::cout << "Processing other request...\n";
    }

    void ChooseTransaction(Context& context, int ammount)
    {
        context.SetState(Singleton<WaitForCard>::GetInstance());
    }

private:
    explicit WaitForTransaction();
    friend class Singleton<WaitForTransaction>;
};

int main()
{
    return 0;
}