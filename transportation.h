//Liam Rotchford 
//Oct 17 18

/* The heirarchy of this program is as follow. The transportation class is an abstract base class that acts as a "glue" and similar data holder for the 3 
 * derived classes that represent the rental vehicle options. The manager class handles the doubly linked list that "has a" node class that contains a 
 * transportation base class pointer that gets derived class (rental vehicle) pointers sent to it to be stored in the DLL. The manager / node class
 * are completly separated from the transportation and derived classes (scooter, bike, zip_car). 
*/

#include <iostream>
#include <cstring>
#include <cctype>
#include <typeinfo>


class manager;						//resolve issue with node class no yet knowing what the transportation class is yet for its pointer
class transportation;
//==============================================================
//++++++++++++++++ NODE CLASS DLL ++++++++++++++++++++++++++++++
//==============================================================

class node						//node container for the DLL in the manager class
{
	public:
		void setdata(transportation * rental_type);	//base class pointer setter and getter
		transportation*& getpoint();

		void setnext(node * temp);		//next pointer setter and getter
		node*& gonext();

		void setprev(node * temp);		//previous pointer setter and getter
		node*& goprev();
	
		int node_delete();			//delete the contents of the whatever node is calling it
		int node_check(int number);		//for remove_one function, used to call the derived class check function to compare the unit ID number
		int get_profit();			//retrieve the rental profit varible for this node	
		int node_display() const;		//for the displays in the derived classes (dynamically bound)

	protected:
		transportation * point;			//base class pointer, (will be used to send derived class pointers to store)

		node * next;				//DLL list
		node * previous;
		
};

//===============================================================
//+++++++++++++++++++ TRANSPORTATION BASE CLASS +++++++++++++++++
//===============================================================

class transportation						//abstract base class, glue of the rental vehicle classes	
{
	public:
		transportation();				//default constructor
		transportation(const transportation & source);	//copy constructor for dynamic mem
		virtual ~transportation();			//virtual destructor (required for dynamic binding, and for virtal pure abstract class)
		
		virtual int check(int number);			//check for remove one functionality implemented in the derived classes
		virtual int get_profit();			//retrieve the profit varible from the derived class object for the total profit
		virtual int display() const = 0;		//virtual pure implemented in all the derived classes
	
	protected:
								//similar data between all the derived classes
		char * type;					//rental vehicle type
		char * intersection;				
		int unit_ID;
		int hours_rented;	
		int rental_profit;				//profit is based on hours rented by rental hourly cost
		bool checked_out;
		bool repair_requested;
		
};

//===============================================================
//+++++++++++++++++ DERIVED RENTAL TYPE CLASSES +++++++++++++++++
//===============================================================

//+++++++++++++++++ SCOOTER CLASS +++++++++++++++++++++++++++++++
class scooter : public transportation				//rental vechicle type stored in the DLL nodes
{
	public:
		scooter();	
		scooter(char * rental_type, char * location, int ID, int hours, int profit, bool checked, bool repair, int battery);
								//constructor with args to intialize data to object	
		int check(int number);				//find correct node to remove
		int get_profit();				//get profit value for this rental if we are a scooter object
		int display() const;				//display this nodes data

	protected:
		int battery_level;				//speacilized scooter data

};

//+++++++++++++++++ ZIP_CAR CLASS +++++++++++++++++++++++++++++++
class zip_car : public transportation				//rental vehicle type stored in the DLL nodes
{
	public:
		zip_car();
		zip_car(const zip_car & source);		//copy constuctor
		zip_car(char * rental_type, char * location, int ID, int hours, int profit, bool checked, bool repair, char * plate, int gas, bool tank);
								//constructor with args to intialize data to object	
		~zip_car();					//deconstructor	
		
		int check(int number);				//find remove one node match
		int get_profit();				//get nodes profit varible for total profit function if we are a zip car object
		int display() const;				//display this nodes data

	protected:
		char * license;					//zip cars speacilized data
		int gas_level;
		bool filled_tank;

};

//+++++++++++++++++ BIKE CLASS +++++++++++++++++++++++++++++++
class bike : public transportation				//rental vehicle type stored in the DLL nodes
{
	public:
		bike();
		bike(char * rental_type, char * location, int ID, int hours, int profit, bool checked, bool repair, int pressure, bool returner);
								//constructor with args to intialize data to object
		int check(int number);				//for remove one function to check for match
		int get_profit();				//get profit varible from this nodes data if we are a bike object
		int display() const;				//display bike objects data

	protected:
		int tire_pressure;				//bikes speacilized data
		bool returned_to_station;

};

//===============================================================
//+++++++++++++++++++ MANAGER DLL CLASS +++++++++++++++++
//===============================================================
class manager							//manages the DLL that stores the derived objects in the base class node pointer
{								//	handles DLL list manipulation
	public:
		manager();
		~manager();
			
		int insert(scooter * sobject);			//inserts based on the derived class pointer we are being sent
		int insert(bike * bobject);			//this is where my upcasting occurs
		int insert(zip_car * cobject);

		int retrieve_remove_one(int number);		//find a matching rental unti ID and remove one node from the list
		int remove_all();				//remove entire list	
		int total_profit();				//determine the total profit based on the summed profit values of the entire list
		int display();					//client side display call
	
	protected:
		node * head;					//head and tail pointers for the DLL
		node * tail;

		int deconstruct(node *& head, node *& current);		//destory the list, used fro destuctor and the remove all
		int inserter(node *& temp);				//insert new node into the list
		int retrieve_remove_one(node *& head, int number);	//find and remove one node that matches user input on unit_ID
		int total_profit(node *& head, int & val);		//determine the total summed profit value based on current list	
		int display(node * head, int & num) const;		//recursivly move through the list to call the derived class displays
};


//=======================================================================================
//+++++++++++++++++++ MAIN SUPPORT FUNCTIONS ++++++++++++++++++++++++++++++++++++++++++++
//=======================================================================================
void user_menu(manager & object);					//show user program options
bool determine(manager & object, int choice);				//take that choice and call the appropriate functions

void finder(manager & object);						//get the match value for the remove one function

void add_rental(manager & object);					//display rental vehicle options`
void gather_data(manager & object, int choice);				//get similar data all the vehicles share
void gather_special_data(manager & object, char *& location, int ID, int hours, bool checked, bool repair, int choice);	//get the unique data of the rental type

void gather_scooter_data(int & battery);				//get unique rental data to make gather speacil data data function smaller
void gather_car_data(char *& plate, int & gas, bool & tank);
void gather_bike_data(int & pressure, bool & returner);



