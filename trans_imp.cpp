//Liam Rotchford
//Oct 17 18

#include "transportation.h"
using namespace std;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ================== Node class setters and getters ====================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//set the data in the node (being sent derived class pointers to be stored in the varible point in the DLL)
void node::setdata(transportation * ptr)
{
	point = ptr;
}

transportation*& node::getpoint()
{
	return point;
}
//	setter and getter for next pointer
void node::setnext(node * temp)
{
	next = temp;
}

node *& node::gonext()
{
	return next;
}
//	setter and getter for previous pointer
void node::setprev(node * temp)
{
	previous = temp;
}

node *& node::goprev()
{
	return previous;
}

//+++++++++++++++++++++++++ NODE CLASS FUNCTIONS +++++++++++++++++++++++

//DELETE DATA IN THE NODE
//delete the contents of the node, of whatever node is calling it, (head->node_delete)
int node::node_delete()
{
	delete point;
	point = NULL;

	return 1;
};

//DOWNCAST AND CALL THE CHECK FUNCITON IN DERIVED CLASS FOR REMOVE ONE
//downcast to call the derived class dynamically bound check function to find a match of the unit ID number the user put in to remove one node
int node::node_check(int number)
{
	if(point)
	{
		scooter * sptr = dynamic_cast<scooter*>(point);		//cast to scooter derived function
		if(sptr)						//if we are currently a scooter pointer then enter if
		{	
			return sptr->check(number);			//call the scooter derived check function
		}

		bike * bptr = dynamic_cast<bike*>(point);		//same case for all three derived types
		if(bptr)
		{	
			return bptr->check(number);
		}

		zip_car * cptr = dynamic_cast<zip_car*>(point);
		if(cptr)
		{
			return cptr->check(number);
		}
	}
	return 0;
}
//DOWNCAST TO CALL THE GET PROFIT DERIVED FUNCTION FOR TOTAL PROFIT 
//downcast to determine what derived object is currently stored in the node that called this function and then call the dynamically bound derived function of 
// get profit to return the rental_cost varible stored in this node to add to a total sum to determine the total profit based on the current list
int node::get_profit()
{
	if(point)
	{
		scooter * sptr = dynamic_cast<scooter*>(point);		//downcast
		if(sptr)						//check if we are that derived type, call the dynamically bound get profit function
			return sptr->get_profit();			//in the derived class

		bike * bptr = dynamic_cast<bike*>(point);		//same for all
		if(bptr)
			return bptr->get_profit();
		
		zip_car * cptr = dynamic_cast<zip_car*>(point);
		if(cptr)
			return cptr->get_profit();

	}
	return 0;
}

//DOWNCAST TO CALL DERIVED DISPLAY FUNCTIONS
//this funciton is called on each cycle on the manager classes recursive diplay function to call the derived class object personal display so it can disp the 
//speacilized data, this downcasts and then calls the display in the correct derived class 
int node::node_display() const
{
	if(point)
	{
		scooter * sptr = dynamic_cast<scooter*>(point);		//downcast
		if(sptr)						//determine if we are that type RTTI
			sptr->display();				//call the the correct derived class display function

		bike * bptr = dynamic_cast<bike*>(point);		//same for all
		if(bptr)
			bptr->display();
		
		zip_car * cptr = dynamic_cast<zip_car*>(point);
		if(cptr)
			cptr->display();

		return 1;
	}
	return 0;
}



//==========================================================
//+++++++++++++++ MANAGER BASE CLASS (DLL MANAGER) +++++++++++++++++++++++
//==========================================================

//CONSTRUCTOR
//default constructor set head and tail to NULL
manager::manager() : head(NULL), tail(NULL)
{
}

//DECONSTRUCTOR
//deconstructor for the list, call the recursive deconstruct function to remove all nodes in the list
manager::~manager()
{
	if(head)
	{
		node * current = head;				//set current to be where our head is
		int val = deconstruct(head, current);		//recursive deconstructor function to delete entire list and all dynamic memory
		delete head;					//delete last head

		head = NULL;					//set head and tail to NULL
		tail = NULL;
	}
}

