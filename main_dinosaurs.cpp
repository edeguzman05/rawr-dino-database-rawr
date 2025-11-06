
/**
 * You probably shouldn't edit this file.
 * It will not be graded, and provides a quick standard way to test your code.
 * 
 * If you wish to write a custom program while you develop,
 * 	use the sandbox.cpp file instead.
 */


//
#include "DinoDataLoader.hpp"
#include "Dinosaur.hpp"
#include "MyDinosaurDatabase.hpp"
#include "Randomer.hpp"
#include "Renderer.hpp"
#include "puhp-tests/Timer.hpp"
#include "puhp-tests/Utility.hpp"


//
#include <algorithm>
#include <climits>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <string>


//
using CPSC131::BST::Renderer;
using CPSC131::Randomer;
using CPSC131::BST::MyBST;
using CPSC131::Databases::Dinosaurs::Dinosaur;
using CPSC131::Databases::Dinosaurs::MyDinosaurDatabase;
using CPSC131::Databases::Dinosaurs::DinoDataLoader;
using CPSC131::Databases::Dinosaurs::DinoTree;

using PuhPTests::Timer;
using PuhPTests::Utility;

using std::cin, std::cout, std::cerr, std::endl;
using std::string, std::to_string;


typedef Dinosaur VTYPE;
const size_t column_width = 20;
const size_t ITERATIONS_PER_DOT = 1000;


//	Proto
void insertRandomDinosaurs(MyDinosaurDatabase& db);
std::string askLine(std::string prompt);
Dinosaur askDinoID(string prompt = "");
void insertDinosaur(MyDinosaurDatabase& db);
void searchDinosaur(MyDinosaurDatabase& db);
void removeDinosaur(MyDinosaurDatabase& db);
void traversePreOrder(MyDinosaurDatabase& db);
void traverseInOrder(MyDinosaurDatabase& db);
void traversePostOrder(MyDinosaurDatabase& db);
void traverseAllTypes(MyDinosaurDatabase& db);
void shuffle(MyDinosaurDatabase& db);
void clear(MyDinosaurDatabase& db);


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
	MyDinosaurDatabase database;
	string s;
	
	while ( true )
	{
		//
		cout
			<< endl
			<< "*** My Dinosaur Database ***" << endl
			<< "Current size: " << database.size() << (database.empty() ? " (empty)" : "") << endl
			<< "Height: " << (database.computeHeight()) << endl
			<< endl
			<< "1. Add a Dinosaur" << endl
			<< "2. Search for a dinosaur" << endl
			<< "3. Remove a Dinosaur" << endl
			<< "4. Insert random dinosaurs" << endl
			<< "5. Traverse: Pre-Order" << endl
			<< "6. Traverse: In-Order" << endl
			<< "7. Traverse: Post-Order" << endl
			<< "8. Traverse: All types" << endl
			<< endl
			<< "S. Shuffle the BST" << endl
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
				insertDinosaur(database);
			}
			else if ( s == "2" ) {
				searchDinosaur(database);
			}
			else if ( s == "3" ) {
				removeDinosaur(database);
			}
			else if ( s == "4" ) {
				insertRandomDinosaurs(database);
			}
			else if ( s == "5" ) {
				traversePreOrder(database);
			}
			else if ( s == "6" ) {
				traverseInOrder(database);
			}
			else if ( s == "7" ) {
				traversePostOrder(database);
			}
			else if ( s == "8" ) {
				traverseAllTypes(database);
			}
			else if ( s == "s" || s == "S" ) {
				shuffle(database);
			}
			else if ( s == "c" || s == "C" ) {
				clear(database);
			}
			else {
				cerr << "Invalid input!" << endl;
			}
		}
		catch(const std::exception& e)
		{
			cerr << "Whoops! Caught an exception!" << endl;
			cerr << "==> " << e.what() << endl;
		}
		
		cout << endl;
		
		//	Render as a png graph, assuming it works.
		//	(but only if a small amount of items are present)
		if ( database.tree().size() < 50 ) {
			Renderer<VTYPE>::renderBST(database.tree());
		}
	}
	
	//
	cout << "Thank you for using this program. Goodbyte!" << endl;
	
	return 0;
}

