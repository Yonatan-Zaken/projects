#include <iostream>
#include <vector>
#include <map>

class ParkingSpot
{
public:
    explicit ParkingSpot();
    virtual ~ParkingSpot() {}
    virtual void AssignSpot() = 0;
    virtual int GetNextFree() = 0;
    virtual int SetNextFree() = 0;
    bool IsFree();
private:
    bool m_isFree;
    int m_nextFree;
};

ParkingSpot::ParkingSpot(): m_isFree(true)
{
}

/******************************************************************************/

class BusSpot: public ParkingSpot
{
public:
private:
};

class CarSpot: public ParkingSpot
{
public:
private:
};

class MotorcycleSpot: public ParkingSpot
{
public:
private:
};

/******************************************************************************/

class AssignSpotCommand
{
public:
    explicit AssignSpotCommand(ParkingSpot& parkingSpot);
    virtual void AssignSpot() = 0;
private:
    ParkingSpot& m_parkingSpot;
};

class AssignBusSpot: public AssignSpotCommand
{
public:
    explicit AssignBusSpot(ParkingSpot& parkingSpot);
    void AssignSpot();
};

class AssignCarSpot: public AssignSpotCommand
{
public:
    explicit AssignCarSpot(ParkingSpot& parkingSpot);
    void AssignSpot();
};

class AssignMotorSpot: public AssignSpotCommand
{
public:
    explicit AssignMotorSpot(ParkingSpot& parkingSpot);
    void Execute();
};

class ParkingAdministrator
{
public:
    void Register(std::string type, AssignCommand& command);
    void Execute(std::string type);
private:
    std::map<std::string, AssignSpotCommand> m_commandMap;
};


/******************************************************************************/

class ParkingFloor
{
public:
    explicit ParkingFloor(char floorLevel, std::size_t busSpots, std::size_t carSpots, std::size_t motorSpots);
    void AddSpot(const ParkingSpot& spot);
    void AssignSpot(std::string type);
    void FreeSpot(ParkingSpot& spot);
    bool IsFull();
    char GetFloorLevel() const;
private:
    char m_floorLevel;
    bool m_isFull;
    BusSpot *m_busSpots;
    CarSpot *m_carSpots;
    MotorcycleSpot *m_motorSpot;

    ParkingAdministrator m_parkingAdmin;

    int m_nextMotorcycleFree;
    int m_nextCarFree;
    int m_nextBustFree;
};

ParkingFloor::ParkingFloor(char floorLevel, std::size_t busSpots, std::size_t carSpots, std::size_t motorSpots):
    m_floorLevel(floorLevel),
    m_isFull(false),
    m_busSpots(new BusSpot[busSpots]),
    m_carSpots(new CarSpot[carSpots]),
    m_motorSpot(new MotorcycleSpot[motorSpots])
{
    m_parkingAdmin.Register("Bus", )
}

bool ParkingFloor::IsFull()
{
    return m_isFull;
}

/******************************************************************************/

class ParkingLot
{
public:
    explicit ParkingLot(std::size_t numOfFloors);
    void AddFloor();
    void AddEntrance();
    bool IsFull();
private:
    std::vector<ParkingFloor> m_floors;
};

ParkingLot::ParkingLot(std::size_t numOfFloors):
    m_floors()
{
    char level = 'A';
    for (std::size_t i = 0; i < numOfFloors; ++i)
    {
        m_floors.push_back(ParkingFloor(static_cast<char>(level + i)));
    }
}

void ParkingLot::AddFloor()
{
    char topFloor = m_floors.front().GetFloorLevel();
    m_floors.push_back(ParkingFloor(static_cast<char>(topFloor + 1)));
}

/******************************************************************************/

int main()
{

    return 0;
}