//REMOVE ALL
//user call deconstructor remove all fuction, to remove all nodes from the list, however calling this wont end the program
int manager::remove_all()
{
	if(head)
	{
		node * current = head;				//same system as the deconstructor as above but since the user cant and shouldn't be calling the 
		int val = deconstruct(head, current);		//deconstructor in this case we have the same code
		delete head;

		head = NULL;
		tail = NULL;
	}
	
	if(!head)					//make sure we determine if we fully removed the list or not
		return 1;
	else
		return 0;
}

//RECURSIVE REMOVE ALL FUNCTION
//recursive fuction for decostructor and remove all function above. delete the list from the head and cycle that until our head is null and list is 
//fully removed
int manager::deconstruct(node *& head, node *& current)
{
	if(!head)
		return 0;

	current = current->gonext();	//set current to be next node (going in it its the head)

	head->setprev(NULL);		//remove the previos pointer

	head->node_delete();		//send to the delete funciton in the node class to delete all dynamic in this node
	delete head;			//delete the node itself
	head = NULL;

	head = current;			//set head to where current it which is now the start of the list

	return deconstruct(head, current);	//call recursive 
}

//CREATE NEW NODE AND SET DATA BASED ON DERIVED POINTER SENT IN
//These three functions are for when we have created our data stored derived object in the support.cpp and are being sent a derived class pointer
//based on that pointer match on the argument list it will call one of these functions and perform upcasting, it will create a new node and set the 
//new derived pointer to be set onto the base class pointer in the node setter function as the DLL data, it will then send it to the DLL inserter function
//to add it to the list
int manager::insert(scooter * sobject)	
{	
	node * temp = new node;		//create new node for the DLL
	temp->setdata(sobject);		//set the base class pointer to point to a derived class object

	int val = inserter(temp);	//send new data set node to the add to list funciton

	return 1;
}

int manager::insert(bike * bobject)	//same as above	
{
	node * temp = new node;
	temp->setdata(bobject);	

	int val = inserter(temp);

	return 1;
}

int manager::insert(zip_car * cobject)	//same as above	
{
	node * temp = new node;
	temp->setdata(cobject);	

	int val = inserter(temp);

	return 1;
}

//INSERT THE NEW NODE INTO THE DLL
//this function adds the newly create node into our list, if our head and tail are currently null then make this new node the head and tail, since we now
//only have one node in the list, otherwise just add the new node in at the head to expand the list, changeing head and leaving tail pointer at the end of the list
int manager::inserter(node *& temp)
{	
	if(!head && !tail)	//list is currently empty
	{
		head = temp;		//set new node to be head and tail
		tail = temp;
		head->setnext(NULL);	//we are only one node list so next and previous is null
		head->setprev(NULL);
		temp = NULL;
	}else				//list is not empty
	{
		node * hold = head;	//hold the head with a new pointer
		temp->setnext(hold);	//set the new node to point at the old head as the next to the new node
		hold->setprev(temp);	//set the hold (where head is currently) and set the previous onto the new node
		head = temp;		//make the new node the new head
	}

	return 1;
}

//FIND THE MATCH UNIT ID NUMBER INPUTTED BY USER AND REMOVE THAT MATCH NODE FROM THE LIST
//this function will take in the user input for the matching unit id number in the list to match to one node they want removed. we will first check the head of the
//list for the match, if the first head is a match and we only have one node we will remove the node and be empty, if we arent one node list and our head is
//the match then we remove the head and set a new head. if we wernt the match and are a one node list then we return 0 that we didn't find it. otherwise we move 
//recursivly through the list in the other function so we can find a match
int manager::retrieve_remove_one(int number)
{
	if(!head)
		return 0;

	if(head->node_check(number))		//check for match in the node
	{
		if(head->gonext() == NULL && head->goprev() == NULL)	//if our head first node it the match and we are a one node list
		{
			head->node_delete();			
			delete head;
			head = NULL;
			tail = NULL;
		}else							//if our match is the first node and we are not a one node list
		{
			node * hold = head->gonext();			//remove the head and set the new head to be the next node

			head->node_delete();
			delete head;
			head = NULL;

			hold->setprev(NULL);
			head = hold;
		}	
		return 1;		//found our match and returned
	}else							//our head wasnt a match and we only have one node return 0 for no match found 
	{
		if(head->gonext() == NULL && head->goprev() == NULL)
			return 0;
	}
	
	return retrieve_remove_one(head, number);		//since our head is a non-match move on through the rest of the list
}

