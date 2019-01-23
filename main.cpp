//Liam Rotchford
//Oct 18 18

/* This program implements Dynamic binding (upcasting, downcasting). The specfic heiarchy is decribed in the transportation.h file description.
 * Using a DLL list, we allow the user to select from 3 rental unit vehicles (derived classes) and we then prompt for general data and then speacilized data based
 * on the rental type selected. We store that data intialized to a newly created object and then send it to be as the baseclass pointer in the DLL.
 * we allow an insertion to the list, remove one, remove all, determine total profit from list, display functionality with the list.
 */

#include "transportation.h"
using namespace std;

int main()
{
	manager object;		//DLL manager class object

	cout << "\n\no Welcome to the Personal Rental Vehicle List: " << endl;	
	cout << "\n======================================================================================" << endl;

	user_menu(object);	//begin program, sending it to user menu to learn about the program 

	return 0;
}