void insertDinosaur(MyDinosaurDatabase& db)
{
	Dinosaur dino;
	std::string s;
	
	dino.setName( askLine("Enter a name") );
	dino.setDiet( askLine("Enter their diet") );
	dino.setPeriod( askLine("Enter the period in which they lived") );
	dino.setLivedIn( askLine("Enter where they lived") );
	dino.setType( askLine("Enter their type") );
	dino.setLength( askLine("Enter their length") );
	dino.setTaxonomy( askLine("Enter their taxonomy") );
	dino.setNamedBy( askLine("Enter who named them") );
	dino.setSpecies( askLine("Enter the species") );
	dino.setLink( askLine("Enter a URL to more information") );
	
	size_t highest_id = 0;
	db.traverseInOrder
	(
		[&highest_id](DinoTree& tree, std::shared_ptr<DinoTree::Node> node) -> bool
		{
			highest_id = node->getData().getID();
			return true;
		}
	);
	dino.setID(highest_id + 1);
	
	cout
		<< "About to add the following Dinosaur: " << endl
		<< dino.toString() << endl
		<< endl
		<< "Is this correct? (y/n) ---> "
		;
	cin >> s;
	if ( s == "y" || s == "Y" ) {
		
		try
		{
			Timer timer;
			db.insert(dino);
			timer.stop();
			cout << "Insertion took " << timer.seconds() << "s" << endl;
		}
		catch ( const CPSC131::BST::ValueExistsError& e )
		{
			cout << "Caught exception: That value exists!" << endl;
		}
		catch ( const std::exception& e)
		{
			cout << "Caught general exception: " << e.what() << endl;
		}
		catch (...)
		{
			cout << "Caught an unsupported object type!" << endl;
		}
		
	}
	else {
		cout << "OK. Aborting!" << endl;
	}
}

void searchDinosaur(MyDinosaurDatabase& db)
{
	Dinosaur dino_for_id = askDinoID();
	
	Timer timer;
	bool exists = db.exists(dino_for_id);
	timer.stop();
	cout << "Search took " << timer.seconds() << "s" << endl;
	
	cout << "That Dinosaur ==> ";
	if ( exists ) {
		
		auto dino = db.find(dino_for_id);
		cout
			<< "Exists!" << endl
			<< dino.toString() << endl
			;
	}
	else {
		cout << "Does not exist" << endl;
	}
}

void removeDinosaur(MyDinosaurDatabase& db)
{
	size_t id;
	
	cout << "Enter the Dinosaur's ID: ";
	cin >> id;
	
	//	Make a fake empty dinosaur so we can just fill its ID,
	//	which is used for search/remove/etc
	Dinosaur dino;
	dino.setID(id);
	
	try
	{
		Timer timer;
		db.remove(dino);
		timer.stop();
		cout << "Removal took " << timer.seconds() << "s" << endl;
	}
	catch(const std::exception& e)
	{
		cerr << "Caught exception: " << e.what() << endl;
	}
}

void insertRandomDinosaurs(MyDinosaurDatabase& db)
{
	//
	DinoDataLoader loader;
	
	//
	cout
		<< "How many dinosaurs do you want to add?" << endl
		<< "> Enter 0 for 3 million (using duplicated data)" << endl
		<< "> Enter 1 for the normal complete database" << endl
		<< "-----> "
		;
	size_t desired_count;
	cin >> desired_count;
	if ( desired_count == 0 ) {
		desired_count = 3000000;
	}
	else if ( desired_count == 1 ) {
		desired_count = 310;
	}
	
	//
	Timer timer;
	loader.loadDinosaursToTree(db.tree(), desired_count);
	timer.stop();
	cout << "Insertions took " << timer.seconds() << "s" << endl;
}

std::string askLine(std::string prompt)
{
	string input;
	
	Utility::clearCinBuffer();
	
	cout << prompt << endl << " --> ";
	std::getline(std::cin, input);
	
	Utility::clearCinBuffer();
	
	return input;
}

Dinosaur askDinoID(string prompt)
{
	if ( prompt.empty() ) {
		prompt = "Enter your Dinosaur ID: ";
	}
	
	size_t id;
	
	cout << prompt;
	cin >> id;
	
	Dinosaur dino;
	dino.setID(id);
	
	return dino;
}

void traversePreOrder(MyDinosaurDatabase& db)
{
	cout << "Pre-order traversal:" << endl;
	db.traversePreOrder
	(
		[](MyBST<VTYPE>& t, std::shared_ptr<MyBST<VTYPE>::Node> node) -> bool
		{
			cout << std::setw(column_width) << node->getData() << " ... ";
			
			return true;
		}
	);
	cout << endl;
}

void traverseInOrder(MyDinosaurDatabase& db)
{
	cout << "In-order traversal:" << endl;
	db.traverseInOrder
	(
		[](MyBST<VTYPE>& t, std::shared_ptr<MyBST<VTYPE>::Node> node) -> bool
		{
			cout << std::setw(column_width) << node->getData() << " ... ";
			
			return true;
		}
	);
	cout << endl;
}

void traversePostOrder(MyDinosaurDatabase& db)
{
	cout << "Post-order traversal:" << endl;
	db.traversePostOrder
	(
		[](MyBST<VTYPE>& t, std::shared_ptr<MyBST<VTYPE>::Node> node) -> bool
		{
			cout << std::setw(column_width) << node->getData() << " ... ";
			
			return true;
		}
	);
	cout << endl;
}

void traverseAllTypes(MyDinosaurDatabase& db)
{
	traversePreOrder(db);
	traverseInOrder(db);
	traversePostOrder(db);
}

void shuffle(MyDinosaurDatabase& db)
{
	db.shuffle();
}

void clear(MyDinosaurDatabase& db)
{
	db.clear();
}