//RECURSIVLY FIND A MATCH TO REMOVE ONE NODE
//search through the list checking ahead one node for the match since we already know the first node is not the match, when and if we find a match, then we can use
//the node before the match to either reconnect the list or set the end of the list back to null. if the match is the last node in the list then remove it
//and set the new end to be null and next ot be null. if its in the middle remove and connect the list around the node that got removed
int manager::retrieve_remove_one(node *& head, int number)
{
	if(!head || head->gonext() == NULL)	//base case since we user check ahead and the match can be the end of the list we can end
		return 0;

	if(head->gonext()->node_check(number))	//check for match on the node ahead of the node we currently sit on
	{
		if(head->gonext() == tail)	//if the match is our tail then remove and reset the end of the list and the tail
		{
			tail->node_delete();
			delete tail;
			tail = NULL;
			head->setnext(NULL);
			tail = head;
		}else				//if we are in the middle of the list then remove the matrch and reconnect the list around the node removed
		{
			node * hold = head->gonext()->gonext();
			node * to_remove = head->gonext();

			to_remove->node_delete();
			delete to_remove;
			to_remove = NULL;

			head->setnext(hold);
			hold->setprev(head);
		}
		return 1;			//match found so return 1, 
	}

	return retrieve_remove_one(head->gonext(), number);	//recurse
}

//TOTAL PROFIT FUNCITON WRAPPER
//check for empty list, if not set val varible and send into the recursive function , return the val value as the total profit. 
int manager::total_profit()
{
	if(!head)
		return 0;
	
	int val = 0;
	total_profit(head, val);

	return val;
}
//TOTAL PROFIT RECURSIVE
//this will move through the entire list and go into the node to pull the rrental profit value and add it to val as a sum to determine the total profit
//from every rental vehicle in the list
int manager::total_profit(node *& head, int & val)
{
	if(!head)
		return 0;
	
	val += head->get_profit();	//get the rental profit value from every node and add it to the val varible to get the total money made
	
	return total_profit(head->gonext(), val);
}

//DISPLAY WRAPPER
//d
int manager::display()
{
	if(!head)
		return 0;

	int num = 1;	//to number each item in teh list
	cout << "\nO Rental Unit Data: " << endl;
	cout << "==========================================" << endl;

	return display(head, num);	//call display recurse
}

//DISPLAY RECURSIVE
//this function will move through the entire list and call the node display function from the node class with whereever the head is current on in the list
//the node function will downcast and determine what derived pointer is stored in that node and then it will call the derived display function so the 
//speacilized data is displayed
int manager::display(node * head, int & num) const
{
	if(!head)
		return 1;

	cout << "\no Rental Vehicle #" << num << "\n+++++++++++++++++++++++" << endl;	

	head->node_display();	//call node display to downcast and call derived dynamically bound diaply funciton

	return display(head->gonext(), ++num);
}

//==========================================================================
//+++++++++++++++++++++++++ TRASPORTATION ABSTRACT BASE CLASS ++++++++++++++
//==========================================================================

//this class acts as the glue for the three derived classes of rental types, it holds all similar data between the three

//CONSTRUCTOR
//set all data to intiliaze to null
transportation::transportation() : type(NULL), intersection(NULL), unit_ID(0), hours_rented(0), rental_profit(0), checked_out(false), repair_requested(false) 
{
}

//COPY CONSTRUCTOR
transportation::transportation(const transportation & source) : unit_ID(source.unit_ID), hours_rented(source.hours_rented), rental_profit(source.rental_profit),   checked_out(source.checked_out), repair_requested(source.repair_requested)
{
	type = new char[strlen(source.type) + 1];	//dynamic mem copies
	strcpy(type, source.type);

	intersection = new char[strlen(source.intersection)+1];
	strcpy(intersection, source.intersection);
}

