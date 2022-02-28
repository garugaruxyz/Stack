#include <iostream>
#include <ostream>
#include "Mystack.h"

struct point {
	int x; ///< coordinata x del punto
	int y; ///< coordinata y del punto

	point(int xx, int yy) : x(xx), y(yy) {}

    point(int value) : x(value), y(value) {}

    point(){}
};

struct greaterthan {
    greaterthan(int value) : i(value){}
	bool operator()(const int &a) const { return (a > i); }
    private: 
        int i;
};

struct lessthan
{
    lessthan(int value) : i(value){}
	bool operator()(const int &a) const { return (a < i); }
    private: 
        int i;
};


std::ostream &operator<<(std::ostream &os, const point &p) {
	std::cout<<"("<<p.x<<","<<p.y<<")";
	return os;
}

typedef Mystack<int> intero;
typedef Mystack<std::string> stringa;
typedef Mystack<point> punto;

void test_mystack_cstr() {

    std::cout << "\033[1;31mTEST COSTRUTTORE\033[0m" << std::endl;

    intero::const_iterator begini, endi;
    punto::const_iterator beginp, endp;
    stringa::const_iterator begins, ends;
    int a[5] = {10,11,12,13,14};

    std::cout << "Costruttore con iteratore (int) : " << std::endl;
	intero provaII(a,a+5);
    std::cout << "Copycostructor provaII2(provaII)" << std::endl;
    intero provaII2(provaII);
    std::cout << "Stampa tutto lo stack dalla cima" << std::endl;
	for(begini = provaII2.begin(), endi = provaII2.end(); begini!=endi; begini--)
		std::cout << *begini << std::endl;
    
    std::cout << "(int)In cima ho : " << provaII2.peek() << std::endl;
    
    std::cout << "\nCostruttore con iteratore (point) : " << std::endl;
	point b[5] = {point(1,2),point(3,4),point(5,6),point(13),point(14)};
	punto provaPP(b,b+5);
    std::cout << "Stampa tutto lo stack dalla cima" << std::endl;
	for(beginp = provaPP.begin(), endp = provaPP.end(); beginp!=endp; beginp--)
		std::cout << *beginp <<std::endl;

    std::cout << "(point)In cima ho : " << provaPP.peek() << std::endl;

    std::cout << "\nCostruttore con iteratore (string) : " << std::endl;
	std::string c[5] = {"ciao","test","costruttore","con","string"};
	stringa provaSS(c,c+5);
    std::cout << "Stampa tutto lo stack dalla cima" << std::endl;
	for(begins = provaSS.begin(), ends = provaSS.end(); begins!=ends; begins--)
		std::cout << *begins << std::endl;

    std::cout << "(string)In cima ho : " << provaSS.peek() << std::endl;
}
void test_push_pop(){
    std::cout << "\n\033[1;31mTEST PUSH & POP\033[0m" << std::endl;
    std::cout << "PUSH & POP (int) : " << std::endl;
    intero provaII;
    provaII.push(1);
    provaII.push(2);
    provaII.push(3);
    provaII.push(4);

    intero::const_iterator begin, end;

    std::cout << "\nStampa tutto lo stack dalla cima" << std::endl;
	for(begin = provaII.begin(), end = provaII.end(); begin!=end; begin--)
		std::cout << *begin << std::endl;
    std::cout << "(int)In cima ho : " << provaII.peek() << std::endl;

    std::cout << "\nPOP  : " << provaII.pop() << std::endl;
    std::cout << "POP  : " << provaII.pop() << std::endl;

    std::cout << "\nStampa tutto lo stack dalla cima" << std::endl;
	for(begin = provaII.begin(), end = provaII.end(); begin!=end; begin--)
		std::cout << *begin << std::endl;
    
    std::cout << "(int)In cima ho : " << provaII.peek() << std::endl;
}
void test_removeif(){
    std::cout << "\n\033[1;31mTEST REMOVE IF\033[0m" << std::endl;
    intero provaII;
    provaII.push(1);
    provaII.push(2);
    provaII.push(3);
    provaII.push(4);
    std::cout << "Remove if greaterthan 2" << std::endl;
    greaterthan gr2(2);
    provaII.removeif(gr2);

    intero::const_iterator begin, end;
    std::cout << "Stampa tutto lo stack dalla cima" << std::endl;
	for(begin = provaII.begin(), end = provaII.end(); begin!=end; begin--)
		std::cout << *begin << std::endl;
}
void test_svuota(){
    std::cout << "\n\033[1;31mTEST SVUOTA STACK\033[0m" << std::endl;
    intero provaII;
    provaII.push(1);
    provaII.push(2);
    provaII.push(3);
    provaII.push(4);
    std::cout << "(int)Size prima : " << provaII.getSize() << std::endl;
    provaII.svuota();
    std::cout << "(int)Size dopo svuota() : " << provaII.getSize() << std::endl;

    point b[5] = {point(1,2),point(3,4),point(5,6),point(13),point(14)};
	punto provaPP(b,b+5);
    std::cout << "\n(point)Size prima : " << provaPP.getSize() << std::endl;
    provaPP.svuota();
    std::cout << "(point)Size dopo svuota() : " << provaPP.getSize() << std::endl;

    std::string c[5] = {"ciao","test","costruttore","con","string"};
	stringa provaSS(c,c+5);
    std::cout << "\n(string)Size prima : " << provaSS.getSize() << std::endl;
    provaSS.svuota();
    std::cout << "string)Size dopo svuota() : " << provaSS.getSize() << std::endl;
}
void test_riempi(){
    std::cout << "\n\033[1;31mTEST RIEMPI\033[0m" << std::endl;
    intero::const_iterator begini, endi;
    int a[5] = {1, 2, 3, 4, 5};
    int b[5] = {6, 7, 8, 9, 10};

    std::cout << "Costruttore con iteratore (int) : " << std::endl;
	intero provaII(a,a+5);
    std::cout << "Stampa tutto lo stack dalla cima" << std::endl;
	for(begini = provaII.begin(), endi = provaII.end(); begini!=endi; begini--)
		std::cout << *begini << std::endl;
    
    std::cout << "\nEseguo riempistack()" << std::endl;
    provaII.riempiStack(b, b+5);
    std::cout << "Stampa tutto lo stack dalla cima" << std::endl;
	for(begini = provaII.begin(), endi = provaII.end(); begini!=endi; begini--)
		std::cout << *begini << std::endl;
}
void test_underflow(){
    std::cout << "\033[1;31mTEST UNDERFLOW\033[0m" << std::endl;

    intero::const_iterator begini, endi;
    int a[5] = {10,11,12,13,14};

    std::cout << "Costruttore con iteratore (int) : " << std::endl;
	intero provaII(a,a+5);
    std::cout << "Stampa tutto lo stack dalla cima" << std::endl;
	for(begini = provaII.begin(), endi = provaII.end(); begini!=endi; begini--)
		std::cout << *begini << std::endl;
    
    std::cout << "POP : " << provaII.pop() << std::endl;
    std::cout << "POP : " << provaII.pop() << std::endl;
    std::cout << "POP : " << provaII.pop() << std::endl;
    std::cout << "POP : " << provaII.pop() << std::endl;
    std::cout << "POP : " << provaII.pop() << std::endl;
    std::cout << "Dimensione stack : " << provaII.getSize() << std::endl;
    //std::cout << "POP : " << provaII.pop() << std::endl; //Con questa pop viene terminato il programma, togliere il commento per testare
}

int main() {
    test_mystack_cstr();
    test_push_pop();
    test_removeif();
    test_svuota();
    test_riempi();
    test_underflow();
    return 0;
}