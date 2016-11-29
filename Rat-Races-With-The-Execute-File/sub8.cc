//Anthony Walter
//sub shop all possible redos and #7
//create a subshop where you order sandwiches, keep track of inventory, and manage repots
//11-30-11
//Allow people to change their order requires a link list.  Keep a linked list of whatever is ordered at the table.  Number the customers. If people want something different then delete the node a put in a new node.  Don’t forget to change the inventory back if they decided that they don’t want an item.  You can make the condition that once the order is set for the table they can’t change it.  Send the completed order to the chef by sending it to a different file.

//Extra credit, may be added at any time but won’t be counted until the final part is graded.

//Print out other reports the manager might find useful.  Such as average sales per person, average size of a group, etc.

//Make your program extra user friendly.
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

const int ITEM = 7;//number of items in menu

class FoodItem//all related food items
{
	public:
		string nameSub;//an array of related names
		double priceArray;//an array of related prices
		int quantityArray;//an array of related inventory
};

class CustomerLink//to keep track of a table's order
{
	public:
		int customerChoice;//what people ordered
		CustomerLink *next;//link declaration
};

typedef CustomerLink* Ptr;//head ptr declaration

void logo();//outputs logo
void menu ();//outputs menu
void startSub (FoodItem myFood[ITEM]);//fills 3 arrays of related menu #'s, prices, and quantities from 4 text files
int getItem ();//asks user for item multiple times
void choiceFunc (FoodItem myFood[ITEM], double &totalprice, Ptr& head);//choice function for the person
int checkFunc (char ynchoice);//checks answer
void groupFunc (FoodItem myFood[ITEM], double &groupPrice, int &customerCount, Ptr& head);//gathers a group's calculated price
void reduceQuant(FoodItem myFood[ITEM], char &choice);//reduces quantity and checks if any are available
void choicingOrg (FoodItem myFood[ITEM], char &choice, double &totalprice, int customerWho, Ptr& head);//organizes functions so it reduces quantity properly w/o adding to totalprice
void reportFunc (double dailyTotal, int customerCount, FoodItem myFood[ITEM]);//outputs the daily report in a notepad file called dailyreport.txt
void inventorySort(FoodItem myFood[ITEM]);//sorts and outputs an inventory report in ascending order
void printLink(Ptr head, FoodItem myFood[ITEM]);//prints out what a table has ordered
void getLink (Ptr& head, int choice);//adds a chosen node to the order
int deleteFunc (Ptr head, FoodItem myFood[ITEM]);//searches and subtracts the node with a chosen order
void confirmFunc (Ptr head, FoodItem myFood[ITEM], double &groupPrice);//re-loops until their "final answer"
void chefFunc (Ptr head, FoodItem myFood[ITEM]);//function to print out the order to the chef in .txt file
void deleteOrder (Ptr head);//deletes and restarts the linklist for next group's order

void main ()
{
	double groupPrice = 0;//price of the group
	double dailyTotal = 0;//a day's totalsales
	int customerCount = 0;//total count of customers
	Ptr head;//main pointer
	head = new CustomerLink;//creates the first node
	head->next=NULL;//creates the nothing link
	FoodItem myFood[ITEM];//class of all ingredients names 
	startSub (myFood);
	string password = "98765";//exit code
	password = "02498";
	while (password != "98765")
	{
		groupFunc (myFood, groupPrice, customerCount, head);
		dailyTotal += groupPrice;
		cout<<"Type in the password if these are the last customers, if not just press "<<endl<<"'s' to skip."<<endl;
		cin>>password;
		while (password != "s" && password != "S" && password != "98765")
		{
			cout<<"Type s to skip, or the password."<<endl;
			cin>>password;
			cout<<endl<<endl<<endl<<endl;
		}
		groupPrice = 0;
	}
	reportFunc (dailyTotal, customerCount, myFood);
	inventorySort(myFood);
	system("pause");
}
//**********
//outputs logo
/**********/
void logo ()
{
	cout<<"Anth's Giant Enormous (and Expensive)"<<endl<<endl;
	cout<<"  SSSSS    X           X    XBBBBBB      SSSSS    "<<endl;
	cout<<"  X        X           X    X       X    X     "<<endl;
	cout<<" S         X           X    X        X  S     "<<endl;
	cout<<"  X        X           x    X       X    X    "<<endl;
	cout<<"    X      X           X    XBBBBBBX      X  "<<endl;
	cout<<"      X    X           X    X       X       X "<<endl;
	cout<<"       S    X         X     X        X       S"<<endl;
	cout<<"      X      X       X      X       X       X "<<endl;
	cout<<" SSSSSS       XUUUUUX       XBBBBBB     SSSS "<<endl<<endl;
	cout<<"of concentrated LDL cholesterol."<<endl<<endl<<endl<<endl;
}