//VIRTUAL DESTRUCTOR 
//remove the two dynamcic char * stored in the class
transportation::~transportation()
{
	delete [] type;
	type = NULL;

	delete [] intersection;
	intersection = NULL;

}

//CHECK VIRTAUL FUNCITON FOR REMOVE ONE 
int transportation::check(int number)
{
}
//GET PROFIT VIRTUAL FUNCTION FOR TOTAL PROFIT FUNCTION
int transportation::get_profit()
{
}
//display virtual function is pure so no need to implement it


//==========================================================================
//+++++++++++++++++++++++++ SCOOTER DERIVED CLASS ++++++++++++++++++++++++++
//==========================================================================

//CONSTRUCTOR
scooter::scooter() : battery_level(0)
{
}

//CONSTRUCTOR WITH ARGS
//used for setting temp varibles for the newly created derived class object to set all the data to the new object
scooter::scooter(char * rental_type, char * location, int ID, int hours, int profit, bool checked, bool repair, int battery)
{
	type = new char[strlen(rental_type)+1];	//set dynamic mem
	strcpy(type, rental_type);

	intersection = new char[strlen(location)+1];
	strcpy(intersection, location);

	unit_ID = ID;				//set varibles
	hours_rented = hours;
	rental_profit = profit;
	checked_out = checked;
	repair_requested = repair;

	battery_level = battery;
}

//CHECK UNIT ID FOR REMOVE FUNCTION
//called from the node function downcast to check if the user ID number matches this nodes, to determine if it is to be the node removed
int scooter::check(int number)
{
	if(unit_ID == number)
		return 1;
	return 0;
}

//GET THE RENTAL PROFIT VALUE FROM THIS NODE FOR THE TOTAL PROFIT FUNCTION
//return the rental_profit value from this node to be added to the total profit value for the entire list, called from the node class downcasted
int scooter::get_profit()
{
	return rental_profit;
}

//DISPLAY FOR DERIVED DYNAMIC BOUND FUNCTION
//This is called from the node class via downcasting as it determines the type we are and calls the appropriate derived class display to display the 
//speacilized data stored on this derived object
int scooter::display() const
{
	cout << "\n\to Rental type: " << type << endl;
	cout << "\n\to Closest intersection location: " << intersection << endl;
	cout << "\n\to Unit ID#: " << unit_ID << endl;
	cout << "\n\to Hours rented for: " << hours_rented << endl;
	cout << "\n\to Rental Cost: $" << rental_profit << ".00 " << endl;
	cout << "\n\to Unit checked out: ";
	if(checked_out)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	cout << "\n\to Repair_requested: ";
	if(repair_requested)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	cout << "\n\to Battery Level: " << battery_level << "%" << endl;
	return 1;
}


//==========================================================================
//+++++++++++++++++++++++++ ZIP_CAR DERIVEED CLASS +++++++++++++++++++++++++
//==========================================================================
//CONSTRUCTOR
zip_car::zip_car() : license(NULL), gas_level(0), filled_tank(false)
{
}

//COPY CONSTRUCTOR
//since its derived and both base and derived have dynamic memory then it will use the intialization list to call the base copy constructor
zip_car::zip_car(const zip_car & source) : gas_level(source.gas_level), filled_tank(source.filled_tank), transportation(source)
{
	license = new char[strlen(source.license) + 1];
	strcpy(license, source.license);
}

//CONSTRUCTOR WITH ARGS
//used for setting temp varibles for the newly created derived class object to set all the data to the new object
zip_car::zip_car(char * rental_type, char * location, int ID, int hours, int profit, bool checked, bool repair, char * plate, int gas, bool tank)
{
	type = new char[strlen(rental_type)+1];
	strcpy(type, rental_type);

	intersection = new char[strlen(location)+1];
	strcpy(intersection, location);

	unit_ID = ID;
	hours_rented = hours;
	rental_profit = profit;
	checked_out = checked;
	repair_requested = repair;

	license = new char[strlen(plate)+1];
	strcpy(license, plate);

	gas_level = gas;
	filled_tank = tank;
}

