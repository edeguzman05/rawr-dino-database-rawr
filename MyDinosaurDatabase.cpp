

/**
 *Name: Minh Tran Nguyen & Emmanuel De Guzman 
 *CWID: 826519571
 *CWID: 884886995
 *Email: minh_nguyen582@csu.fullerton.edu & edeguzmanjr05@csu.fullerton.edu
 */

/**
 * ***** TEST COVERAGE BOUNTY *****
 * If you can discover a part of this code that is not currently
 * covered by test cases, you may receive a small amount
 * of extra credit for reporting it to me.
 * 
 * Send me a detailed description of what is not covered.
 * If I decide to add the test cases for future semesters,
 * you'll be granted the extra credit right away.
 * 
 * Valid only for the first reporter.
 */

#include "MyDinosaurDatabase.hpp"


#include <algorithm>
#include <iostream>



namespace CPSC131::Databases::Dinosaurs
{
	MyDinosaurDatabase::MyDinosaurDatabase()
	{
		///	YOUR WELCOME
		this->rng_ = std::mt19937(this->random_device_());
		
		//	Feel free to add more code here, if you feel it is needed
	}
	
	///	Insert a Dinosaur record into the database
	void MyDinosaurDatabase::insert(const Dinosaur& dino)
	{
		this->tree_.insert(dino);
	}
	
	///	Check if a Dinosaur record exists in the database
	bool MyDinosaurDatabase::exists(const Dinosaur& dino) const
	{
		return tree_.exists(dino);
	}
	
	/**
	 * Return a Dinosaur record from the database to the caller
	 * 
	 * For all methods here that take an incoming Dinosaur object,
	 * the caller expects to create an empty Dinosaur object
	 * with ***only*** the ID field filled out.
	 * 
	 * When the Dinosaur class has its comparison operators
	 * overloaded properly, the BST will be able to locate
	 * the correct Dinosaur entry in the tree using just the ID field.
	 */
	Dinosaur& MyDinosaurDatabase::find(const Dinosaur& dino)
	{
		return tree_.find(dino);
	}
	
	///	Remove a Dinosaur entry from the database.
	void MyDinosaurDatabase::remove(const Dinosaur& dino)
	{
		tree_.remove(dino);
	}
	
	///	Iterate all Dinosaur records using pre-order traversal.
	void MyDinosaurDatabase::traversePreOrder
	(
		std::function<
			void(DinoTree&, std::shared_ptr<DinoTree::Node>)
		> callback
	)
	{
		tree_.traversePreOrder(callback);
	}
	
	/**
	 * Iterate Dinosaur records with in-order traversal
	 * (const version)
	 */
	void MyDinosaurDatabase::traverseInOrder
	(
		std::function<
			void(const DinoTree&, std::shared_ptr<DinoTree::Node>)
		> callback
	) const
	{
		tree_.traverseInOrder(callback);
	}
	
	/**
	 * Iterate Dinosaur records with in-order traversal
	 * (non-const version)
	 */
	void MyDinosaurDatabase::traverseInOrder
	(
		std::function<
			void(DinoTree&, std::shared_ptr<DinoTree::Node>)
		> callback
	)
	{
		tree_.traverseInOrder(callback);
	}
	
	/**
	 * Iterate Dinosaur records with post-order traversal
	 * (non-const)
	 */
	void MyDinosaurDatabase::traversePostOrder
	(
		std::function<
			void(DinoTree&, std::shared_ptr<DinoTree::Node>)
		> callback
	)
	{
		tree_.traversePostOrder(callback);
	}
	
	/**
	 * Iterate Dinosaur records with level-order traversal
	 * (non-const)
	 */
	void MyDinosaurDatabase::traverseLevelOrder
	(
		std::function<
			bool(DinoTree&, std::shared_ptr<DinoTree::Node>)
		> callback
	)
	{
		this->traverseLevelOrder(callback);
	}
	
	/**
	 * YOUR WELCOME
	 * 
	 * Shuffle the dinosaur database, by pulling all records out of
	 * the tree into a vector, then shuffling the vector,
	 * then inserting back into the tree.
	 * 
	 * The database itself won't actually change, but the topology
	 * is significantly likely to be different.
	 * 
	 * In general, this can be a potential cure for poisoned
	 * input data ordering.
	 * 
	 * YOUR WELCOME
	 */
	void MyDinosaurDatabase::shuffle()
	{
		std::vector<Dinosaur> dinos_list;
		
		//	Pull all Dinos to a list
		this->tree_.traverseInOrder
		(
			[&dinos_list](DinoTree& t, std::shared_ptr<DinoTree::Node> node) -> bool
			{
				dinos_list.push_back(node->getData());
				
				return true;
			}
		);
		
		//	Shuffle the list
		std::shuffle(dinos_list.begin(), dinos_list.end(), this->rng_);
		
		//	Add back in to the tree
		this->clear();
		for ( auto& dino : dinos_list ) {
			this->insert(dino);
		}
	}
	
	///	Return the computed height of the database's internal BST
	size_t MyDinosaurDatabase::computeHeight()
	{
		return tree_.computeHeight();
	}
	
	///	Return the number of records in the database
	size_t MyDinosaurDatabase::size()
	{
		return tree_.size();
	}
	
	///	Return true if the database if empty; false otherwise
	bool MyDinosaurDatabase::empty()
	{
		return tree_.empty();
	}
	
	///	Clear the entire database
	void MyDinosaurDatabase::clear()
	{
		tree_.clear();
	}
	
	//	Return a reference to the internal binary seatns/rch tree
	DinoTree& MyDinosaurDatabase::tree()
	{
		return this->tree_;
	}
}

