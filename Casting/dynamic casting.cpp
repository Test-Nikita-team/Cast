
#include <iostream>
using namespace std;
class Base
{
protected:
	int value;
public:
	Base(int value_ = 10) : value(value_)
	{}
	void SetValue(int value_)
	{
		value = value_;
	}
	int GetValue() const
	{
		return value;
	}
	virtual void Show()const
	{
		cout << "Virtual Show() is working( from Base )\n";
	}
};
class Derived : public Base
{
public:
	Derived(int value_ = 100) : Base(value_)
	{}
	void Show()const
	{
		cout << "Virtual Show() is working( from Derived )\n";
	}
	virtual void Show2()const // !!! �������� � ���� Derived, � Base �� �� �� ����
	{
		cout << "Virtual Show2() is working( from Derived )\n";
	}

};
class SuperDerived : public Derived
{
public:
	SuperDerived(int value_ = 1000) :Derived(value_)
	{}
	virtual void Show3()
	{
		cout << "Virtual Show3() is working( from SuperDerived )\n";

	}
};
#define Line cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
int main()
{
	
	cout << "\n\t\tDYNAMIC_CAST<TYPE *>\n";
	
	Base * pbase = new  Derived(33);// 
	Base *pB = new Base(11);
	Derived * pD;
	if (pD = dynamic_cast<Derived *>(pbase)) // ���������� ���������������  ��� ���������� �����(���������� ����= ������ ��� �������)
	{
		pD->Show(); //���� ������������ ������, ����� pbase �������� ������ ������ ����� ����� Derived * �� ��������� �� �����
		pD->Show2();
	}
	else
	{
		cout << "Untenable casting\n";

	}

	if (pD = dynamic_cast<Derived *>(pB)) //�� ������� ��������
	{
		pD->Show();
		pD->Show2();
	}
	else
	{
		cout << "\nUntenable casting dynamic_cast<Derived *>(pB)\n"; //��������� ����

	}
	Line
	Base *  arr[3] = { new Base(11), new Derived(22), new SuperDerived(32) };
	SuperDerived *pS;
	for (int i = 0; i < 3; ++i)
	{
		cout << "\n\tObject # " << i << "\n";
		arr[i]->Show();
		if (pD = dynamic_cast<Derived*>(arr[i]))
			pD->Show2();
		if (pS = dynamic_cast<SuperDerived *>(arr[i]))
			pS->Show3();

		
	}
	Line
	cout << "\n\t\tDYNAMIC_CAST<TYPE &>\n";

	Base & ref = SuperDerived(5);// ����  ���������
	//Base & ref = Derived(5); // ���� ���������� ����������
	SuperDerived s;
	try // �������� ��������, �� �������� � ����� try
	{
		s = dynamic_cast<SuperDerived&> (ref); // ������, ���� ref ���������� �� SuperDerived(�� �������� �� �����), ������ ���������� ���������� ���� bad_cast
		s.Show2();
	}
	catch (bad_cast & e) // ������ ���������� ���� bad_cast
	{
		cout << e.what() << endl;  //������� - ������� what()  �����  bad_cast ������ �� ���������
	}
	
	Line
	cout << "\n\t\tTYPEID\n";
	cout << "\nType of 100 : " << typeid(100).name() << endl;
	cout << "Type of 100. : " << typeid(100.).name() << endl;
	
	cout << "\nType of pbase  = " << typeid(pbase).name() << endl;
	cout << "Type of *pbase  = " << typeid(*pbase).name() << endl;

	cout << "\nType of pB  = " << typeid(pB).name() << endl;
	cout << "Type of *pB  = " << typeid(*pB).name() << endl;

	Line
	if (typeid(*pbase) == typeid(*pB)) // 
		cout << "*pbase and  *pB are EQUAL type objects\n";
	else
		cout << "*pbase and  *pB are NOT  EQUAL type objects\n";
	
	
	if (typeid(*pbase) == typeid(*arr[1])) // 
		cout << "*pbase and  *arr[1] are EQUAL type objects\n";
	else
		cout << "*pbase and  *arr[1] are NOT  EQUAL type objects\n";
	
	

	for (auto i : arr)
		delete i;
	return 0;
}