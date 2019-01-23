//Liam Rotchford
//Oct 18 18

/* This file mainly handles the user display menus and prompts for gaining nessessary data from the user about the data for each rental unit. This file also controls
 * the choicesfor what the user may want to do with the list to correctly call the class functions. If the user selects to add a new vehicle to the list they are
 * prompted first for the shared similar data all units share, and then are taken to speacilized functions to gain the speacilized data. We then send all of those
 * temp varibles and send them into a constructor with args to intilaize that data to a new derived object. That object is then assigned to a derived pointer
 * sent into the insert class function to be added to the list
 */

#include "transportation.h"

using namespace std;

/* This function is the first function the user enters from main and it displays the user menu of options for working with the list, there is a try catch block to 
 * make sure input on the choice is handled at run time. In the event they dont enter a valid input on the choice the program will default to quit and end. If 
 * however the input is valid it will enter the function determine, defined below. Based on the return from define from determine the program will end or 
 * keep looping the menu options prompt until the user quits or enters an invalid input
 */
void user_menu(manager & object)
{
	bool valid = false;
	int choice = 0;

	do
	{	//user menu options to manipulate the DLL list
		cout << "\n\nO Rental Vehicle User menu: " << "\n======================================================================================" << endl;	
		cout << "\n\n\t1) Add new rental vehicle to rental list" << endl;
		cout << "\n\t2) Remove one rental vehicle from the rental list" << endl;
		cout << "\n\t3) Remove all rental vehicles from the rental list" << endl;	
		cout << "\n\t4) Display the rental list" << endl;
		cout << "\n\t5) Determine total rental profit from list" << endl;	
		cout << "\n\t6) Quit " << endl;

		cout << "\n\n\to Selection: ";
		cin >> choice;
		cin.ignore(100, '\n');

		try{	//test to see if input is valid
			if(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6)
				throw choice;
		}
		catch(int)	//non valid input defaults to quit option to end the program
		{			
			cout << "\n\t+ Non valid selection given, defaulting to 6) Quit" << endl;
			choice = 6;
		}

		if(!determine(object, choice))		//valid input gets sent into the determine function, if the user choose quit when it returns it will
			valid = true; 				//set valid to true and exit the do while loop and end the program

	}while(!valid);

	cout << "\n\n\to Thank you for using the rental vehicle list!!!\n\n\n\n" << endl;
}

/* This funciton takes the choice input from the user in the above function and determines what class member function or support function to call appropriate
 * to the user selection. If the user chose 6) quit then we return 0 and end the program
 */
bool determine(manager & object, int choice)
{

	switch(choice)		//determine case by the user choice varible
	{
		case 1:
			add_rental(object);		//send to support function to take in user input into temp varibles to be initialized to new derived object
			break;
		case 2:
			finder(object);			//send to support function to determine what rental unit they would like removed from the list
			break;
		case 3:
			{
				if(!object.remove_all())	//send to remove_all class fucntion
					cout << "\n\n\t+ Not all the rental units have been removed from the list" << endl;
				else
					cout << "\n\n\t+ All rental units have been removed from the from the list" << endl;
			}
			break;
		case 4:
			{
				if(!object.display())		//send to the display class member function
					cout << "\n\t\t+ Rental List is currently empty" << endl;
			}
			break;
		case 5:
			{
				int profit = object.total_profit();	//send to the total profit class memeber function to determine the total money made
				cout << "\n\to The total profit based on the current rental list is: $" << profit << ".00" << endl;
			}	
			break;
		case 6:	
			return 0;				//user chose to quit the program
	}
	return 1;
}

/* This function first will display the current list to the user so the user can see all the unit_ID numbers. Then ask the user for the unit_ID number
 * they want removed from the list. we then take that user input and send it to the retrieve remove one class function to search the list when we find the match
 * remove it, otherwise we report it not found
 */
