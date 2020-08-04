#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "utility.hpp"

/******************************************************************************/
enum SPOT_SIZE
{
    BUS,
    CAR,
    MOTORCYCLE
};

class Vehicle
{
public:
    explicit Vehicle();
    virtual ~Vehicle() noexcept = 0;

    int GetLicenseNum() const;
    SPOT_SIZE GetSize() const;

protected:
    int m_licenseNum;
    SPOT_SIZE m_size;
    static int s_plateCounter;
};

int Vehicle::s_plateCounter = 0;

Vehicle::Vehicle()
{}

Vehicle::~Vehicle() noexcept
{}

int Vehicle::GetLicenseNum() const
{
    return m_licenseNum;
}

SPOT_SIZE Vehicle::GetSize() const
{
    return m_size;
}

class Bus: public Vehicle
{
public:
    explicit Bus();
    ~Bus() noexcept;
};

Bus::Bus()
{
    m_size = BUS;
    m_licenseNum = s_plateCounter++;
}

Bus::~Bus() noexcept
{}

class Car: public Vehicle
{
public:
    explicit Car();
    ~Car() noexcept;
};

Car::Car()
{
    m_size = CAR;
    m_licenseNum = s_plateCounter++;
}

Car::~Car() noexcept
{}

class Motorcycle: public Vehicle
{
public:
    explicit Motorcycle();
    ~Motorcycle() noexcept;
};

Motorcycle::Motorcycle()
{
    m_size = MOTORCYCLE;
    m_licenseNum = s_plateCounter++;
}

Motorcycle::~Motorcycle() noexcept
{}

/******************************************************************************/

class ParkingSpot
{
public:
    enum VACANCY 
    {
        VACANT,
        FULL
    };

    explicit ParkingSpot();
    ~ParkingSpot() noexcept {}
    void AssignSpot(Vehicle* vehicle);
    void FreeSpot();
    bool IsFree();
    int GetSpotID() const;
    int GetNextFree() const;
    int GetSpotNum() const;
    int GetFloor() const;

    void SetSpotSize(SPOT_SIZE size);
    void SetSpotID(int ID);
    void SetNextFree(int nextID);
    void SetSpotNum(int num);
    void SetFloor(int floor);

private:
    Vehicle *m_parkedVehicle;
    SPOT_SIZE m_size;
    int m_spotID;
    int m_nextFree;
    int m_spotNum;
    int m_floor;
};

ParkingSpot::ParkingSpot(): 
    m_parkedVehicle(nullptr)
{
}

void ParkingSpot::AssignSpot(Vehicle *vehicle)
{
    m_parkedVehicle = vehicle;
}

void ParkingSpot::FreeSpot()
{
    m_parkedVehicle = nullptr;
}

bool ParkingSpot::IsFree()
{
    return (m_parkedVehicle == nullptr);
}

int ParkingSpot::GetSpotID() const
{
    return m_spotID;
}

int ParkingSpot::GetNextFree() const
{
    return m_nextFree;
}

int ParkingSpot::GetSpotNum() const
{
    return m_spotNum;
}

int ParkingSpot::GetFloor() const
{
    return m_floor;
}

void ParkingSpot::SetSpotID(int ID)
{
    m_spotID = ID;
}

void ParkingSpot::SetNextFree(int nextID)
{
    m_nextFree = nextID;
}

void ParkingSpot::SetSpotSize(SPOT_SIZE size)
{
    m_size = size;
}

void ParkingSpot::SetSpotNum(int num)
{
    m_spotNum = num;
}

void ParkingSpot::SetFloor(int floor)
{
    m_floor = floor;
}

/******************************************************************************/

class ParkingAdmin
{
public:
    explicit ParkingAdmin();

    void Register(int licenseNum, ParkingSpot& parkingSpot);
    void Unregister(int licenseNum);
    ParkingSpot& GetVehicleSpot(int licenseNum);

private:
    std::map<int, ParkingSpot> m_parkingMap;
};

ParkingAdmin::ParkingAdmin():
    m_parkingMap()
{}

void ParkingAdmin::Register(int licenseNum, ParkingSpot& parkingSpot)
{
    m_parkingMap[licenseNum] = parkingSpot;
}

void ParkingAdmin::Unregister(int licenseNum)
{
    if (m_parkingMap.find(licenseNum) == m_parkingMap.end())
    {
        std::cout << "Vehicle not registered\n";
        return;
    }

    m_parkingMap.erase(licenseNum);
}

ParkingSpot& ParkingAdmin::GetVehicleSpot(int licenseNum)
{
    if (m_parkingMap.find(licenseNum) == m_parkingMap.end())
    {
        std::cout << "Vehicle not registered\n";
        //throw
    }

    return m_parkingMap[licenseNum];
}

/******************************************************************************/

class ParkingFloor
{
public:
    explicit ParkingFloor(char floorLevel, std::size_t busSpots, std::size_t carSpots, std::size_t motorSpots);
    ParkingSpot& ParkVehicle(Vehicle *vehicle);
    void ExitVehicle(Vehicle *vehicle, int spotIndex);
    bool IsFull(SPOT_SIZE size);
    char GetFloorLevel() const;
private:
    char m_floorLevel;
    bool m_isFull;
    boost::shared_ptr<ParkingSpot[]> m_busSpots;
    boost::shared_ptr<ParkingSpot[]> m_carSpots;
    boost::shared_ptr<ParkingSpot[]> m_motorSpots;

