
/**
 * You probably shouldn't edit this file.
 * It will not be graded, and provides a quick standard way to test your code.
 * 
 * If you wish to write a custom program while you develop,
 * 	use the sandbox.cpp file instead.
 */


//
#include "MyBST.hpp"
#include "Randomer.hpp"
#include "Renderer.hpp"
#include "puhp-tests/Timer.hpp"


//
#include <algorithm>
#include <climits>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <string>


//
using CPSC131::BST::MyBST;
using CPSC131::BST::Renderer;
using CPSC131::Randomer;

using PuhPTests::Timer;

using std::cin, std::cout, std::endl;
using std::string, std::to_string;


//	We'll be using integers
typedef int VTYPE;


const size_t ITERATIONS_PER_DOT = 1000;
const size_t column_width = 5;


//	Proto
void loadDatabase();
int askInteger(string prompt = "");
void insertInteger(MyBST<VTYPE>& t);
void insertBulkIntegers(MyBST<VTYPE>& t);
void searchInteger(MyBST<VTYPE>& t);
void removeInteger(MyBST<VTYPE>& t);
void insertRandomIntegers(MyBST<VTYPE>& t, size_t count = 0);
void traversePreOrder(MyBST<VTYPE>& t);
void traverseInOrder(MyBST<VTYPE>& t);
void traversePostOrder(MyBST<VTYPE>& t);
void traverseAllTypes(MyBST<VTYPE>& t);
void shuffle(MyBST<VTYPE>& t);
bool validateOrdering(const MyBST<VTYPE>& t);
void clear(MyBST<VTYPE>& t);


//
std::random_device random_device;
auto rng = std::default_random_engine(random_device());


//
int main()
{
	//
	cout << "Welcome to the MyBST Text User Interface!" << endl;
	cout << "Brought to you by Professor Peralta" << endl;
	cout << endl;
	
	//
	MyBST<VTYPE> bst;
	string s;
	
	/// DEBUG
	//insertRandomIntegers(bst, 25);
	//traverseAllTypes(bst);
	//Renderer<VTYPE>::renderBST(bst);
	
	while ( true )
	{
		//
		cout
			<< endl
			<< "*** My BST ***" << endl
			<< "Current size: " << bst.size() << (bst.empty() ? " (empty)" : "") << endl
			<< "Height: " << (bst.computeHeight()) << endl
			<< endl
			<< "1. Add an integer" << endl
			<< "2. Add integers (bulk)" << endl
			<< "3. Search for an integer" << endl
			<< "4. Remove an integer" << endl
			<< "5. Insert random integers" << endl
			<< "6. Traverse: Pre-Order" << endl
			<< "7. Traverse: In-Order" << endl
			<< "8. Traverse: Post-Order" << endl
			<< "9. Traverse: All types" << endl
			<< endl
			<< "S. Shuffle the BST" << endl
			<< "V. Validate the BST" << endl
			<< "C. Clear the BST" << endl
			<< endl
			<< endl
			<< "(q to quit)" << endl
			<< "===> "
			;
		cin >> s;
		cout << "Your input: " << s << endl;
		cin.ignore(INT_MAX, '\n');
		cout << endl;
		
		//
		if ( s == "q" || s == "Q" ) {
			break;
		}
		
		//
		try
		{
			if ( s == "1" ) {
				insertInteger(bst);
			}
			else if ( s == "2" ) {
				insertBulkIntegers(bst);
			}
			else if ( s == "3" ) {
				searchInteger(bst);
			}
			else if ( s == "4" ) {
				removeInteger(bst);
			}
			else if ( s == "5" ) {
				insertRandomIntegers(bst);
			}
			else if ( s == "6" ) {
				traversePreOrder(bst);
			}
			else if ( s == "7" ) {
				traverseInOrder(bst);
			}
			else if ( s == "8" ) {
				traversePostOrder(bst);
			}
			else if ( s == "9" ) {
				traverseAllTypes(bst);
			}
			else if ( s == "s" || s == "S" ) {
				shuffle(bst);
			}
			else if ( s == "v" || s == "V" ) {
				validateOrdering(bst);
			}
			else if ( s == "c" || s == "C" ) {
				clear(bst);
			}
			else {
				cout << "Invalid input!" << endl;
			}
		}
		catch(const std::exception& e)
		{
			cout << "Whoops! Caught an exception!" << endl;
			cout << "==> " << e.what() << endl;
		}
		
		cout << endl;
		
		//	Render as a png graph, assuming it works.
		//	(but only if a small amount of items are present)
		if ( bst.size() <= 50 ) {
			Renderer<VTYPE>::renderBST(bst);
		}
	}
	
	//
	cout << "Thank you for using this program. Goodbyte!" << endl;
	
	return 0;
}

int askInteger(string prompt)
{
	if ( prompt.empty() ) {
		prompt = "Enter your integer: ";
	}
	
	int i;
	
	cout << prompt;
	cin >> i;
	
	return i;
}

void insertInteger(MyBST<VTYPE>& t)
{
	int i = askInteger();
	
	Timer timer;
	try
	{
		t.insert(i);
	}
	catch(...)
	{
		cout << "Caught exception while trying to insert" << endl;
	}
	
	timer.stop();
	cout << "Insertion took " << timer.seconds() << "s" << endl;
}