void finder(manager & object)
{
	int number = 0;

	if(!object.display())		//display the current list to the user, if its empty just return since theres nothing to remove
		cout << "\n\t\t+ Rental List is currently empty, returning to menu" << endl;
	else				//list has nodes so ask user for ID number they want removed
	{
		cout << "\n\t\to Please enter in the rental unit ID number to determine which unit to remove from the list: ";
		cin >> number;
		cin.ignore(100, '\n');

		if(!object.retrieve_remove_one(number))		//send to user input to remove one function and determine if the match is in the lsit or not
			cout << "\n\t\t+ Rental unit not found in the list" << endl;
		else
			cout << "\n\t\t+ Rental unit removed from the list" << endl;
	}
}

/* This function is for when the user has selected to add a new rental unit to the list, we first display the list prompt for the type of rental units we 
 * have availble. along with the cost per hour based on the unit type. we have input checker that will loop the user when invalid input is given. 
 * we then send the user to gather data function to get the user input of shared data between all rental types.
 */
void add_rental(manager & object)
{
	bool valid = false;
	int choice = 0;

	do		//display the types of rental units they user can rent
	{
		cout << "\n\no Rental Vehicle Options: " << endl;
		cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "\n\n\t1) Lime Scooter \n\t\t- Great for short distance transportation at { $10 per hour }" << endl;
		cout << "\n\t2) Nike Bike \n\t\t- Great for medium distance transportation at { $5 per hour }" << endl;
		cout << "\n\t3) Zip Car \n\t\t- Great for long distance transportation at { $20 per hour }" << endl;

		cout << "\n\n\to Please make your rental selection: ";
		cin >> choice;
		cin.ignore(100, '\n');

		if(choice == 1 || choice == 2 || choice == 3)	//input checker
			valid = true;
		else
		{
			cout << "\n\tO Please only make your rental selection from the given options above. ";
			cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n" << endl;
		}
	}while(!valid);

	cout << "\no Rental Data Input: ";	//send to the gather data function to get the similar data all rental units share from the user input
	cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n" << endl;
	gather_data(object, choice);		//gather data function call
}

/* This funciton is rather large but that is due to needing to get the user input into a lot of temporary data varibles to be stored into our object 
 * this function gets all the user inpuit for the similar data that all the rental units share. We have a small for loop to cycle through the two
 * bool data type prompts based on the char input for yes or no with a try block to check that will default to N for invalid data
 * once finished it will go to the gather speacial data to get the unique rental ttype data
 */
void gather_data(manager & object, int choice)
{
	char street1[50];		//temporary data varibles for the class  data
	char street2[20];
	char option = 0;	

	char * location = NULL;
	int ID = 0, hours = 0;
	bool checked = false, repair = false;

	cout << "\n\to Please enter the street name the rental unit is currently on: ";	//get first street the unit is on
	cin.get(street1, 50, '\n');
	cin.ignore(100,'\n');
	strcat(street1, " and ");							//add to it "and"

	cout << "\n\to Please enter the closest intersecting street name the unit is near by: ";	//get the cross street
	cin.get(street2, 20, '\n');
	cin.ignore(100,'\n');
	strcat(street1, street2);							//put both streets together

	location = new char[strlen(street1)+1];						//take the one char array and make it a dynamic one for intersection
	strcpy(location, street1);

	cout << "\n\to Please enter the rental units ID number: "; 			//get the rental ID number
	cin >> ID;
	cin.ignore(100,'\n');

	cout << "\n\to How many hours will you be renting the unit for? : ";		//get how long in hours they plan to rent the unit for
	cin >> hours;
	cin.ignore(100, '\n');

	for(int i = 0; i < 2; ++i)							//determine if they want to rent it now or later, or if it needs repair
	{
		if(i == 0)	
		{
			cout << "\n\to Do you plan on renting the unit right now or later? (Y - Now / N - Later) : ";
			cin >> option;							//rent now or later
			cin.ignore(100,'\n');
			option = toupper(option);
		}else
		{	
			cout << "\n\to Does the unit need repair? (Y / N) : ";		//repair
			cin >> option;
			cin.ignore(100,'\n');
			option = toupper(option);
		}	

		try{
			if(option != 'Y' && option != 'N')				//try block to check input
				throw option;
		}
		catch(char){								//if a non valid is received it will default to 'N'
			cout << "\n\t\t+ Non-given option received, auto correcting to 'N', ending program " << endl;
			option = 'N';
		}

		if(option == 'Y' && i == 0)						//set the rent now or later temp varible to true if user entered a Y	
			checked = true;
		else
			repair = true;							//set repair needed temp varible to true if the user entered a Y
	}

	gather_special_data(object, location, ID, hours, checked, repair, choice);	//send to the gather speacilized data function to get the rental types data

	delete [] location;								//delete our dynamically created char * for the intersection temp var
	location = NULL;
}