//DESTRUCTOR
zip_car::~zip_car()
{
	delete [] license;
	license = NULL;
}

//CHECK UNIT ID FOR REMOVE FUNCTION
//called from the node function downcast to check if the user ID number matches this nodes, to determine if it is to be the node removed
int zip_car::check(int number)
{
	if(unit_ID == number)
		return 1;
	return 0;
}

//GET THE RENTAL PROFIT VALUE FROM THIS NODE FOR THE TOTAL PROFIT FUNCTION
//return the rental_profit value from this node to be added to the total profit value for the entire list, called from the node class downcasted
int zip_car::get_profit()
{
	return rental_profit;
}

//DISPLAY FOR DERIVED DYNAMIC BOUND FUNCTION
//This is called from the node class via downcasting as it determines the type we are and calls the appropriate derived class display to display the 
//speacilized data stored on this derived object
int zip_car::display() const
{
	cout << "\n\to Rental type: " << type << endl;
	cout << "\n\to Closest intersection location: " << intersection << endl;
	cout << "\n\to Unit ID#: " << unit_ID << endl;
	cout << "\n\to Hours rented for: " << hours_rented << endl;
	cout << "\n\to Rental Cost: $" << rental_profit << ".00" << endl;
	cout << "\n\to Unit checked out: ";
	if(checked_out)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	cout << "\n\to Repair_requested: ";
	if(repair_requested)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	cout << "\n\to License Plate Digits: " << license << endl;
	cout << "\n\to Gas Level: " << gas_level << "%" << endl;
	cout << "\n\to Will the tank be filled afterwards: ";
	if(filled_tank)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	return 1;
}

//==========================================================================
//+++++++++++++++++++++++++ BIKE DERIVED CLASS +++++++++++++++++++++++++++++
//==========================================================================
//CONSTRUCTOR
bike::bike() : tire_pressure(0), returned_to_station(false)
{
}

//CONSTRUCTOR WITH ARGS
//used for setting temp varibles for the newly created derived class object to set all the data to the new object
bike::bike(char * rental_type, char * location, int ID, int hours, int profit, bool checked, bool repair, int pressure, bool returner)
{
	type = new char[strlen(rental_type)+1];
	strcpy(type, rental_type);

	intersection = new char[strlen(location)+1];
	strcpy(intersection, location);

	unit_ID = ID;
	hours_rented = hours;
	rental_profit = profit;
	checked_out = checked;
	repair_requested = repair;

	tire_pressure = pressure;
	returned_to_station = returner;
}

//CHECK UNIT ID FOR REMOVE FUNCTION
//called from the node function downcast to check if the user ID number matches this nodes, to determine if it is to be the node removed
int bike::check(int number)
{
	if(unit_ID == number)
		return 1;
	return 0;
}

//GET THE RENTAL PROFIT VALUE FROM THIS NODE FOR THE TOTAL PROFIT FUNCTION
//return the rental_profit value from this node to be added to the total profit value for the entire list, called from the node class downcasted
int bike::get_profit()
{
	return rental_profit;
}

//DISPLAY FOR DERIVED DYNAMIC BOUND FUNCTION
//This is called from the node class via downcasting as it determines the type we are and calls the appropriate derived class display to display the 
//speacilized data stored on this derived object
int bike::display() const
{
	cout << "\n\to Rental type: " << type << endl;
	cout << "\n\to Closest intersection location: " << intersection << endl;
	cout << "\n\to Unit ID#: " << unit_ID << endl;
	cout << "\n\to Hours rented for: " << hours_rented << endl;
	cout << "\n\to Rental Cost: $" << rental_profit << ".00" << endl;
	cout << "\n\to Unit checked out: ";
	if(checked_out)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	cout << "\n\to Repair_requested: ";
	if(repair_requested)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	cout << "\n\to Tire Pressure: " << tire_pressure << "%" << endl;
	cout << "\n\to Will the bike be returned to a bike station: ";
	if(returned_to_station)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	return 1;
}
