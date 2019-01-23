# CS202-System-Programing-Prog-2
CS202 Program 2 Assigned under Karla Fant at Portland State University

Description:

This program implements Dynamic binding (upcasting, downcasting). The specfic heiarchy is decribed in the transportation.h file description.Using a Doubly linked list, we allow the user to select from 3 rental unit vehicles (derived classes) and we then prompt for general data and then speacilized data based on the rental type selected. We store that data intialized to a newly created object and then send it to be as the baseclass pointer in the DLL. we allow an insertion to the list, remove one, remove all, determine total profit from list, display functionality with the list.

Data Structure: doubly linked list

    Heirarachy 1:
    
        Transportation   Transportation    Transportation
               |                |                |
               |                |                |
            Scooter           Zip car           Bike
            
    Heirarachy 2:
    
            Manager ----- Node
