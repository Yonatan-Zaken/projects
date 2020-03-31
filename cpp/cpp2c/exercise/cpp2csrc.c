#include <stdio.h>


int s_count;

/**************************PublicTransport Structs*****************************/
 
struct PublicTransport
{
    struct PublicTransport__vtbl* v_ptr;
    int m_license_plate;    
};

struct PublicTransport__vtbl
{
    void(*Dtor)(struct PublicTransport*);
    void(*Display_this)(struct PublicTransport*);
};

/****************************** Minibus Structs *******************************/

struct Minibus
{
    struct PublicTransport base;
    int m_numSeats;
};

/************************** PublicTransport Funcs *****************************/
void PublicTransport__ctor(struct PublicTransport* mem_);
void PublicTransport__dtor(struct PublicTransport* this_);
void PublicTransport__cctor(struct PublicTransport* mem_, struct PublicTransport* src_);
void PublicTransport__Display_this(struct PublicTransport* this_);
void PublicTransport__PrintCount_this(struct PublicTransport* this_);

struct PublicTransport__vtbl g_PublicTransport_vtbl = 
{ &PublicTransport__dtor, 
  &PublicTransport__Display_this };

void PublicTransport__ctor(struct PublicTransport* mem_)
{
    mem_->v_ptr = (&g_PublicTransport_vtbl);
    mem_->m_license_plate = ++s_count;
    printf("PublicTransport::Ctor() %d\n", mem_->m_license_plate); 
}

void PublicTransport__dtor(struct PublicTransport* this_)
{
    --s_count;
    printf("PublicTransport::Dtor() %d\n", this_->m_license_plate);
}

void PublicTransport__cctor(struct PublicTransport* mem_, struct PublicTransport* other_)
{
    mem_->m_license_plate = ++s_count;
    printf("PublicTransport::CCtor() %d\n", mem_->m_license_plate);
}

void PublicTransport__Display_this(struct PublicTransport* this_)
{
    printf("PublicTransport::display(): %d\n", this_->m_license_plate);
}

void PublicTransport__PrintCount_this(struct PublicTransport* this_)
{
    printf("s_count: %d\n", s_count);
}

static int PublicTransport__GetID_this(struct PublicTransport *this_)
{
    return this_->m_license_plate;    
}

/******************************* Minibus Funcs ********************************/

void Minibus_ctor(struct Minibus* mem_)
{
    PublicTransport__ctor(mem_);
    mem_->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

/*
void Minibus_cctor(struct Minibus* mem_, struct Minibus* other_)
{
    PublicTransport__cctor(mem_);
    
}
*/

void Minibus__dtor(struct Minibus* this_)
{
    printf("Minibus::Dtor()\n");
}

void Minibus__Display_this(struct Minibus* this_)
{
    printf("Minibus::display() ID:%d", PublicTransport__GetID_this(this_));
    printf(" num seats:%d\n", this_->m_numSeats);
}

void Minibus__Wash(struct Minibus* this_, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes,
PublicTransport__GetID_this(this_));    
}

/******************************* Taxi Funcs ********************************/


/******************************************************************************/

int main (int argc, char *argv[], char **envp)
{
    struct PublicTransport p1;
    
    PublicTransport__ctor(&p1);
    PublicTransport__dtor(&p1);
    return 0;
}
