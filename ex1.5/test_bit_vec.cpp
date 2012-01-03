#include <iostream>
#include <stdexcept>

#include "bit_vector.h"

int main() {

    Vector<bool> v;           // ok: defaultkonstruktor ger vektor med flyttal
    Vector<bool> *a = new Vector<bool>[3];  // dynamiskt allokerade ser ut så här
    delete [] a;

    assert(v.size() == 0);      // tom från början
    v.push_back(true);          // lägg till ett element sist
    assert(v.size() == 1);      // nu ligger ett element i vektorn
    v.push_back(false);
    assert(v.size() == 2);
    assert(v[0] == true
    	&& v[1] == false);
    
    v.sort(false);              // sortera i fallande ordning
    assert(v[0] == true &&      // hamnade de rätt?
		v[1] == false);       
    assert(v.size() == 2);      // ingenting ändrat?
    v[1] = false;                // tilldelning av enstaka element;

    const Vector<bool> &vc = v;  // skapa konstant referens
    assert(vc.size() == 2);     // ok: ändrar ej vektorn som är konstant
    assert(vc[0] == true &&     // ok: ändrar ej vektorn som är konstant
	   vc[1] == false);
    
    v.clear();                  // töm hela vektorn
    assert(v.size() == 0);      // tom när alla element är borttagna

    Vector<bool> three(3);
    three[0] = true;
    three[1] = false;
    three[2] = true;
    // TODO
    three.sort();
    assert(three[0] == true);
    assert(three[1] == true);
    assert(three[2] ==false);

    // kontrollera att följande rader inte går att kompilera COMPLETED
    #if 0

   	vc[0] = true;             // fel: tilldelning av konstant objekt
    Vector<char> c = v;         // fel: tilldelning av olika typer
    vc.sort();                  // fel: ändrar konstant objekt

    #endif

    Vector<bool> vv(31, false); // Skapa en 31 stor vektor
	vv[3] = true;
	assert(vv[3] == true);

	Vector<bool> w;		// tom vektor
	// TODO
	// std::copy(vv.begin(), vv.end(), std::back_inserter(w));
	// std::cout << std::distance(vv.begin(), vv.end()); // konstant iterator och konvertering
	Vector<bool>::const_iterator it = vv.begin();
	std::advance(it, 2);
	assert(*it == false);
	
	std::advance(it, 1);
	assert(*it == true);

    return 0;
}