void insertBulkIntegers(MyBST<VTYPE>& t)
{
	cout
		<< "Enter integers separated by spaces or newlines." << endl
		<< "Enter a Q or something invalid to quit." << endl
		<< endl
		;
	
	std::vector<int> inputs;
	int input;
	while ( true )
	{
		cout << "Ready for next integer --> ";
		cin >> input;
		if ( cin.fail() ) {
			cout << "Invalid input; Quitting!";
			cin.clear();	// clear must come before ignore lol
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		
		inputs.push_back(input);
	}
	
	cout << "Inserting " << inputs.size() << " integers ... " << endl;
	Timer timer;
	for ( auto input : inputs ) {
		
		try
		{
			t.insert(input);
		}
		catch(...)
		{
			cout << "Caught exception while trying to insert: " << input << endl;
		}
	}
	timer.stop();
	cout << "Inserted " << inputs.size() << " integers in " << timer.seconds() << "s" << endl;
}

void searchInteger(MyBST<VTYPE>& t)
{
	int i = askInteger();
	
	Timer timer;
	bool exists = t.exists(i);
	timer.stop();
	cout << "Search took " << timer.seconds() << "s" << endl;
	
	cout << "That integer ==> ";
	if ( exists ) {
		cout << "Exists!";
	}
	else {
		cout << "Does not exist";
	}
}

void removeInteger(MyBST<VTYPE>& t)
{
	int i = askInteger();
	
	Timer timer;
	
	t.remove(i);
	
	timer.stop();
	cout << "Removal took " << timer.seconds() << "s" << endl;
}

void insertRandomIntegers(MyBST<VTYPE>& t, size_t count)
{
	Randomer r;
	
	if ( count == 0 ) {
		cout << "How many integers do you wish to add? ";
		cin >> count;
	}
	
	cout << "Generating random numbers" << endl;
    auto ints = r.integers(count);
    cout << "Done generating random numbers" << endl;
    
    cout << "Inserting " << count << " random integers" << endl;
    Timer timer;
    size_t success_count = 0;
    for ( auto i : ints ) {
		
		cout << " ... " << i;
		
		try
		{
			t.insert(i);
			success_count++;
		}
		catch (const CPSC131::BST::ValueExistsError& e)
		{
			//	Complain on duplicates
			cout << " [duplicate detected; ignoring]" ;
		}
	}
	cout << endl;
	timer.stop();
	cout << "Inserted " << success_count << " integers in " << timer.seconds() << "s" << endl;
}

void traversePreOrder(MyBST<VTYPE>& t)
{
	cout << "Pre-order traversal:" << endl;
	t.traversePreOrder
	(
		[](MyBST<VTYPE>& t, std::shared_ptr<MyBST<VTYPE>::Node> node) -> bool
		{
			cout << std::setw(column_width) << node->getData() << " ... ";
			
			return true;
		}
	);
	cout << endl;
}

void traverseInOrder(MyBST<VTYPE>& t)
{
	cout << "In-order traversal:" << endl;
	t.traverseInOrder
	(
		[](MyBST<VTYPE>& t, std::shared_ptr<MyBST<VTYPE>::Node> node) -> bool
		{
			cout << std::setw(column_width) << node->getData() << " ... ";
			
			return true;
		}
	);
	cout << endl;
}

void traversePostOrder(MyBST<VTYPE>& t)
{
	cout << "Post-order traversal:" << endl;
	t.traversePostOrder
	(
		[](MyBST<VTYPE>& t, std::shared_ptr<MyBST<VTYPE>::Node> node) -> bool
		{
			cout << std::setw(column_width) << node->getData() << " ... ";
			
			return true;
		}
	);
	cout << endl;
}

void traverseAllTypes(MyBST<VTYPE>& t)
{
	traversePreOrder(t);
	traverseInOrder(t);
	traversePostOrder(t);
}

void shuffle(MyBST<VTYPE>& t)
{
	std::vector<VTYPE> integers_list;
	
	//	Pull all Dinos to a list
	cout << "Pulling all tree items to a flat list" << endl;
	t.traverseInOrder
	(
		[&integers_list](MyBST<VTYPE>& t, std::shared_ptr<MyBST<VTYPE>::Node> node) -> bool
		{
			integers_list.push_back(node->getData());
			
			return true;
		}
	);
	cout << "Finished pulling all tree items to a flat list" << endl;
	
	//	Shuffle the list
	cout << "Shuffling the flat list" << endl;
	std::shuffle(integers_list.begin(), integers_list.end(), rng);
	cout << "Finished shuffling the flat list" << endl;
	
	//	Add back in to the tree
	cout << "Adding shuffled list back into the tree (fingers crossed on the distribution)" << endl;
	t.clear();
	for ( auto& integer : integers_list ) {
		t.insert(integer);
	}
	cout << "Finished adding shuffled list back into the tree" << endl;
}

bool validateOrdering(const MyBST<VTYPE>& t)
{
	//
	bool order_is_valid = true;
	bool first_time = true;
	VTYPE last_found;
	
	//
	cout << "Validating order of nodes ..." << endl;
	t.traverseInOrder
	(
		[&order_is_valid, &first_time, &last_found]
		(const MyBST<VTYPE>& t, std::shared_ptr<MyBST<VTYPE>::Node> node) -> bool
		{
			if ( first_time ) {
				first_time = false;
			}
			else if ( node->getData() < last_found ) {
				order_is_valid = false;
				return false;
			}
			
			last_found = node->getData();
			
			return true;
		}
	);
	
	//
	if ( order_is_valid ) {
		cout << "Nodes appear to be in valid order (assuming traverseInOrder is working)" << endl;
	}
	else {
		cout << "Either the nodes aren't in the correct order or traverseInOrder is broken!" << endl;
	}
	
	return order_is_valid;
}

void clear(MyBST<VTYPE>& t)
{
	t.clear();
}



