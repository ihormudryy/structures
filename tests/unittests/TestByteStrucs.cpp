#include <gtest/gtest.h>
#include <memory>
#include <math.h> 
#include <limits> 
#include "stack/stack.h"
#include "queue/queue.h"

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

#define HW(name) cout<<"Hello World " << name <<endl

class String
{
public:
    String(){};
    String(String& arg)
    {
        _getLength(arg.value);
        value = arg.value;
    };
    String(char* c)
    {
        _getLength(c);
        value = c;
    };
    String operator=(char* c)
    {
        _getLength(c);
        value = c;
		return *this;
    };
    int length(){
        return _length;
    };
    void print(){std::cout << value << std::endl;};
    friend std::ostream& operator<<(std::ostream& o, const String& s){
        return o << s.value;
    };
    char operator[](int i){
        char res;
        res = *(value+i);
        return res;
    };
private:
    char* value;
    int _length = 0;
    void _getLength(char* c)
    {
        char tmp;
        while (tmp = *c++)
        {
            _length++;
        }
    };
};

using namespace std;

struct b_struct
{
	int power = 0;
	int mantissa;
};

void testReloading(int& q)
{
    cout << "Called by reference " << q << endl;
}

void testReloading(int* q)
{
    cout << "Called by pointer " << q << endl;
}

void setValueToReference(int a, int& b, const int& c = 0)
{
    a += 10;
    b += 200;
}

void flipInts(int* a, int* b = 0)
{
	int tmp = *b;
	*b = *a;
	*a = tmp;
}

const char* base = "0";
const int m = (int)*base;
int toInt(char* string)
{
    int res = 0;
    do
    {
       res *= 10;
       int digit = (int)*string;
       cout << digit << endl;
       res += digit % m;
    } while(*++string);
    return res;
}

char* parseString(int number)
{
    int grade = 0;
    int cp_num = number;
    do{ grade++; cout << cp_num << " ";} while ((cp_num /= 10) > 0);

    char* res = new char[grade + 1];

    int tmp = 0;
    while (number > 0)
    {
        tmp = number % 10;
        number /= 10;
        char val = (char)(tmp + m);
        res[--grade] = val;
        cout << number << endl;
    }
    return res;
}

b_struct parseDouble(double v)
{
	b_struct res;
	double tmp_val = v;
    while (tmp_val - floor(tmp_val) >= 1.0e-6)
	{
		res.power++;
		tmp_val *= 10;
	}
	res.mantissa = tmp_val;
	return res;
};

TEST(TestByteStruct, simpleStructrure)
{
    char t = 0;
    for (int i = 0; i < 128; i++)
    {
        t = i;
        if ((t >= 'a' && t <= 'z') || (t >= '0' && t <= '9'))
            cout << t << " = " << (int)t << " ";
    }
	cout<<endl;
	double* doub = new double(243454412e-5);
	b_struct instance = parseDouble(*doub);
	cout << "power -" << instance.power << endl;
	cout << "mantissa " << instance.mantissa << endl;
	int m = 2 << 31;
	cout << "Max int " << m << endl;
	int* a1 = new int(195485);
	int* b1 = new int(578323);
	flipInts(a1, b1);
	cout << "A " << *a1 << " B " << *b1 << endl;
	int& a2 = *b1;
	int& b2 = *a1;
	flipInts(&a2, &b2);
	cout << "A " << *a1 << " B " << *b1 << endl;
}

TEST(TestByteStruct, limits)
{
	cout << "int max " << numeric_limits<int>::max() << " min " << numeric_limits<int>::min() << endl;
	cout << "char max " << (int)numeric_limits<char>::max() << " min " << (int)numeric_limits<char>::min() << endl;
	cout << "short max " << numeric_limits<short>::max() << " min " << numeric_limits<short>::min() << endl;
	cout << "long max " << numeric_limits<long>::max() << " min " << numeric_limits<long>::min() << endl;
	cout << "float max " << numeric_limits<float>::max() << " min " << numeric_limits<float>::min() << endl;
	cout << "double max " << numeric_limits<double>::max() << " min " << numeric_limits<double>::min() << endl;
	cout << "unsigned max " << numeric_limits<unsigned>::max() << " min " << numeric_limits<unsigned>::min() << endl;
	cout << "bool max " << numeric_limits<bool>::max() << " min " << numeric_limits<bool>::min() << endl;
}

TEST(TestByteStruct, arrays)
{
	double dbarr[3] = { 1.45, 53.42, 1.3e-3 };
	double* s = dbarr;
	cout << "First " << *s << endl;
	cout << "INTEGERS" << endl;

	int intarr[4] = { 1, 52, 3, 19 };
	int* a = intarr;
	cout << "First int " << *a << endl;
    cout << "ToInt " << toInt("100412") << endl;
    char* string = parseString(4823923);
    cout << "parseString 4823923 == " << string << endl;
}

TEST(TestByteStruct, references)
{
    int a0 = 2;
    int a1 = 2;
    setValueToReference(a0, a1);
    cout << "a0 was 2 " << a0 << " a1 was 2 " << a1 <<endl;
    setValueToReference(a1, a0);
    cout << "a1 was 202 " << a1 <<endl;
}