/* This fucntion determines the rental type the user chose and then sets the rental type char* temp varible, it then determines the cost of the rent
 * based on the user inputted number of hours, it then sends to the rental types speacilied data ,and then it takes all of the created temp varibles and 
 * creates a new derived object of that rental type class sending it to a constructor with arguments to intilized the user data into the object, we then
 * set a pointer to it and send that pointer into the insert fuinction to be put into the DLL
 */
void gather_special_data(manager & object, char *& location, int ID, int hours, bool checked, bool repair, int choice)
{
	char * rental_type = NULL;
	int profit = 0;

	switch(choice)		//determine what rental type the user selected
	{
		case 1:			//SCOOTER
			{
				int battery = 0;	
				char type1[8] = "Scooter";	//set type temp as scooter

				rental_type = new char[strlen(type1)+1];	//create it dynamic
				strcpy(rental_type, type1);

				profit = hours * 10;		//determine the cost by the hour scooters are $10 per hour
				gather_scooter_data(battery);	//get the battery level user input data
								//create a new derived object, with a constructor that take all temporary varibles to initialize
									//to our class data to be saved in this object and have a derived pointer point to it
				scooter * sobject = new scooter(rental_type, location, ID, hours, profit, checked, repair, battery);	

				object.insert(sobject);							//insert object pointer into DLL
			}
			break;

		case 2:			//BIKE
			{					
				int pressure = 0;
				bool returner = false;
				char type3[5] = "Bike";

				rental_type = new char[strlen(type3) + 1];
				strcpy(rental_type, type3);

				profit = hours * 5;			//bike rental is 5$ per hour

				gather_bike_data(pressure, returner);	//get speacilized bike data
									//create new bike object and intiliaze the data to it 
				bike * bobject = new bike(rental_type, location, ID, hours, profit, checked, repair, pressure, returner);

				object.insert(bobject);			//insert into the DLL
			}
			break;

		case 3:			//CAR
			{
				char * plate = NULL;
				char type2[8] = "Zip Car";	
				int gas = 0;
				bool tank = false;

				rental_type = new char[strlen(type2)+1];
				strcpy(rental_type, type2);

				profit = hours * 20;					//car rental is 20$ per hour
				gather_car_data(plate, gas, tank);
									//create a new car object and initialize the data to it
				zip_car * cobject = new zip_car(rental_type, location, ID, hours, profit, checked, repair, plate, gas, tank);

				object.insert(cobject);			//insert into the DLL

				delete [] plate;			//plate is dynamically made in the gather car data function so delete it
				plate = NULL;
			}
			break;
	}
	delete [] rental_type;				//all of these will create a dynamic char* of rental type so delete it 
	rental_type = NULL;
}

