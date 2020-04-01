/*********************************/
/*    CPP2C                      */
/*    Author: Yonatan            */
/*    Reviewed By:               */
/*    Date:   1/4/20             */
/*********************************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#define NUM_SEATS 20

typedef struct PublicTransport PublicTransport_t;
typedef struct Minibus Minibus_t;
typedef struct Taxi Taxi_t;
typedef struct SpecialTaxi SpecialTaxi_t;

int PublicTransport_g_s_count;

/**************************PublicTransport Structs*****************************/

struct PublicTransport
{
    struct PublicTransport__vtbl *v_ptr;
    int m_license_plate;    
};

struct PublicTransport__vtbl
{
    void(*Dtor)(PublicTransport_t*);
    void(*Display_this)(PublicTransport_t*);
};

void PublicTransport__PrintCount(); 
void PublicTransport__ctor(PublicTransport_t *mem_);
void PublicTransport__dtor(PublicTransport_t *this_);
void PublicTransport__cctor(PublicTransport_t *mem_, PublicTransport_t *other_);
void PublicTransport__Display_this(PublicTransport_t *this_);

struct PublicTransport__vtbl g_PublicTransport_vtbl = 
{ 
    &PublicTransport__dtor, 
    &PublicTransport__Display_this 
};

/****************************** Minibus Structs *******************************/

struct Minibus
{
    PublicTransport_t base;
    int m_numSeats;
};

struct Minibus__vtbl
{
    struct PublicTransport__vtbl basevt;
    void (*minibus_wash)(Minibus_t*, int);
};

void Minibus__ctor(Minibus_t *mem_);
void Minibus__dtor(Minibus_t *this_);
void Minibus__cctor(Minibus_t *mem_, Minibus_t *other_);
void Minibus__Display_this(Minibus_t *this_);
void Minibus__Wash_this(Minibus_t *this_, int minutes);

struct Minibus__vtbl g_Minibus_vtbl = 
{ 
    {(void(*)(PublicTransport_t*))&Minibus__dtor, 
    (void(*)(PublicTransport_t*))&Minibus__Display_this}, 
    &Minibus__Wash_this 
};

/******************************** Taxi Structs ********************************/

struct Taxi
{
    PublicTransport_t base;
};

struct Taxi__vtbl
{
    struct PublicTransport__vtbl basevt;
};

void Taxi__ctor(Taxi_t *mem_);
void Taxi__dtor(Taxi_t *this_);
void Taxi__cctor(Taxi_t *mem_, Taxi_t *other_);
void Taxi__Display_this(Taxi_t *this_);

struct Taxi__vtbl g_Taxi_vtbl = 
{
    {
     (void(*)(PublicTransport_t*))&Taxi__dtor,
     (void(*)(PublicTransport_t*))&Taxi__Display_this
    }
};

/*************************** Special Taxi Structs *****************************/

struct SpecialTaxi
{
    Taxi_t base;
};

struct SpecialTaxi__vtbl
{
    struct Taxi__vtbl basevt;
};

void SpecialTaxi__ctor(SpecialTaxi_t *mem_);
void SpecialTaxi__dtor(SpecialTaxi_t *this_);
void SpecialTaxi__cctor(SpecialTaxi_t *mem_, SpecialTaxi_t *other_);
void SpecialTaxi__Display_this(SpecialTaxi_t *this_);

struct SpecialTaxi__vtbl g_SpecialTaxi_vtbl = 
{
    {
        {   
            (void(*)(PublicTransport_t*))&SpecialTaxi__dtor,
            (void(*)(PublicTransport_t*))&SpecialTaxi__Display_this
        }   
    }
};

/************************** PublicTransport Funcs *****************************/

void PublicTransport__ctor(PublicTransport_t *mem_)
{
    mem_->v_ptr = (&g_PublicTransport_vtbl);
    mem_->m_license_plate = ++PublicTransport_g_s_count;
    printf("PublicTransport::Ctor()%d\n", mem_->m_license_plate); 
}

void PublicTransport__dtor(PublicTransport_t *this_)
{
    this_->v_ptr = (&g_PublicTransport_vtbl);
    --PublicTransport_g_s_count;
    printf("PublicTransport::Dtor()%d\n", this_->m_license_plate);
}

