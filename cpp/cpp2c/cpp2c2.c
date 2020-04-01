

struct Y__vtbl;


struct Y
{
	struct Y__vtbl* v_ptr;
	
	struct X m_x;
	int m_a;
}

struct Der
{
	struct Y base;
	X m_x2;
};

void Der__ctor(Der* mem_)
{
	Y__ctor( mem_ );
	X_ctor( &( mem_->m_x2 ) );
	
	*(Der__vtbl**)mem_=g_Der_vtbl;
}

void Der__dtor(Der* this_)
{
}


struct Y__vtbl
{
	void(*Dtor)(Y*);
	void(*Foo_this)(void*);
	int (*Calc_const_this)(const Y*)
};

struct Der__vtbl
{
	struct Y__vtbl basevt;
	void (*Dodo_this)(Der*);
}

const Y__vtbl g_Y_vtbl={	&Y__dtor, &Y__Foo_this, &Y__Calc_const_this };

const Der__vtbl g_Der_vtbl={	{ ()&Der__dtor, &Y__Foo_this, ()&Der__Calc_const_this  }, &Der__Dodo_this };



void Y__Bar_const_this(const Y*);
void Y__Foo_this(Y*);
int Y__Calc_const_this(const Y*);

void Y__ctor(Y* mem_)
{
	mem_->v_ptr= &g_Y_vtbl;
	
	X_ctor( &(mem_->m_x) );
}

void Y__dtor( Y* this_ )
{
	X_dtor( this_);
}


void Fifi_Yref( Y*  y_)
{
	Y__Bar_const_this(y_);
	
	y_->v_ptr->Foo_this(y_);
}

void ByVal_Y(struct Y* y_)
{
	Y__Foo_this(y_);
}

int main()
{
	
	struct Y y1;
	struct Der d1;
	struct DerDerDerDer d2;
	struct Y tmp_y;
	
	Y__ctor(&y1);
	Der__ctor(&d1);
	
	Y__cctor(&tmp_y, &y1);
	ByVal_Y( &tmp_y );
	Y__dtor(&tmp_y);
	
	Y__Bar_const_this(&y1);
	
	Y__Foo_this(&y1)
	
	
	Fifi_Yref(&y1);
	
	Fifi_Yref(&d1);
	
	Der_dtor(&d1);
	Y__dtor(&y1);
	
	return 0;
}























