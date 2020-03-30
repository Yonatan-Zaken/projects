class Y
{
public:
	virtual ~Y(){}
	virtual void Foo();	
	virtual int Calc()const;
	void Bar()const;
private:
	X m_x;
	int m_a;
};

class Der: public Y
{
public:
	virtual int Calc()const;
	virtual void Dodo();
private:
	X m_x2;
};
	



void Fifi( Y&  y_)
{
	
	y_.Bar();
	
	y_.Foo();
}

void ByVal(Y y_)
{
    y_.Foo();
}

Y RetVal()
{
    Y ret;

    ...
    
    return ret;    
}

int main()
{
	Y y1;
	
	Der d1;
	
	ByVal(y1);
	
	Y& yr= y1;
	
	yr.Bar();
	
	yr.Foo();
	
	Fifi(yr);
	
	Fifi(d1);
	
	Retval().Foo();
	
	return 0;
}








