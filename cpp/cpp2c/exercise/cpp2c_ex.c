/*******************************
    CPP2C
    C File
    21/03/2020
    ILRD - RD8081               
*******************************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

int PublicTransport_g_s_count = 0;

typedef struct PublicTransport PublicTransport_t;
typedef struct Minibus Minibus_t;
typedef struct Taxi Taxi_t;
typedef struct SpecialTaxi SpecialTaxi_t;
typedef struct PublicConvoy PublicConvoy_t;

/************************** PublicTransport structs *****************************/

struct PublicTransport
{
    void (**v_ptr)(PublicTransport_t *);
    int m_license_plate;       
};

void PublicTransport_dtor(PublicTransport_t *this_);
void PublicTransport_Display_this(PublicTransport_t *this_);

void (*g_PublicTransport_vtbl[2])(PublicTransport_t *) = 
{ 
    &PublicTransport_dtor, 
    &PublicTransport_Display_this 
};

/************************** Minibus Structs *****************************/

struct Minibus
{
    PublicTransport_t m_base;
    int m_numSeats;
};

void Minibus_dtor(Minibus_t *this_);
void Minibus_Display_this(Minibus_t *this_);
void Minibus_Wash_this(Minibus_t* this_, int minutes);

void (*g_Minibus_vtbl[3])(Minibus_t *) = 
{ 
    &Minibus_dtor, 
    &Minibus_Display_this, 
    (void(*)(Minibus_t *))&Minibus_Wash_this
};

/************************** Taxi Structs *****************************/

struct Taxi
{
    PublicTransport_t m_base;
};

void Taxi_dtor(Taxi_t *this_);
void Taxi_Display_this(Taxi_t *this_);

void (*g_Taxi_vtbl[2])(Taxi_t *) = 
{
    &Taxi_dtor,
    &Taxi_Display_this
};

/************************** SpecialTaxi Structs *****************************/

struct SpecialTaxi
{
    Taxi_t m_base;
};

void SpecialTaxi_dtor(SpecialTaxi_t *this_);
void SpecialTaxi_Display_this(SpecialTaxi_t *this_);

void (*g_SpecialTaxi_vtbl[2])(SpecialTaxi_t *) = 
{
    &SpecialTaxi_dtor,
    &SpecialTaxi_Display_this
};

/************************** PublicConvoy Structs ******************************/

struct PublicConvoy
{
    PublicTransport_t m_base;
    PublicTransport_t *m_pt1;    
    PublicTransport_t *m_pt2;
    Minibus_t m_m;
    Taxi_t m_t;
};

void PublicConvoy_dtor(PublicConvoy_t *this_);
void PublicConvoy_Display_this(PublicConvoy_t *this_);

void (*g_PublicConvoy_vtbl[2])(PublicConvoy_t *) = 
{
    &PublicConvoy_dtor,
    &PublicConvoy_Display_this
};


/************************** PublicTransport Funcs *****************************/

void PublicTransport_ctor(PublicTransport_t *mem_)
{
    mem_->v_ptr = g_PublicTransport_vtbl;
    mem_->m_license_plate = ++PublicTransport_g_s_count;
    printf("PublicTransport::Ctor()%d\n", mem_->m_license_plate);
}

void PublicTransport_dtor(PublicTransport_t *this_)
{
    --PublicTransport_g_s_count;
    printf("PublicTransport::Dtor()%d\n", this_->m_license_plate);
}

void PublicTransport_cctor(PublicTransport_t *mem_, PublicTransport_t *other_)
{
    mem_->v_ptr = g_PublicTransport_vtbl;
    mem_->m_license_plate = ++PublicTransport_g_s_count;
    printf("PublicTransport::CCtor()%d\n", mem_->m_license_plate);
}

void PublicTransport_Display_this(PublicTransport_t *this_)
{
    printf("PublicTransport::display():%d\n", this_->m_license_plate);
}

void PublicTransport_PrintCount()
{
    printf("s_count: %d\n", PublicTransport_g_s_count);
}

int PublicTransport_GetID_this(PublicTransport_t *this_)
{
    return this_->m_license_plate;
}

/************************** Minibus Funcs *****************************/