//**************
//outputs the menu
//**********
void menu ()
	{
		cout<<endl<<"Menu:"<<endl<<endl<<endl;
		cout<<"  1. Real Elf Bread (100% Real Elf)  $99"<<setw(6)<<"  5. Chinese Lettered Alphabet Soup  $50"<<endl;
		cout<<"  2.       Elephant Lard             $50"<<setw(6)<<"  6.  Flavorless Saturated Fat Oil    $2"<<endl;
		cout<<"  3.       Dinosaur Bacon            $40"<<setw(6)<<"  7. Grease Enhanced Moo Moo Steak  $199"<<endl;
		cout<<"  4.    Endangered Penguin Beaks     $70"<<setw(6)<<endl<<endl<<endl; 
	}

//**************************************************************
//fills 4 arrays of related menu #'s, prices, and quantities and shows logo and menu
//*****************************************************************

void startSub (FoodItem myFood[ITEM])
{
	logo();
	menu ();
	string junk;//stores words until new lines
	ifstream fin;//opens the inventory file
	fin.open("subsmenu.txt");//opens the subsmenu text file

	for (int i = 0; i <ITEM; i++)
	{
		getline(fin, myFood[i].nameSub, '\n'); //gets words until it sees a new line
		fin>>myFood[i].priceArray;
		fin>>myFood[i].quantityArray;
		getline(fin, junk, '\n');
	}
	fin.close();

}

//**********************
//asks customer for item choice
//************************

int getItem ()
{
	int choice;//item number choice
	cout<<"Place your order by Item #."<<endl;
	cin>> choice;
	while (choice < 1 || choice > 7)
	{
		cout<<"Not on the menu Einstein, try again."<<endl;
		cin>>choice;
	}
	return choice -1;
}

