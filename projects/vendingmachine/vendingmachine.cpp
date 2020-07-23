#include <iostream>
#include <map>
#include <utility>
#include <string>

#include "singleton.hpp"
using namespace ilrd;

/**************************** Product Implementation **************************/

class Product
{
public:
    Product(std::string codeName, std::size_t quantity, int price):
        m_code(codeName),
        m_quantity(quantity),
        m_price(price)
    {}

    int GetPrice() { return m_price; }
    std::size_t GetQuantity() { return m_quantity; }
private:
    std::string m_code;
    std::size_t m_quantity;
    int m_price;
};

/******************************* State Pattern ********************************/

class Controller;

class State
{
public:
    virtual ~State() {}

    virtual void Restart(Controller& controller) = 0;
    virtual void Reset(Controller& controller) = 0;

    virtual void InsertCoin(Controller& controller, int coin) = 0;
    virtual void PressChoice(Controller& controller, std::string code) = 0;
    virtual void Dispense(Controller& controller) = 0;
private:
};

class PendingMoneyState: public State
{
public: 
    explicit PendingMoneyState()
    {

    }

    void InsertCoin(Controller& controller, int coin)
    {
        controller.SetState(Singleton<CoinInsertedState>::GetInstance())
    }

    void PressChoice(Controller& controller, std::string code)
    {
        std::cout << code.c_str() << "price is: " << controller.GetProductInfo(code).GetPrice();
        std::cout << controller.GetProductInfo(code).GetQuantity() << " items left\n";
    }

    void Dispense(Controller& controller)
    {
        std::cout << "Invalid Operation\n";
    }

private:

};

class UnavailableState: public State
{
public:
    virtual void Operation(Controller& controller)
    {
        
    }
private:

};

class CoinInsertedState: public State
{
public:
    explicit CoinInsertedState()
    {
        
    }

    void InsertCoin(Controller& controller, int coin)
    {
        m_coinsCollected += coin;
        controller.SetState(this); 
    }

    void PressChoice(Controller& controller, std::string code)
    {
        controller.SetState(Singleton<DispenseState>::GetInstance());
    }

    void Dispense(Controller& controller)
    {
        controller.SetState(Singleton<PendingMoneyState>::GetInstance());
    }
private:
    int m_coinsCollected;

};

class DispenseState: public State
{
    explicit DispenseState()
    {

    }

    void InsertCoin(Controller& controller)
    {
        std::cout << "Previous order processing...\n";
    }

    void PressChoice(Controller& controller)
    {
        std::cout << "Previous order processing\n";
    }

    void Dispense(Controller& controller)
    {
        controller.SetState(Singleton<PendingMoneyState>::GetInstance());
    }
};

class Controller
{
public:
    explicit Controller():
        m_currState(Singleton<PendingMoneyState>::GetInstance())
    {

    }

    void SetState(State *state)
    {
        m_currState = state;
    }

    void Add(std::string nameCode, Product product)
    {
        m_vendingMap[nameCode] = product;
    }

    Product& GetProductInfo(std::string code) 
    {
        return m_vendingMap[code];
    }
    
private:
    State *m_currState;
    std::map<std::string, Product> m_vendingMap;
};

int main()
{
    return 0;
}