void Minibus_ctor(Minibus_t *mem_)
{
    PublicTransport_ctor(&mem_->m_base);
    *(void(***)(Minibus_t *))mem_ = g_Minibus_vtbl;
    mem_->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void Minibus_dtor(Minibus_t *this_)
{
    *(void(***)(Minibus_t *))this_ = g_Minibus_vtbl;
    printf("Minibus::Dtor()\n");
    PublicTransport_dtor(&this_->m_base);
}

void Minibus_cctor(Minibus_t *mem_, Minibus_t *other_)
{
    PublicTransport_cctor(&mem_->m_base, &other_->m_base);
    *(void(***)(Minibus_t *))mem_ = g_Minibus_vtbl;
    mem_->m_numSeats = other_->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void Minibus_Display_this(Minibus_t *this_)
{
    printf("Minibus::display() ID:%d", PublicTransport_GetID_this(&this_->m_base));
    printf(" num seats:%d\n", this_->m_numSeats);
}

void Minibus_Wash_this(Minibus_t* this_, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, 
    PublicTransport_GetID_this(&this_->m_base));
}

/************************** Taxi Funcs *****************************/

void Taxi_ctor(Taxi_t *mem_)
{
    PublicTransport_ctor(&mem_->m_base);
    *(void(***)(Taxi_t *))mem_ = g_Taxi_vtbl;
    printf("Taxi::Ctor()\n");
}

void Taxi_dtor(Taxi_t *this_)
{
    *(void(***)(Taxi_t *))this_ = g_Taxi_vtbl;
    printf("Taxi::Dtor()\n");
    PublicTransport_dtor(&this_->m_base);
}

void Taxi_cctor(Taxi_t *mem_, Taxi_t *other_)
{
    PublicTransport_cctor(&mem_->m_base, &other_->m_base);
    *(void(***)(Taxi_t *))mem_ = g_Taxi_vtbl;
    printf("Taxi::CCtor()\n");
}

void Taxi_Display_this(Taxi_t *this_)
{
    printf("Taxi::display() ID:%d\n", PublicTransport_GetID_this(&this_->m_base));
}

/************************** SpecialTaxi Funcs *****************************/

void SpecialTaxi_ctor(SpecialTaxi_t *mem_)
{
    Taxi_ctor(&mem_->m_base);
    *(void(***)(SpecialTaxi_t *))mem_ = g_SpecialTaxi_vtbl;
    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxi_dtor(SpecialTaxi_t *this_)
{
    *(void(***)(SpecialTaxi_t *))this_ = g_SpecialTaxi_vtbl;
    printf("SpecialTaxi::Dtor()\n");
    Taxi_dtor(&this_->m_base);
}

void SpecialTaxi_cctor(SpecialTaxi_t *mem_, SpecialTaxi_t *other_)
{
    Taxi_cctor(&mem_->m_base, &other_->m_base);
    *(void(***)(SpecialTaxi_t *))mem_ = g_SpecialTaxi_vtbl;
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxi_Display_this(SpecialTaxi_t *this_)
{
    printf("SpecialTaxi::display() ID:%d\n", PublicTransport_GetID_this(&this_->m_base.m_base));
}

/************************** PublicConvoy Funcs *****************************/

void PublicConvoy_ctor(PublicConvoy_t *mem_)
{
    Minibus_t *m1 = malloc(sizeof(Minibus_t));
    Taxi_t *t1 = malloc(sizeof(Taxi_t));
    
    PublicTransport_ctor(&mem_->m_base);
    *((void(***)(PublicConvoy_t *))mem_) = g_PublicConvoy_vtbl;
    
    Minibus_ctor(m1);
    mem_->m_pt1 = (PublicTransport_t *)m1;
    Taxi_ctor(t1);
    mem_->m_pt2 = (PublicTransport_t *)t1;
    
    Minibus_ctor(&mem_->m_m);
    Taxi_ctor(&mem_->m_t);
}

void PublicConvoy_dtor(PublicConvoy_t *this_)
{
    *((void(***)(PublicConvoy_t *))this_) = g_PublicConvoy_vtbl;
    Minibus_dtor((Minibus_t *)this_->m_pt1);
    free(this_->m_pt1); this_->m_pt1 = NULL;
    Taxi_dtor((Taxi_t *)this_->m_pt2);
    free(this_->m_pt2); this_->m_pt2 = NULL;
    Taxi_dtor(&this_->m_t);
    Minibus_dtor(&this_->m_m);
    PublicTransport_dtor(&this_->m_base);
}

void PublicConvoy_cctor(PublicConvoy_t *mem_, PublicConvoy_t *other_)
{
    PublicTransport_cctor(&mem_->m_base, &other_->m_base);
    *((void(***)(PublicConvoy_t *))mem_) = g_PublicConvoy_vtbl;
    
    mem_->m_pt1 = malloc(sizeof(Minibus_t));
    Minibus_cctor((Minibus_t *)mem_->m_pt1, (Minibus_t *)other_->m_pt1);
    
    mem_->m_pt2 = malloc(sizeof(Taxi_t));
    Taxi_cctor((Taxi_t *)mem_->m_pt2, (Taxi_t *)other_->m_pt2);

    Minibus_cctor(&mem_->m_m, &other_->m_m);
    Taxi_cctor(&mem_->m_t, &other_->m_t);
}

void PublicConvoy_Display_this(PublicConvoy_t *this_)
{
    this_->m_pt1->v_ptr[1](this_->m_pt1);
    this_->m_pt2->v_ptr[1](this_->m_pt2);
    Minibus_Display_this(&this_->m_m);
    Taxi_Display_this(&this_->m_t);
}


/****************************** Other Funcs ******************************/

void PrintInfo_Minibus(Minibus_t *m)
{
    Minibus_Wash_this(m, 3);
}

void PrintInfo_Int(PublicTransport_t *mem_)
{
    Minibus_t ret;
    Minibus_ctor(&ret);
    printf("print_info(int i)\n");
    Minibus_Display_this(&ret);
    PublicTransport_cctor(mem_, &ret.m_base);
    Minibus_dtor(&ret);
}

void PrintInfo_PublicTransport(PublicTransport_t *pt)
{
    pt->v_ptr[1](pt);
}

void Taxi_Display(Taxi_t *t)
{
    Taxi_Display_this(t);
}

/********************************* Main **********************************/

int main()
{
/************************* Variable Declerations *************************/
    Minibus_t m1 = {0};
    PublicTransport_t p1 = {0};
    
    Minibus_t *arr[2];
    Taxi_t *t1 = NULL;

    PublicTransport_t arr2[3] = {0};
    Minibus_t m2 = {0};
    Taxi_t t2 = {0};

    Minibus_t m3 = {0};
    
    Minibus_t arr3[4] = {0};
    Taxi_t *arr4 = NULL;

    SpecialTaxi_t st;
    Taxi_t copy;

    PublicConvoy_t *pc = NULL;
    PublicConvoy_t *pc2 = NULL;

/****************************** Invocations ******************************/
    Minibus_ctor(&m1);
    PrintInfo_Minibus(&m1);
    PrintInfo_Int(&p1);
    PublicTransport_Display_this(&p1);
    PublicTransport_dtor(&p1);

    arr[0] = malloc(sizeof(Minibus_t));
    Minibus_ctor(arr[0]);
    t1 = malloc(sizeof(Taxi_t));
    Taxi_ctor(t1);
    arr[1] = malloc(sizeof(Minibus_t));
    Minibus_ctor(arr[1]);


    arr[0]->m_base.v_ptr[1]((PublicTransport_t *)arr[0]);
    t1->m_base.v_ptr[1]((PublicTransport_t *)t1);
    arr[1]->m_base.v_ptr[1]((PublicTransport_t *)arr[1]);

    Minibus_dtor(arr[0]);
    free(arr[0]);
    Taxi_dtor(t1);
    free(t1);
    Minibus_dtor(arr[1]);
    free(arr[1]);

    Minibus_ctor(&m2);
    PublicTransport_cctor(&arr2[0], &m2.m_base);
    Minibus_dtor(&m2);
    Taxi_ctor(&t2);
    PublicTransport_cctor(&arr2[1], &t2.m_base);
    Taxi_dtor(&t2);
    PublicTransport_ctor(&arr2[2]);

    PublicTransport_Display_this(&arr2[0]);
    PublicTransport_Display_this(&arr2[1]);
    PublicTransport_Display_this(&arr2[2]);

    PrintInfo_PublicTransport(&arr2[0]);
    
    PublicTransport_PrintCount();
    Minibus_ctor(&m3);
    PublicTransport_PrintCount();

    Minibus_ctor(&arr3[0]);    
    Minibus_ctor(&arr3[1]);    
    Minibus_ctor(&arr3[2]);    
    Minibus_ctor(&arr3[3]);  

    arr4 = malloc(sizeof(Taxi_t) * 4);
    Taxi_ctor(&arr4[0]);
    Taxi_ctor(&arr4[1]);
    Taxi_ctor(&arr4[2]);
    Taxi_ctor(&arr4[3]);
    Taxi_dtor(&arr4[3]);
    Taxi_dtor(&arr4[2]);
    Taxi_dtor(&arr4[1]);
    Taxi_dtor(&arr4[0]);

    printf("%d\n", (1 > 2) ? 1 : 2);
    printf("%d\n", (1 > 2.0f) ? 1 : 2);

    SpecialTaxi_ctor(&st);
    Taxi_cctor(&copy, &st.m_base);
    Taxi_Display(&copy);
    Taxi_dtor(&copy);

    pc = malloc(sizeof(PublicConvoy_t));
    PublicConvoy_ctor(pc);

    pc2 = malloc(sizeof(PublicConvoy_t));
    PublicConvoy_cctor(pc2, pc);

    pc->m_base.v_ptr[1]((PublicTransport_t *)pc);
    pc2->m_base.v_ptr[1]((PublicTransport_t *)pc2);

    PublicConvoy_dtor(pc);
    free(pc);

    pc2->m_base.v_ptr[1]((PublicTransport_t *)pc2);

    PublicConvoy_dtor(pc2);
    free(pc2);

    SpecialTaxi_dtor(&st);
    Minibus_dtor(&arr3[3]);
    Minibus_dtor(&arr3[2]);
    Minibus_dtor(&arr3[1]);
    Minibus_dtor(&arr3[0]);

    Minibus_dtor(&m3);

    PublicTransport_dtor(&arr2[2]);
    PublicTransport_dtor(&arr2[1]);
    PublicTransport_dtor(&arr2[0]);

    Minibus_dtor(&m1);




    return 0;
}