//*******************
//deals with a customer's order
//************************
void choiceFunc (FoodItem myFood[ITEM], double &totalprice, int customerWho, Ptr& head)
{
	
	char choice;//bool choice
	char ynchoice;//another item bool
	
	choicingOrg (myFood, choice, totalprice, customerWho, head);
	

	do
	{
		cout<<"Would you like another item? (y/n)"<<endl;
		cin >> ynchoice;
		ynchoice = checkFunc (ynchoice);
		if (ynchoice == 'y')
		{
			choicingOrg (myFood, choice, totalprice, customerWho, head);
		}
		else{;}
	}while (ynchoice == 'y');
}
///***************
//just to check for proper answers
//&********************
int checkFunc (char ynchoice)
{
	ynchoice = tolower(ynchoice);
	while (ynchoice != 'y' && ynchoice != 'n')
	{
		cout<<"press y or n....genius, nothing else."<<endl;
		cin>>ynchoice;
		ynchoice = tolower(ynchoice);
	}
	return ynchoice;
}
//**************
//deals with a group's order
//*****************
void groupFunc (FoodItem myFood[ITEM], double &groupPrice, int &customerCount, Ptr& head)
{
	char ynchoice = 'y';///local boolean choice
	ynchoice = checkFunc (ynchoice);
	double totalprice = 0;//tallies the totalprice for a single person
	int customerWho = 0;//keeps track of which customer for the link list or i.e. which person on table

	while (ynchoice == 'y')
	{
		customerCount ++;
		customerWho ++;
		choiceFunc(myFood, totalprice, customerWho, head);
		cout<<"Are their any typical overweight Americans left to order? y/n"<<endl;
		cin>>ynchoice;
		ynchoice = checkFunc (ynchoice);
		groupPrice += totalprice;
		totalprice = 0;
	}

	confirmFunc (head, myFood, groupPrice);
	chefFunc (head, myFood);
	cout<<"Your wallet(s) becomes lighter by "<<groupPrice<<" kajillion dollars."<<endl;
	deleteOrder (head);




	
}
//*************************
//reduces food quantity, if zero it still charges, if less a boolean-type is set to false
//**************************
void reduceQuant(FoodItem myFood[ITEM], char &choice)
{
	myFood[choice].quantityArray --;

	if (myFood[choice].quantityArray == 0)
	{
		cout<<"Warning, you just ran out of "<<myFood[choice].nameSub<<"!"<<endl;
	}
	else if (myFood[choice].quantityArray < 0)
		{
			cout<<"Warning, you're out of "<<myFood[choice].nameSub<<"!"<<endl;
			cout<<"There is nothing left pick something else. You won't be charged for this."<<endl;
			choice = '%';
		}
		else{;}
}
//**************************
//organizes functions so it reduces quantity properly w/o adding to totalprice
//******************************************
void choicingOrg (FoodItem myFood[ITEM], char &choice, double &totalprice, int customerWho, Ptr& head)
{
	
	double price;//sets price for a choice
	do
	{
		choice = getItem();
		getLink(head, choice);
		cout<<"Customer #"<<customerWho<<": You ordered some artery clogging "<<myFood[choice].nameSub<<endl<<"at "<<myFood[choice].priceArray<<" kajillion dollars."<<endl;
		reduceQuant(myFood, choice);
	}while (choice == '%');

	price = myFood[choice].priceArray;
	totalprice += price;
}
//************************************
//outputs the daily report in a notepad file
//***********************************
void reportFunc (double dailyTotal, int customerCount, FoodItem myFood[ITEM])
{
	ofstream rep;//initiation of output of sales and customers
	ofstream inv;//initiation inventory report
	rep.open("dailyreport.txt");//the name of the daily sales file
	rep<<"Here are todays numbers: "<<endl<<"Daily Sales: (in kajillions)$"<<dailyTotal<<endl<<"Daily Customers: "<<customerCount<<endl<<endl;
	rep<<endl<<endl;
	rep<<"Cya! You better make me more money tomorrow!"<<endl<<"Not one penny less, or you are fired."<<endl<<"Btw, you can't have X-day off either, so don't ask."<<endl;
}
//*****************************************
//sorts the data and outputs the inventory report in ascending order
//*******************************
void inventorySort(FoodItem myFood[ITEM])
	{
		ofstream rep;//outputs for inventory report
		rep.open("inventoryreport.txt");//the name of the inventory report file
		int i, j;//i compares each element and j compares i to rest 
		int temp;   // holding variable 
		string temp2;// another holding variable to sort names with item
		for (i=0; i< (ITEM -1); i++)    // element to be compared
		{
			  for(j = (i+1); j < ITEM; j++)   // rest of the elements
			 {
					if (myFood[i].quantityArray > myFood[j].quantityArray)          
				   {
							temp = myFood[i].quantityArray;
							temp2 = myFood[i].nameSub;
							myFood[i].quantityArray = myFood[j].quantityArray;
							myFood[j].quantityArray = temp;
							myFood[i].nameSub = myFood[j].nameSub;
							myFood[j].nameSub = temp2;
				   }
			  }
		 }
		rep<<"Here is the inventory report according to lowest to highest: "<<endl;
		for (int i = 0; i < ITEM; i++)
		{
			rep<<myFood[i].nameSub<<":   "<<myFood[i].quantityArray<<endl;
		}
		rep<<endl<<endl;;
		for (int i = 0; i<ITEM; i++)
		{
			if (myFood[i].quantityArray < 10)
			{
				rep<<"You might consider ordering some "<<myFood[i].nameSub<<" soon...."<<endl;
			}
			else {;}
		}
	}
//****************************************************
//adds node counters with order
//********************************
void getLink (Ptr& head, int choice)
{	
		CustomerLink* temp;//temp pointer declaration
		head->customerChoice = choice;//fills the specified node with the data from choice
		temp = new CustomerLink;//makes the next node which is blank that temp is now pointing at
		temp->next = head;//make the link temp is pointing at to head
		head = temp;//makes the next empty node what head is poitning at now
}