void PublicTransport__cctor(PublicTransport_t *mem_, PublicTransport_t *other_)
{
    mem_->m_license_plate = ++PublicTransport_g_s_count;
    mem_->v_ptr = (&g_PublicTransport_vtbl);
    printf("PublicTransport::CCtor()%d\n", mem_->m_license_plate);
}

void PublicTransport__Display_this(PublicTransport_t *this_)
{
    printf("PublicTransport::display():%d\n", this_->m_license_plate);
}

void PublicTransport__PrintCount()
{
    printf("s_count: %d\n", PublicTransport_g_s_count);
}

int PublicTransport__GetID_this(PublicTransport_t *this_)
{
    return this_->m_license_plate;    
}

/******************************* Minibus Funcs ********************************/

void Minibus__ctor(Minibus_t *mem_)
{
    PublicTransport__ctor(&(mem_->base));
    (*(struct Minibus__vtbl**)mem_) = &g_Minibus_vtbl;
    mem_->m_numSeats = NUM_SEATS;
    printf("Minibus::Ctor()\n");
}

void Minibus__cctor(Minibus_t *mem_, Minibus_t *other_)
{
    PublicTransport__cctor(&(mem_->base), &(other_->base));
    (*(struct Minibus__vtbl**)mem_) = &g_Minibus_vtbl;
    mem_->m_numSeats = other_->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void Minibus__dtor(Minibus_t *this_)
{
    (*(struct Minibus__vtbl**)this_) = &g_Minibus_vtbl;
    printf("Minibus::Dtor()\n");
    PublicTransport__dtor(&(this_->base));
}

void Minibus__Display_this(Minibus_t *this_)
{
    printf("Minibus::display() ID:%d", PublicTransport__GetID_this(&(this_->base)));
    printf(" num seats:%d\n", this_->m_numSeats);
}

void Minibus__Wash_this(Minibus_t *this_, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes,
PublicTransport__GetID_this(&(this_->base)));    
}

/********************************* Taxi Funcs *********************************/

void Taxi__ctor(Taxi_t *mem_)
{
    PublicTransport__ctor(&(mem_->base));
    (*(struct Taxi__vtbl**)mem_) = &g_Taxi_vtbl;
    printf("Taxi::Ctor()\n");
}

void Taxi__dtor(Taxi_t *this_)
{
    (*(struct Taxi__vtbl**)this_) = &g_Taxi_vtbl;
    printf("Taxi::Dtor()\n");
    PublicTransport__dtor(&(this_->base));
}

void Taxi__cctor(Taxi_t *mem_, Taxi_t *other_)
{
    PublicTransport__cctor(&(mem_->base), &(other_->base));
    (*(struct Taxi__vtbl**)mem_) = &g_Taxi_vtbl;
    printf("Taxi::CCtor()\n");
}

void Taxi__Display_this(Taxi_t *this_)
{
    printf("Taxi::display() ID:%d\n", PublicTransport__GetID_this(&(this_->base)));
}

/***************************** Special Taxi Funcs *****************************/

