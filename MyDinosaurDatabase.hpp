#ifndef CPSC131_BST_MDINOSAURDATABASE_HPP
#define CPSC131_BST_MDINOSAURDATABASE_HPP


/**
 * You probably don't need to work on this class declaration.
 * 
 * Don't modify any existing prototypes.
 * 
 * You may add more helper functions, if you wish.
 */


#include "MyBST.hpp"

#include "DinosaurTypeDefs.hpp"
#include "Dinosaur.hpp"

#include <random>


namespace CPSC131::Databases::Dinosaurs
{
	/**
	 * Begin the MyDinosaurDatabase class declaration.
	 * 
	 * Hint: The class doesn't actually do much. It's a wrapper!
	 */
	class MyDinosaurDatabase
	{
		public:
			
			MyDinosaurDatabase();
			
			void insert(const Dinosaur& dino);
			bool exists(const Dinosaur& dino) const;
			Dinosaur& find(const Dinosaur& dino);
			void remove(const Dinosaur& dino);
			
			void traversePreOrder(
				std::function<
					void(DinoTree&, std::shared_ptr<DinoTree::Node>)
				> callback
			);
			void traverseInOrder(
				std::function<
					void(const DinoTree&, std::shared_ptr<DinoTree::Node>)
				> callback
			) const;
			void traverseInOrder(
				std::function<
					void(DinoTree&, std::shared_ptr<DinoTree::Node>)
				> callback
			);
			void traversePostOrder(
				std::function<
					void(DinoTree&, std::shared_ptr<DinoTree::Node>)
				> callback
			);
			void traverseLevelOrder(
				std::function<
					bool(DinoTree&, std::shared_ptr<DinoTree::Node>)
				> callback
			);
			
			void shuffle();
			
			size_t computeHeight();
			size_t size();
			bool empty();
			
			void clear();
			
			DinoTree& tree();
			
		private:
			
			DinoTree tree_;
			
			std::random_device random_device_;
			std::mt19937 rng_;
	};
}


#endif