//*************************************
//void printCustomerLink cout's nodes until NULL
//***************************************
void printLink(Ptr head, FoodItem myFood[ITEM])
{
	cout<<"Here is what everyone ordered:"<<endl;
	CustomerLink* current;//my local pointer
	current = head;//my local pointer set to head
	current = current->next;//since the node head has is empty current needs to move a 'link'
	while (current != NULL)
	{
		cout<<current->customerChoice+1<<": "<<myFood[current->customerChoice].nameSub<<endl;
		current = current -> next;
	}
}
//**********************************************
//searches for a node and deletes the chosen node
//*****************************************************
int deleteFunc (Ptr head, FoodItem myFood[ITEM])
{
		char ynchoice = 'n';//local bool variable
		int choice;//local food choice variable
		CustomerLink *search;//keeps track of the chosen node to delete
		CustomerLink *savior;//a 'before' search tracker to point the link around the node search deletes
		while (ynchoice == 'n')
		{
			printLink(head, myFood);
		
			cout<<"Which order do you want to remove? (enter by number)"<<endl;
			cin>>choice;
			choice = choice - 1;
			savior = head;
			search = head;
			search = search -> next;
			while (search != NULL && search->customerChoice != choice)
			{
				search = search -> next;
			}
			if (search == NULL)
			{
				cout<<"Couldn't find your order...please choose again"<<endl;
			}
			else
			{
				cout<<"So you want to delete item #"<<search->customerChoice+1<<": "<<myFood[search->customerChoice].nameSub<<" is this correct? y/n"<<endl;
				cin>>ynchoice;
				checkFunc (ynchoice);
				if (ynchoice == 'y')
				{
					while (savior->next != search)
					{
						savior = savior->next;
					}
					savior->next = search->next;
					delete search;
	
				}
				else {;}
			}
		}
		return choice;
}
//******************************************************
// function to add or subtract nodes and adds to inventory or prices likewise
//*******************************************************
void confirmFunc (Ptr head, FoodItem myFood[ITEM], double &groupPrice)
{
	int choice;// local food choice variable
	char ynchoice;// local bool variable
	char addSub;// another bool variable to choose whether you want to add or subtract or skip this function easier if so desired.
	//
	printLink(head, myFood);
	cout<<"Do you wish to make any changes your order? y/n"<<endl;
	cin>>ynchoice;
	checkFunc (ynchoice);
	
	while (ynchoice == 'y')
	{
	   cout<<"What item would you like to add or subtract? (Press '+' for add or press '-' for subtract or 's' to skip."<<endl;
	   cin>>addSub;
	   	while (addSub != '+' && addSub != '-' && addSub != 's' && addSub != 'S')
		{
			cout<<"press '+' or '-' or 's'....genius, nothing else."<<endl;
			cin>>addSub;
		}
		if (addSub == '-')
		{
		   choice = deleteFunc(head, myFood);
		   myFood[choice].quantityArray ++;
		   groupPrice = groupPrice - myFood[choice].priceArray;
		}
		else if (addSub == '+')
			{
				menu ();
				cout<<"Choose an item from the menu to add."<<endl;
				choice = getItem();
				getLink(head, choice);
				myFood[choice].quantityArray --;
				groupPrice = groupPrice + myFood[choice].priceArray;
			}
		else {;}
		printLink(head, myFood);
		cout<<"Do you wish to make any other changes to your order?"<<endl;
		cin>>ynchoice;
		checkFunc (ynchoice);
	   	
	}
}
//****************************************
//function to print out the table order to the chef in .txt file
//*************************************************
void chefFunc (Ptr head, FoodItem myFood[ITEM])
{
	ofstream rep;//declares the file output
	rep.open("chefticket.txt");//declares the text file name
	rep<<"Here is what everyone ordered:"<<endl;
	CustomerLink* current;//declares local pointer
	current = head;
	current = current->next;
	while (current != NULL)
	{
		rep<<myFood[current->customerChoice].nameSub<<endl;
		current = current -> next;
	}
}
//***************************************
//deletes the linklist at end of each order
//****************************************
void deleteOrder (Ptr head)
{
	CustomerLink* current;//declares local pointer
	current = head;
	current = current->next;
	while (current != NULL)
	{
		head->next = current -> next;
		delete current;
		current = head -> next;

	}
}
//no problems now