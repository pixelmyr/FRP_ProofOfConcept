#include "WatchedPtr.h"

class Integer
{
public:
	Integer()
		: _val(0)
	{
	}

	Integer(int val)
		: _val(val)
	{
	}

	void Set(int val)
	{
		_val = val;
	}

	Integer operator+(const Integer &other)
	{
		return Integer(_val + other._val);
	}

	void Update(Integer *newVal)
	{
		_val += newVal->GetVal(); //For this demo we will increase by 1
	}

	int GetVal()
	{
		return _val;
	}

private:
	int _val;
};


void ChangeValue(Integer *intVal)
{
	intVal->Set(4);
	printf("%d\n", intVal->GetVal());
}

void Test(WatchedPtr<Integer> wB)
{
	printf("B has been set to ");
	ChangeValue(wB);
}

int main()
{
	Integer a, b;
	a.Set(10);
	b.Set(20);

	a = a + b;

	printf("A: %d\n", a.GetVal());
	printf("B: %d\n", b.GetVal());

	WatchedPtr<Integer> wA, wB;
	wA.Reset(&a);
	wB.Reset(&b);

	std::function<void(Integer *)> aCallback = std::bind(&Integer::Update, &a, std::placeholders::_1);
	wB.AddListener(&aCallback);

	Test(wB);

	printf("A's new value: %d\n", a.GetVal());

	getchar();
}