    int m_nextMotorcycleFree;
    int m_nextCarFree;
    int m_nextBusFree;

    static int s_spotCounter;
};

int ParkingFloor::s_spotCounter = 0;

ParkingFloor::ParkingFloor(char floorLevel, std::size_t busSpots, std::size_t carSpots, std::size_t motorSpots):
    m_floorLevel(floorLevel),
    m_isFull(false),
    m_busSpots(new ParkingSpot[busSpots]),
    m_carSpots(new ParkingSpot[carSpots]),
    m_motorSpots(new ParkingSpot[motorSpots]),
    m_nextMotorcycleFree(0),
    m_nextCarFree(0),
    m_nextBusFree(0)
{
    std::size_t i = 0;
    for (i = 0; i < busSpots; ++i)
    {
        m_busSpots[i].SetSpotSize(BUS);
        m_busSpots[i].SetSpotID(i);
        m_busSpots[i].SetNextFree(i + 1);
        m_busSpots[i].SetSpotNum(s_spotCounter++);
    }
    m_busSpots[i - 1].SetNextFree(ParkingSpot::FULL);

    for (i = 0; i < carSpots; ++i)
    {
        m_carSpots[i].SetSpotSize(CAR);
        m_carSpots[i].SetSpotID(i);
        m_carSpots[i].SetNextFree(i + 1);
        m_carSpots[i].SetSpotNum(s_spotCounter++);
    }
    m_carSpots[i - 1].SetNextFree(ParkingSpot::FULL);
    
    for (i = 0; i < motorSpots; ++i)
    {
        m_motorSpots[i].SetSpotSize(MOTORCYCLE);
        m_motorSpots[i].SetSpotID(i);
        m_motorSpots[i].SetNextFree(i + 1);
        m_motorSpots[i].SetSpotNum(s_spotCounter++);
    }
    m_motorSpots[i - 1].SetNextFree(ParkingSpot::FULL);
}

ParkingSpot& ParkingFloor::ParkVehicle(Vehicle *vehicle)
{
    SPOT_SIZE size = vehicle->GetSize();

    if (size == MOTORCYCLE)
    {
        m_motorSpots[m_nextMotorcycleFree].AssignSpot(vehicle);
        int spot = m_nextMotorcycleFree;
        m_nextMotorcycleFree = m_motorSpots[spot].GetNextFree();
        return m_motorSpots[spot];
    }

    else if (size == CAR)
    {

    }
    
    
}

void ParkingFloor::ExitVehicle(Vehicle *vehicle, int spotIndex)
{
    SPOT_SIZE size = vehicle->GetSize();

    if (size == MOTORCYCLE)
    {
        m_motorSpots[spotIndex].FreeSpot();
        m_motorSpots[spotIndex].SetNextFree(m_nextMotorcycleFree);
        m_nextMotorcycleFree = spotIndex;
    }
    

}

bool ParkingFloor::IsFull(SPOT_SIZE size)
{
    if (size == BUS)
    {
        return (m_nextBusFree == ParkingSpot::FULL);
    }

    else if (size == CAR)
    {
        return ((m_nextCarFree == ParkingSpot::FULL) && (m_nextBusFree == ParkingSpot::FULL));
    }

    else if (size == MOTORCYCLE)
    {
        return (m_nextMotorcycleFree == ParkingSpot::FULL);
    }
    
    return false;
}

/******************************************************************************/

class ParkingLot
{
public:
    explicit ParkingLot();
    void AddFloor(char floorLevel, std::size_t busSpots, std::size_t carSpots, std::size_t motorSpots);
    
    void ParkVehicle(Vehicle *vehicle);
    void ExitVehicle(Vehicle *vehicle);
    
private:
    std::vector<ParkingFloor> m_floors;
    ParkingAdmin m_admin;
    int m_capacity;
};

ParkingLot::ParkingLot():
    m_floors()
{
}

void ParkingLot::AddFloor(char floorLevel, std::size_t busSpots, std::size_t carSpots, std::size_t motorSpots)
{
    m_floors.push_back(ParkingFloor(floorLevel, busSpots, carSpots, motorSpots));
    m_capacity += (busSpots + carSpots + motorSpots);
}

void ParkingLot::ParkVehicle(Vehicle *vehicle)
{
    std::vector<ParkingFloor>::iterator it;

    for (it = m_floors.begin(); it != m_floors.end(); ++it)
    {
        if (!it->IsFull(vehicle->GetSize()))
        {
            ParkingSpot& spot = it->ParkVehicle(vehicle);
            m_admin.Register(vehicle->GetLicenseNum(), spot);
            return;
        }
    }
    
    std::cout << "No VACANT spots to park\n";
}

void ParkingLot::ExitVehicle(Vehicle *vehicle)
{
    ParkingSpot& spot = m_admin.GetVehicleSpot(vehicle->GetLicenseNum());
    m_floors[spot.GetFloor()].ExitVehicle(vehicle, spot.GetSpotID());
    m_admin.Unregister(vehicle->GetLicenseNum());
}


/******************************************************************************/

int main()
{

    return 0;
}