/* this function just takes the user input on the battery level with a try block to make sure the input was in a 0 to 100 range */
void gather_scooter_data(int & battery)
{
	//determine battery level of scooter
	cout << "\n\to Please enter the current battery level of the scooter in a range of 0 to 100: ";
	cin >> battery;
	cin.ignore(100, '\n');
	try{
		if(battery < 0 || battery > 100)
			throw battery;
	}
	catch(int){
		cout << "\n\t\t+ Not in correct battery level range, defaulting to full charge 100." << endl;
		battery = 100;
	}
}

/* this funciton takes in the user input on tire pressure with a 0 to 100 range try block to handle the input, along with if the user plans to return the 
 * bike back to its station or not with a try block to determine the input of the char with yes or no to set the bool varible. If the input is invalid it 
 * will default to N 
 */
void gather_bike_data(int & pressure, bool & returner)
{
	char option = 0;	
				//determine tire pressure
	cout << "\n\to Please enter the current tire pressure in the wheels in a range of 0 to 100: ";
	cin >> pressure;
	cin.ignore(100, '\n');
	try{
		if(pressure < 0 || pressure > 100)
			throw pressure;
	}
	catch(int){
		cout << "\n\t\t+ Not in correct air pressure level range, defaulting to full pressure 100." << endl;
		pressure = 100;
	}
				//determine if the user plans to return it to the station
	cout << "\n\to Do you plan on returning the bike to a bike station once your done with your rental?  (Y / N) : ";
	cin >> option;
	cin.ignore(100, '\n');
	option = toupper(option);	
	try{
		if(option != 'Y' && option != 'N')
			throw option;
	}
	catch(char){
		cout << "\n\t\t+ Non-given option received, auto correcting to 'N', ending program " << endl;
		option = 'N';
	}
}

/* this functions determines the zip cars data of the char* license plate, gas level and if they will return the car with a full tank or not. 
 * there is a split between the license plate value by 3 digits to make sure the user inputs it correctly, strcat putting them together into one char[] to copy
 * into dynamic. The license plate chars are capitalized as well. the gas level is try blocked to be within a range of 0 to 100. the returned with full take
 * has its char input checked to determine the bool, invalid input defaults to N
 */
void gather_car_data(char *& plate, int & gas, bool & tank)
{
	char plateholder[10];
	char last_three[4];	
	char option = 0;
				//get first three digits of the license plate
	cout << "\n\to Please enter the FIRST THREE DIGITS liscense plate number on the rental unit: ";
	cin.get(plateholder, 10, '\n');
	cin.ignore(100, '\n');
	strcat(plateholder, "-");		//add a '-' to the end of the 3 digits
						//get last 3 digits 
	cout << "\n\to Please enter the LAST THREE DIGITS of the license plate number: ";
	cin.get(last_three, 4, '\n');
	cin.ignore(100, '\n');

	strcat(plateholder, last_three);	//put both sets together for one license plate

	for(int i = 0; i < strlen(plateholder); ++i)	//capitalize the license plate
	{
		if(isalpha(plateholder[i]))	
			plateholder[i] = toupper(plateholder[i]);	
	}

	plate = new char[strlen(plateholder)+1];	//create dynamic char * for the temp liscense plate 
	strcpy(plate, plateholder);
					//get gas level
	cout << "\n\to Please enter the current gas level of the car in a range of 0 to 100: ";
	cin >> gas;
	cin.ignore(100, '\n');
	try{
		if(gas < 0 || gas > 100)
			throw gas;
	}
	catch(int){
		cout << "\n\t\t+ Not in correct gas level range, defaulting to full tank 100." << endl;
		gas = 100;
	}
					//determine if they plan to refill the take before they finish
	cout << "\n\to Do you plan on refilling the gas tank once your done with your rental?  (Y / N) : ";
	cin >> option;
	cin.ignore(100, '\n');
	option = toupper(option);	
	try{
		if(option != 'Y' && option != 'N')
			throw option;
	}
	catch(char){
		cout << "\n\t\t+ Non-given option received, auto correcting to 'N', ending program " << endl;
		option = 'N';
	}
}