void SpecialTaxi__ctor(SpecialTaxi_t *mem_)
{
    Taxi__ctor(&(mem_->base));
    (*(struct SpecialTaxi__vtbl**)mem_) = &g_SpecialTaxi_vtbl;
    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxi__dtor(SpecialTaxi_t *this_)
{
    (*(struct SpecialTaxi__vtbl**)this_) = &g_SpecialTaxi_vtbl;
    printf("SpecialTaxi::Dtor()\n");
    Taxi__dtor(&(this_->base));
}
void SpecialTaxi__cctor(SpecialTaxi_t *mem_, SpecialTaxi_t *other_)
{
    Taxi__cctor(&(mem_->base), &(other_->base));
    (*(struct SpecialTaxi__vtbl**)mem_) = &g_SpecialTaxi_vtbl;   
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxi__Display_this(SpecialTaxi_t *this_)
{
    printf("SpecialTaxi::display() ID:%d\n", 
                     PublicTransport__GetID_this(&(this_->base.base)));
}

/******************************** Other Funcs *********************************/

void PrintInfoPublic(PublicTransport_t *a_)
{
    a_->v_ptr->Display_this(a_);
}

void PrintInfoVoid()
{
    PublicTransport__PrintCount();        
}

void PrintInfoMinibus(Minibus_t *m_)
{
    (*(struct Minibus__vtbl**)m_)->minibus_wash(m_, 3);
}

void PrintInfoInt(PublicTransport_t *mem_, int i)
{
    struct Minibus ret;
    
    Minibus__ctor(&ret);
    printf("print_info(int i)\n");
    Minibus__Display_this(&ret);
    PublicTransport__cctor(mem_, &(ret.base));
    Minibus__dtor(&ret);          
}

void TaxiDisplay(Taxi_t* t_)
{
    Taxi__Display_this(t_);
}

/******************************************************************************/

int main (int argc, char *argv[], char **envp)
{

/*********************************** variables ********************************/
    int i = 0;
    Minibus_t m;
    PublicTransport_t p;
    Taxi_t t;
    SpecialTaxi_t st;
    Taxi_t temp;
    
    Minibus_t *m_arr[2];
    Taxi_t *t_arr = NULL;
    Taxi_t *t_ptr = NULL;
    
    Minibus_t m_2;
    Taxi_t t_2;
    PublicTransport_t p_2[3];
    
    Minibus_t m_3;
    
    Minibus_t m_arr2[4];
    
/******************************** 190 - 192 ***********************************/
    Minibus__ctor(&m);
    PrintInfoMinibus(&m);
    PrintInfoInt(&p, 3);
    PublicTransport__Display_this(&p);
    PublicTransport__dtor(&p);

/******************************** 193 - 202 ***********************************/
    m_arr[0] = (Minibus_t*)malloc(sizeof(Minibus_t));
    Minibus__ctor(m_arr[0]);
    
    t_arr = (Taxi_t*)malloc(sizeof(Taxi_t));
    Taxi__ctor(t_arr);

    m_arr[1] = (Minibus_t*)malloc(sizeof(Minibus_t));
    Minibus__ctor(m_arr[1]);
    
    m_arr[0]->base.v_ptr->Display_this((PublicTransport_t *)m_arr[0]);
    t_arr->base.v_ptr->Display_this((PublicTransport_t *)t_arr);
    m_arr[1]->base.v_ptr->Display_this((PublicTransport_t *)m_arr[1]);
    
    Minibus__dtor(m_arr[0]);
    Taxi__dtor(t_arr);
    Minibus__dtor(m_arr[1]);
    
    free(m_arr[0]);
    free(m_arr[1]);
    free(t_arr);

/******************************** 203 - 209 ***********************************/
    Minibus__ctor(&m_2);
    PublicTransport__cctor(p_2, &(m_2.base));
    Minibus__dtor(&m_2);
    
    Taxi__ctor(&t_2);
    PublicTransport__cctor(p_2 + 1, &(t_2.base));
    Taxi__dtor(&t_2);
    
    PublicTransport__ctor(p_2 + 2);
    
    PublicTransport__Display_this(p_2);
    PublicTransport__Display_this(p_2 + 1);
    PublicTransport__Display_this(p_2 + 2);
    
    PrintInfoPublic(p_2);
    
/******************************** 210 - 212 ***********************************/
    PublicTransport__PrintCount();
    Minibus__ctor(&m_3);
    PublicTransport__PrintCount();

/******************************** 214 - 216 ***********************************/    
    for (i = 0; i < 4; ++i)
    {
        Minibus__ctor(m_arr2 + i);
    }
    
    t_ptr = (Taxi_t*)malloc(sizeof(Taxi_t) * 4);

    for (i = 0; i < 4; ++i)
    {
        Taxi__ctor(t_ptr + i);
    }
    
    for (i = 3; i >= 0; --i)
    {
        Taxi__dtor(t_ptr + i);
    }
    
    free(t_ptr);
    
/******************************** 218 - end ***********************************/    
    printf("%d\n", (2 > 1) ? 2 : 1);
    printf("%d\n", (2.0f > 1) ? 2 : 1);
    
    SpecialTaxi__ctor(&st);
    Taxi__cctor(&temp, &(st.base));
    TaxiDisplay(&temp);
    Taxi__dtor(&temp);
    
    SpecialTaxi__dtor(&st);
    
    for (i = 3; i >= 0; --i)
    {
        Minibus__dtor(m_arr2 + i);
    }
    
    Minibus__dtor(&m_3);
    
    for (i = 2; i >= 0; --i)
    {
        PublicTransport__dtor(p_2 + i);
    }
    
    Minibus__dtor(&m);
    
    return 0;
}