TEST(TestByteStruct, testReload)
{
    int g = 10;
    testReloading(g);
    testReloading(&g);
    void (*efct)(int, int&, const int&);
    efct = &setValueToReference;
    cout << "Pointer to function " << efct << endl;
    (*efct)(g,g, 10);
	cout << "Pointer to function called " << g << endl;
    HW("FML");
}

TEST(TestByteStruct, testUnion)
{
    struct simple
    {
        int a;
        int b;
    };
    simple s;
    s.a = 1;
    ASSERT_TRUE(s.a == 1);
    s.b = 1234;
    ASSERT_TRUE(s.b == 1234);
}

TEST(TestByteStruct, testDestructor)
{
	class abstr
	{
		virtual void cool() = 0;
		virtual int random() = 0;
	};
	class base
	{
		
	public:
		enum check
		{
			IGOR, VASYA
		};
		base(const int& i = 0){ val = i; };
		~base(){
			cout << "Destructor called" << endl;
		};
		check current; 
		virtual void print(){ cout << "print value " << this->val << " CURRENT " << current << endl; };
		virtual void down(){ cout << "BASE COOL" << endl; };
	protected:
		void outter(){ cout << "PROTECTED METHOD " << endl; };
	private:
		int val;
	};

	class derived : base, abstr
	{
	public:
		void cool(){};
        int random(){ return 9; }; // very unexpected :)
		derived(const base::check value, const int& i = 0) : base(i){ _base.current = value; };
		void print(){ _base.print(); base::outter(); };
	private:
		base _base;
	};
	
	base* instance1 = new base(2);
	delete instance1;
	base instance2;
	base instance3;
	base* instance4 = &instance2;
	
	derived der(base::check::IGOR, 5154);
	der.print();
}

TEST(TestByteStruct, testVirtualMethods)
{
	class virt1
	{
	public:
		~virt1(){ cout << "Virt1 destructor" << endl; };
		virtual void draw(){ cout << "Vir1 draw() " << endl; };
	};
	class virt2
	{
	public:
		virtual void draw(){ cout << "Vir2 draw() " << endl; };
		//virtual void temp() = 0;
	};
	class virtDerived : public virt1, virt2
	{
	public:
		//virtDerived(){};
		//~virtDerived(){};
		void operator delete(void*, size_t)
		{
			cout << "Virtual destructor " << endl;
		};
		void draw()
		{
			virt1::draw();
			virt2::draw();
		}
	};
	virtDerived d;
	d.draw();
	virt1* d_ptr = new virtDerived();
	cout << "Base class " << endl;
	d_ptr->draw();
	delete d_ptr;
	//virt1* v = d;
	//v->draw();
}

TEST(TestByteStruct, testOverloadOperators)
{
    class simple
    {
        int v;
        int f;
    public:
        simple(){};
        simple(int arg){v = arg;};
        int get(const char* ...){return v;};
        simple& operator=(int a){v = a; return *this;};
        void operator+=(int s){this->v += s;};
        operator char(){return (char)v;};
    };
    simple k(10);
    k += 39;
	const char* sd = "asd";
	ASSERT_EQ(k.get(sd, sd), 49);
    char c = k;
    cout << c << endl;
    simple z(344);
    z = 1034;
    z = 483;
	cout << z.get(sd, sd) << endl;
	ASSERT_EQ(z.get(sd, sd), 483);
}
short x = 4, i = 0;
void fun1()
{  if (i == 0) throw 2; }
int fun2()
{ --x; fun1();  x++; return x; }

TEST(TestByteStruct, testCustomStringClass)
{
    String s1("igorko");
    String s2 = s1;
    s1.print();
    s2 = "mudryypaokrje";
    s1.print();
    s2.print();
    String s3(s2);
    s3 = "superwise";
    s3.print();
    cout << s1 << " Size " <<  s1.length() << endl;
    cout << s2 << " Size " <<  s2.length() << endl;
    cout << "second " << s2[1] << endl;
	//cout << sa.length() << endl;
    char* pass;
    cout << "Password:" << endl;
    cout.flush();
    try
    {
        fun2();
    }
    catch (int)
    {
        cout << "Exception ";
    }
    cout << x << " " << i;
}

TEST(TestByteStruct, testHouseOfCards)
{
    using namespace customalgorithms;
    Stack<int> s;
    Queue<int> q();
    int a[56];
    for(int i = 0; i < 56; i++)
        a[i] = -1;
    int counter = 0;
    while (counter < 56)
    {
        int val = rand() % 56;
        if(a[val] == -1)
        {
            s.push(val);
            a[val] = 1;
            counter++;
        }
    }
    cout << "Size " << s.size() << endl;
    //while(s.size() > 0) cout << s.pop() << " ";
    cout << endl;
    /*
    while (q.size() < 56)
    {
        int v1 = s.pop();
        int v2 = s.pop();
        while(v1 < v2)
        {
            q.enqueue(v2);
            v2 = s.pop();
        }
        else 
    }
    */
}
