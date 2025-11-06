#ifndef CPSC131_BST_MYBST_HPP
#define CPSC131_BST_MYBST_HPP

/**
 * Work on this code!
 */


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


#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <queue>


namespace CPSC131::BST
{
	///	YOUR WELCOME
	using std::cout, std::endl;
	
	///	YOUR WELCOME
	///	Must bring std::to_string into this scope so we can overload it further below
	using std::to_string;
	
	///	YOUR WELCOME
	//	Custom exceptions
	struct ValueNotFoundError : std::runtime_error
	{
		using std::runtime_error::runtime_error;
	};
	struct ValueExistsError : std::runtime_error
	{
		using std::runtime_error::runtime_error;
	};
	///	YOUR WELCOME
	
	/*********************************
	 * Begin declarations
	 * 
	 * DO NOT modify any existing declarations
	 * or your tests will likely not pass.
	 * 
	 * You may ADD additional declarations if you wish to use helper functions,
	 * which is probably a smart idea.
	 ********************************/
	template <class T>
	class MyBST
	{
		public:
			
			//	Node
			class Node
			{
				public:
					
					/// /////////////////////////////////////
					///	Overloading so std::to_string works
					///	YOUR WELCOME
					std::string to_string(const Node& node)
					{
						std::stringstream ss;
						
						//	Note that this won't compile unless
						//	any custom T type used is overloaded for the stream operator
						ss
							<< "MyBST<T>::Node"
							<< "; Data = " << this->data_
							<< "; Depth = " << this->depth_
							<< "; Parent = " << this->parent_.get()
							<< "; Left Child = " << this->left_child_.get()
							<< "; Right Child = " << this->right_child_.get()
							;
						
						return ss.str();
					}
					/// /////////////////////////////////////
					
					//	CTORs
					Node();
					Node(const Node& other);
					
					//	DTOR
					~Node();
					
					T& getData();
					void setData(T data);
					
					size_t getDepth() const;
					void setDepth(size_t depth);
					
					void setParent(std::shared_ptr<Node> p);
					std::shared_ptr<Node> getParent() const;
					
					void setLeftChild(std::shared_ptr<Node> lc);
					std::shared_ptr<Node> getLeftChild() const;
					
					void setRightChild(std::shared_ptr<Node> rc);
					std::shared_ptr<Node> getRightChild() const;
					
					void clear();
					
					T& operator*();
					bool operator==(const Node& other);
					bool operator!=(const Node& other);
					
					size_t getHeight(Node* H) const; //Recursive Helper
					
				private:
					
					T data_;
					size_t depth_ = 0;
					
					std::shared_ptr<Node>
						parent_,
						left_child_,
						right_child_
						;
					
				friend class MyBST;
			};
			
			//	CTORs
			MyBST();
			MyBST(const MyBST& other);
			
			//	DTOR
			~MyBST();
			
			//
			void insert(T value);
			
			///	Seems redundant to return the object you're looking for
			///	until we remember we can place less information in the
			///	argument's object, relying on comparison operators to still work
			T& find(T value);
			
			std::shared_ptr<Node> find_node(T value) const;
			
			void remove(T value);
			void remove(std::shared_ptr<Node> node);
			
			std::shared_ptr<Node> ReplacementSuccessor(std::shared_ptr<MyBST<T>::Node> node); //Helper Function
			
			
			bool exists(T value) const;
			
			std::shared_ptr<Node> getRoot() const;
			
			bool isRoot(const std::shared_ptr<Node>& node) const;
			bool isInternal(const std::shared_ptr<Node>& node) const;
			bool isExternal(const std::shared_ptr<Node>& node) const;
			bool isLeaf(const std::shared_ptr<Node>& node) const;
			
			bool isParent(const std::shared_ptr<Node>& node) const;
			bool hasParent(const std::shared_ptr<Node>& node) const;
			
			size_t getChildCount(const std::shared_ptr<Node>& node) const;
			bool hasOneChild(const std::shared_ptr<Node>& node) const;
			bool hasTwoChildren(const std::shared_ptr<Node>& node) const;
			
			bool isLeftChild(const std::shared_ptr<Node>& node) const;
			bool hasLeftChild(const std::shared_ptr<Node>& node) const;
			bool isRightChild(const std::shared_ptr<Node>& node) const;
			bool hasRightChild(const std::shared_ptr<Node>& node) const;
			
			void traversePreOrder(std::function<void(MyBST&, std::shared_ptr<Node>)> callback);
			void traverseInOrder(std::function<void(const MyBST&, std::shared_ptr<Node>)> callback) const;
			void traverseInOrder(std::function<void(MyBST&, std::shared_ptr<Node>)> callback);
			void traversePostOrder(std::function<void(MyBST&, std::shared_ptr<Node>)> callback);
			void traverseLevelOrder(std::function<bool(const MyBST&, std::shared_ptr<Node>)> callback) const;
			void traverseLevelOrder(std::function<bool(MyBST&, std::shared_ptr<Node>)> callback);
			
			void clear();
			
			bool empty() const;
			size_t size() const;
			
			std::shared_ptr<Node> getDeepestLeaf();
			size_t computeHeight();
			
			std::string renderToDot() const;
			
			bool operator==(const MyBST<T>& other);
			bool operator!=(const MyBST<T>& other);
			MyBST& operator=(const MyBST<T>& other);
		
		private:
			
			///	YOUR WELCOME
			void traverseLevelOrder
			(
				std::shared_ptr<Node> node,
				std::function<bool(const MyBST&, std::shared_ptr<Node>)> callback
			) const;
			
			///	YOUR WELCOME
			void traverseLevelOrder
			(
				std::shared_ptr<Node> node,
				std::function<bool(MyBST&, std::shared_ptr<Node>)> callback
			);
			
			///	Private members; DO NOT MODIFY
			std::shared_ptr<Node> root_;
			size_t size_ = 0;
			
			///	Friend class; DO NOT MODIFY
			friend class Tester;
			
	};
	
	/*********************************
	 * Begin definitions
	 * 
	 * Below you'll find definitions (implementations) of all declared
	 * methods you saw above. You must complete each method below.
	 * 
	 * Your work it to complete the incomplete methods below, changing
	 * anything in the methods' bodies you feel is needed.
	 * But do not modify method signatures.
	 * 
	 * 
	 ********************************/


	
	/*********************
	 * Begin Node methods!
	 * aka MyBST<T>::Node
	 ********************/
	
	

	///	Node Constructor (CTOR)
	template <class T>
	MyBST<T>::Node::Node()
	{
		depth_ = 0;
		parent_ = nullptr;
		left_child_ = nullptr;
		right_child_= nullptr;
	}
	
	/**
	 * Node's Copy Constructor
	 * 
	 * What does it mean to "copy one Node to another"?
	 * 
	 * For this project, we'll assume pointer-stealing is totally
	 * fine for Nodes, because they don't own the overall data structure
	 * but simply hold values.
	 * 
	 * In other words, copy all pointers and the value directly.
	 */
	template <class T>
	MyBST<T>::Node::Node(const MyBST<T>::Node& other)
	{
		data_ = other.data_;
		depth_= other.depth_;
		parent_ = other.parent_;
		left_child_=other.left_child_;
		right_child_ = other.right_child_;
	}
	
	/**
	 * Node Destructor (DTOR)
	 * 
	 * You probably want to clear out all pointers here.
	 */
	template <class T>
	MyBST<T>::Node::~Node()
	{
		this->clear();
	}
	
	///	Return the Node's data to the caller, as a reference
	template <class T>
	T& MyBST<T>::Node::getData()
	{
		return data_;
	}
	
	///	Set the Node's data
	template <class T>
	void MyBST<T>::Node::setData(T data)
	{
		data_ = data;
	}
	
	///	Return the Node's depth to the caller
	template <class T>
	size_t MyBST<T>::Node::getDepth() const
	{
		return depth_;
	}
	
	///	Set the Node's depth
	template <class T>
	void MyBST<T>::Node::setDepth(size_t depth)
	{
		depth_ = depth;
	}
	
	///	Set the Node's parent pointer
	template <class T>
	void MyBST<T>::Node::setParent(std::shared_ptr<MyBST<T>::Node> p)
	{
		parent_ = p ;
	}
	
	///	Return the Node's parent pointer to the caller
	template <class T>
	std::shared_ptr<class MyBST<T>::Node::Node> MyBST<T>::Node::getParent() const
	{	
		return parent_;
	}
	
	///	Set the Node's left child pointer
	template <class T>
	void MyBST<T>::Node::setLeftChild(std::shared_ptr<MyBST<T>::Node> lc)
	{
		left_child_ = lc;
	}
	
	///	Return the Node's left child pointer to the caller
	template <class T>
	std::shared_ptr<class MyBST<T>::Node> MyBST<T>::Node::getLeftChild() const
	{	
		return left_child_;
	}
	
	///	Set the Node's right child pointer
	template <class T>
	void MyBST<T>::Node::setRightChild(std::shared_ptr<MyBST<T>::Node> rc)
	{
		right_child_ = rc;
	}
	
	///	Return the Node's right child pointer to the caller
	template <class T>
	std::shared_ptr<class MyBST<T>::Node::Node> MyBST<T>::Node::getRightChild() const
	{	
		return right_child_;
	}
	
	/**
	 * The clear() method should null all pointers.
	 * 
	 * Doing this and also null'ing the corresponding left/right
	 * child pointer in this Node's parent node (if applicable)
	 * effectively snips the Node from the tree and allows
	 * the smart pointers to avoid memory leaks.
	 */
	template <class T>
	void MyBST<T>::Node::clear()
	{
		parent_ = nullptr;
		left_child_ = nullptr;
		right_child_ = nullptr;
		//delete this;
	}
	
	//Recursive Function
	template <class T> //This compiles but computeHeight doesn't. Need assistance here pls :,(
	size_t MyBST<T>::Node::getHeight(Node* H) const
	{
		// Base case when H passes the root
		if (H == nullptr) {
			return 0;
		}
		
		//Computes the height of the left side
		auto leftHeight = getHeight(H->left_child_.get());
		
		//Computes the height of the right side
		auto rightHeight = getHeight(H->right_child_.get());
		
		//Grabs the max of the left and right and adds one to account for the root
		return 1 + std::max(leftHeight, rightHeight);
		
		//I borrowed (yoinked) this shit from Dr. Bein lol
	}
	
	/**
	 * Dereferencing operator
	 * Return this Node's value to the caller, by reference.
	 */
	template <class T>
	T& MyBST<T>::Node::operator*()
	{		
		return this->data_;
	}
	
	/**
	 * Comparison/equality operator.
	 * 
	 * For this project, we'll say two nodes are equal
	 * when their data is equal (not their pointers)
	 */
	template <class T>
	bool MyBST<T>::Node::operator==(const Node& other)
	{
		return data_ == other.data_;
	}
	
	/**
	 * Inequality operator,
	 * which is the opposite of the equality operator above
	 */
	template <class T>
	bool MyBST<T>::Node::operator!=(const Node& other)
	{
		return data_ != other.data_;
	}
	
	
	/***********************************
	 * Begin Binary Search Tree methods!
	 * aka MyBST<T>
	 **********************************/
	
	
	/**
	 * Binary Search Tree's Constructor
	 * (BST CTOR)
	 */
	template <class T>
	MyBST<T>::MyBST()
	{
		root_ = nullptr;
		size_ = 0;
	}
	
	/**
	 * BST's Copy Constructor (Copy CTOR)
	 * 
	 * Hint: How can you copy a BST to another and ensure 
	 * the same topology? This is why level-order traversal
	 * has been impemented on your behalf.
	 * 
	 * Simply iterate through the source tree using level-order
	 * traversal.
	 * For each Node you find, just insert() its data into the
	 * destination tree.
	 * 
	 * Level-order traversal automatically handles the correct
	 * topology.
	 * 
	 */
	template <class T>
	MyBST<T>::MyBST(const MyBST& other)
	{
		*this = other;
	}
	
	/**
	 * Tree's Destructor.
	 * 
	 * Here you should empty the tree to ensure no memory leaks.
	 */
	template <class T>
	MyBST<T>::~MyBST()
	{
		this->clear();

	}
	
	/**
	 * Insert the given value into the tree, at the proper position.
	 * 
	 * Throw a ValueExistsError if the value already exists in the tree.
	 */
	template <class T>
	void MyBST<T>::insert(T value)
	{
		if (exists(value)) {
			throw ValueExistsError("This value already exists!");
		}
		//create new Node 
		auto new_node = std::make_shared<Node>();
    	new_node->setData(value);
		//if tree is empty (root_ is null), new node is the root
		if(root_ == nullptr){
			root_ = new_node;
			new_node->setDepth(0);
			this->size_++;
			return;
		}
		//traversing to the deepest level 
		std::shared_ptr<Node> temp_parent = nullptr;
		auto temp = root_;
		size_t temp_depth = 0; //temporary depth, will increase each time travel down
		
		while(temp){
			temp_parent = temp;
			temp_depth++;
			if(value < temp->getData()){
				temp = temp->getLeftChild();
			} else {
				temp = temp->getRightChild();
			}
		}
		new_node->setParent(temp_parent);
		new_node->setDepth(temp_depth);
		//do the pointer magic  
		if (value < temp_parent->getData()){
			temp_parent->setLeftChild(new_node);
		}else{
			temp_parent->setRightChild(new_node);
		}
		size_++;
	}
	
	/**
	 * Find a value in the Tree, and return a reference to it.
	 * 
	 * Should throw ValueNotFoundError if the value isn't in the Tree.
	 */
	template <class T>
	T& MyBST<T>::find(T value)
	{
		if (!exists(value)) {
			throw ValueNotFoundError("This value does not exist!");
		}
		//I sort of dumbed this down because I was kinda lost on this one :,(
		auto temp = root_;
		while (temp != nullptr) {
			if (value > temp->getData()) {
				temp = temp->getRightChild();
			} else if (value < temp->getData()) {
				temp = temp->getLeftChild();
			} else if (value == temp->getData()) {
				break;
			}
		}
		return temp->getData();
	}
	
	/**
	 * Find a value in the Tree, and return its containing Node pointer
	 * to the caller.
	 * 
	 * This is very similar to the above find() method,
	 * only find_node returns a Node pointer, while find() returns
	 * a reference to the actual value.
	 * 
	 * If the value isn't found, don't throw any exceptions; Simply
	 * return a null pointer to the caller.
	 */
	template <class T>
	std::shared_ptr<class MyBST<T>::Node> MyBST<T>::find_node(T value) const
	{
		auto squirrel = root_;
		
		while (squirrel != nullptr) {
			if (value == squirrel->getData()) {
				return squirrel;
				
			} else if (value < squirrel->getData()) {
				squirrel = squirrel->getLeftChild();
				
			} else if (value > squirrel->getData()) {
				squirrel = squirrel->getRightChild();
			}
		}
		return nullptr;
	}
	
	/**
	 * Remove a value from the Tree. * 
	 * Should throw a ValueNotFoundError excption if the value
	 * doesn't exist in the Tree.
	 */
	template <class T>
	void MyBST<T>::remove(T value)
	{
		if (!exists(value)) {
			throw ValueNotFoundError("This value does not exist!");
		}
		
		auto node = find_node(value);
		remove(node);
	}
	
	/**
	 * Remove a specific Node from the Tree.
	 * 
	 * This is very similar to the above remove(T),
	 * only we specify an actual Node pointer to remove rather
	 * than a value.
	 * 
	 * Should throw some type of exception if the Node is null.
	 */
	template <class T>
	void MyBST<T>::remove(std::shared_ptr<MyBST<T>::Node> node)
	{
		if (empty()) {
			throw ValueNotFoundError("This value does not exist!");
		}
		//Three cases: No children, One Child and 2 Children
		if(node->getLeftChild() == nullptr && node->getRightChild() == nullptr){
			auto temp_parent = node->getParent();
			if (temp_parent != nullptr){
				if(temp_parent->getLeftChild() == node){
					temp_parent->setLeftChild(nullptr);
            } else {
                temp_parent->setRightChild(nullptr);
            }
        	} else {
            // If this is the root node, just clear the tree
            	root_ = nullptr;
				}
			}
		else if (!node->getLeftChild() || !node->getRightChild()) {
        	auto temp_child = node->getLeftChild() ? node->getLeftChild() : node->getRightChild();
			auto temp_parent = node->getParent();
        	if (temp_parent) {
            	if (temp_parent->getLeftChild() == node) {
                	temp_parent->setLeftChild(temp_child);
            	} else {
                		temp_parent->setRightChild(temp_child);
            	}
        	} else {
            	// If this is the root node, update the root
            	root_ = temp_child;
        	}
        	temp_child->setParent(temp_parent);
    	}
		else {
        	auto temp_child = node->getRightChild();
        	while (temp_child->getLeftChild()) {
            	temp_child = temp_child->getLeftChild();
        	}

        	node->setData(temp_child->getData());

       		if (temp_child->getParent()->getLeftChild() == temp_child) {
            	temp_child->getParent()->setLeftChild(temp_child->getRightChild());
        	} else {
            	temp_child->getParent()->setRightChild(temp_child->getRightChild());
        	}

        	if (temp_child->getRightChild()) {
            	temp_child->getRightChild()->setParent(temp_child->getParent());
        	}
    	}

		//calculate depth using lambda 
		auto recalculateDepth = [](std::shared_ptr<Node> node, size_t temp_depth, auto& self) {
        	if (!node) return;
        	node->setDepth(temp_depth);
        	self(node->getLeftChild(), temp_depth + 1, self);
        	self(node->getRightChild(), temp_depth + 1, self);
   		};

    	// Apply depth updates
    	if (node->getParent()) {
        	recalculateDepth(node->getParent(), node->getParent()->getDepth(), recalculateDepth);
   		}
		//resize
		size_--;
	}
	
	
	template <class T>
	std::shared_ptr<class MyBST<T>::Node> MyBST<T>::ReplacementSuccessor(std::shared_ptr<MyBST<T>::Node> node) {
		auto newSuccessor = node->getRightChild();
		while (newSuccessor->getLeftChild() != nullptr) {
			newSuccessor = newSuccessor->getLeftChild();
		}
		return node;
		
	}
	
	
	/**
	 * Return true if the value exists in the Tree,
	 * or false otherwise.
	 */
	template <class T>
	bool MyBST<T>::exists(T value) const
	{
		//SCREW RECURSION!!!!!!!
		
		//Creates a temp ptr at the root
		auto temp = root_;
		
		//Checks if root isn't null
		while (temp != nullptr) {
			//The value exists
			if (temp->getData() == value) {
				return true;
				
			//Grabs the left set of data if the value is less
			} else if (value < temp->getData()) {
				temp = temp->getLeftChild();
			//Grabs the right set of data if the value is more
			} else if (value > temp->getData()) {
				temp = temp->getRightChild();
			}
		}
		return false;
	}
	
	/// Return the root Node pointer to the caller
	template <class T>
	std::shared_ptr<class MyBST<T>::Node> MyBST<T>::getRoot() const
	{
		return root_;
	}
	
	/// Return true if the specified Node is the root Node
	template <class T>
	bool MyBST<T>::isRoot(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if (node == root_){
			return true;
		}
		
		return false;
	}
	
	///	Return true if the specified Node is internal
	template <class T>
	bool MyBST<T>::isInternal(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if((node->getLeftChild() != nullptr ||node->getRightChild()!= nullptr)){
			return true;
		}
		return false;
	}
	
	///	Return true if the specified Node is external
	template <class T>
	bool MyBST<T>::isExternal(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if((node->getLeftChild() == nullptr && node->getRightChild() == nullptr)){
			return true;
		}
		return false;
	}
	
	///	Return true if the specified Node is a leaf
	template <class T>
	bool MyBST<T>::isLeaf(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if ((node->getLeftChild() == nullptr) && (node->getRightChild() == nullptr)) {
			return true;
		}
		return false;
	}
	
	///	Return true if the specified Node is a parent of any other Node
	template <class T>
	bool MyBST<T>::isParent(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		//If neither HasTwo or HasOne fulfills the conditions
		if ((node->getLeftChild() == nullptr) && (node->getRightChild() == nullptr)) {
			return false;
		}
		return true;
	}
	
	///	Return true if the specified Node has a parent
	template <class T>
	bool MyBST<T>::hasParent(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if (node->getParent() != nullptr){
			return true;
		}
		return false;
	}
	
	///	Return the number of child nodes that this Node has
	template <class T>
	size_t MyBST<T>::getChildCount(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if (!empty()) {
			// Two children exist here
			if ((node->getLeftChild() != nullptr) && (node->getRightChild() != nullptr)) {
				return 2;
				
			// No children exist, but the tree is NOT empty
			} else if ((node->getLeftChild() == nullptr) && (node->getRightChild() == nullptr)) { 
				return 0;
				
			// Only the right child exists here
			} else if ((node->getLeftChild() == nullptr) && (node->getRightChild()!= nullptr)) {
				return 1;
				
			// Only the left child exists here
			} else if ((node->getLeftChild() != nullptr) && (node->getRightChild()== nullptr)) {
				return 1;
			}
		}
		//The tree is empty by this point (This is in the case it's checking for an empty tree)
		return 0; 
	}
	
	///	Return true if the specified Node has exactly one child
	template <class T>
	bool MyBST<T>::hasOneChild(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
	//If either the left or right child exist, and vice versa doesn't, safe to assume there is one child
		if ((node->getLeftChild() == nullptr) && (node->getRightChild()!= nullptr)) {
			return true;
		}
		if ((node->getLeftChild() != nullptr) && (node->getRightChild() == nullptr)) {
			return true;
		}
		return false;
	}
	
	///	Return true if the specified Node has exactly two children
	template <class T>
	bool MyBST<T>::hasTwoChildren(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if ((node->getLeftChild() != nullptr) && (node->getRightChild() != nullptr)) {
			return true;
		} else {
		return false;
		}
	}
	
	///	Return true if the specified Node is the left child of its parent
	template <class T>
	bool MyBST<T>::isLeftChild(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if (hasParent(node) && (node->getData() < node->getParent()->getData()) && !(isRoot(node))) {
			return true;
		}
		return false;
	}
	
	///	Return true if the specified Node has a left child
	template <class T>
	bool MyBST<T>::hasLeftChild(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if (node->getLeftChild() != nullptr) {
			return true;
		}
		
		return false;
	}
	
	///	Return true if the specified Node is the right child of its parent
	template <class T>
	bool MyBST<T>::isRightChild(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if (hasParent(node) && (node->getData() > node->getParent()->getData()) && !(isRoot(node))) {
			return true;
		}
		return false;
	}
	
	///	Return true if the specified Node has a right child
	template <class T>
	bool MyBST<T>::hasRightChild(const std::shared_ptr<MyBST<T>::Node>& node) const
	{
		if (node->getRightChild() != nullptr) {
			return true;
		}
		
		return false;
	}
	
	/**
	 * Visit every Node in the Tree, in pre-order traversal.
	 * 
	 * Allow the caller to provide a custom
	 * callback function (lambda, usually)which they can
	 * use to "visit" each Node.
	 * 
	 * The callback function will receive a Tree reference
	 * and a Node pointer as arguments.
	 */
	template <class T>
	void MyBST<T>::traversePreOrder
	(
		std::function<void(MyBST<T>&, std::shared_ptr<MyBST<T>::Node>)> callback
	)
	{
		std::function<void(std::shared_ptr<Node>)> preOrder = [&](std::shared_ptr<Node> node) {
   			if (!node) {
        		return;
    		}
    		callback(*this, node);
    		
    		preOrder(node->getLeftChild());
    		preOrder(node->getRightChild());
		};
		preOrder(root_);
	}
	
	/**
	 * Visit every Node in the Tree, in in-order traversal.
	 * 
	 * This is the const overload of traverseInOrder.
	 * 
	 * Note that some of these traversal methods
	 * have constant overloads, allowing the caller to use them
	 * even in constant contexts. Notice this method is marked
	 * as "const", and also uses a callback signature
	 * that has a constant Tree pointer.
	 * 
	 */
	template <class T>
	void MyBST<T>::traverseInOrder
	(
		std::function<void(const MyBST<T>&, std::shared_ptr<MyBST<T>::Node>)> callback
	) const
	{
		//	TODO: Your code here 
		std::function<void(std::shared_ptr<Node>)> inOrder = [&](std::shared_ptr<Node> node) {
			if(!node){
				return; 
			}
			inOrder(node->getLeftChild());
			
			callback(*this, node);
			
			inOrder(node->getRightChild());
		};
		inOrder(root_);
	}
	
	/**
	 * This is the non-const overload of traverseInOrder.
	 */
	template <class T>
	void MyBST<T>::traverseInOrder
	(
		std::function<void(MyBST<T>&, std::shared_ptr<MyBST<T>::Node>)> callback
	)
	{
		//	TODO: Your code here
			std::function<void(std::shared_ptr<Node>)> inOrder = [&](std::shared_ptr<Node> node) {
			if(!node){
				return; 
			}
			inOrder(node->getLeftChild());
			
			callback(*this, node);
			
			inOrder(node->getRightChild());
		};
		inOrder(root_);
	}
	
	/**
	 * Traverse the Tree using post-order (non-const)
	 */
	template <class T>
	void MyBST<T>::traversePostOrder
	(
		std::function<void(MyBST<T>&, std::shared_ptr<MyBST<T>::Node>)> callback
	)
	{
		std::function<void(std::shared_ptr<Node>)> postOrder = [&](std::shared_ptr<Node> node) {
   		if (!node) {
        		return;
    		}
    		
    		postOrder(node->getLeftChild());
    		postOrder(node->getRightChild());
    		
    		callback(*this, node);
    		
		};
		postOrder(root_);
	}
	
	/**
	 * YOUR WELCOME
	 * 
	 * Traverse the Tree using level-order (const version).
	 * 
	 * DO NOT MODIFY this method, as it may be considered tampering with
	 * the unit tests and result in a 0 for the entire assignment.
	 */
	template <class T>
	void MyBST<T>::traverseLevelOrder
	(
		std::function<bool(const MyBST<T>&, std::shared_ptr<MyBST<T>::Node>)> callback
	) const
	{
		this->traverseLevelOrder(this->root_, callback);
	}
	
	/**
	 * YOUR WELCOME
	 * 
	 * Traverse the Tree using level-order (non-const version).
	 * 
	 * DO NOT MODIFY this method, as it may be considered tampering with
	 * the unit tests and result in a 0 for the entire assignment.
	 */
	template <class T>
	void MyBST<T>::traverseLevelOrder
	(
		std::function<bool(MyBST<T>&, std::shared_ptr<MyBST<T>::Node>)> callback
	)
	{
		this->traverseLevelOrder(this->root_, callback);
	}
	
	/**
	 * Clear the Tree by removing every Node.
	 * (results in an empty Tree)
	 */
	template <class T>
	void MyBST<T>::clear()
	{	   // While the tree is not empty, remove the root node
   		while (root_) {
        	remove(root_); // Remove the root node iteratively
    	}

    // After all nodes have been removed, reset size
    	size_ = 0;
		root_ = nullptr;
		size_ = 0;
	
	}
	
	///	Return true if the Tree is empty
	template <class T>
	bool MyBST<T>::empty() const
	{
		if (root_ == nullptr) {
			return true;
		} else {
		return false;
		}
	}
	
	/**
	 * Return the number of values in this Tree
	 * 
	 * This should run in constant time, not linear!
	 */
	template <class T>
	size_t MyBST<T>::size() const
	{
		return size_;
	}
	
	/**
	 * Locate the deepest leaf in the tree,
	 * and return it as a Node pointer.
	 * 
	 * Running in Linear time is fine.
	 */
	template <class T>
	std::shared_ptr<class MyBST<T>::Node> MyBST<T>::getDeepestLeaf()
	{
		return nullptr;
	}
	
	/**
	 * Compute the height of the Tree and return to the caller.
	 * 
	 * Running in linear time is OK.
	 */
	template <class T>
	size_t MyBST<T>::computeHeight()
	{
		
		return root_->getHeight(root_.get());
	}
	
	
	/**
	 * YOUR WELCOME
	 * 
	 * You should not modify this method, but should study it
	 * for your own learning.
	 * 
	 * This basically generates a graph in the "dot" language,
	 * which we can use with the "dot" program (from graphviz)
	 * to render a pretty pretty graph to an image file.
	 * 
	 * When you manipulate your Tree using the main() TUI's,
	 * you should notice a graph continually being updated
	 * in the file system. You can open it with an image viewer
	 * and see a visual representation of your Tree,
	 * to help your debugging! :)
	 * 
	 */
	template <class T>
	std::string MyBST<T>::renderToDot() const
	{
		std::stringstream ss;
		size_t null_count = 0;
		
		ss
			<< "digraph \"MyBST\"" << endl
			<< "{" << endl
				<< "\tlabelloc=\"t\";" << endl
				<< "\tlabel=\"My BST\";" << endl
			;
		
		this->traverseLevelOrder
		(
			[&ss, &null_count](const MyBST<T>& t, std::shared_ptr<MyBST<T>::Node> node) -> bool
			{
				std::stringstream temp;
				
				temp << node->getData();
				if ( t.isRoot(node) ) {
					temp << "\nroot";
				}
				else if ( t.isLeaf(node) ) {
					temp << "\nleaf";
				}
				temp << "\nD = " << node->getDepth();
				std::string node_label = temp.str();
				
				//	Node's ID / label line
				ss
					<< "\t\"" << node->getData() << "\""
					<< " [label=\"" << node_label << "\"]"
					<< ";"
					<< endl
					;
				
				std::shared_ptr<MyBST<T>::Node> p;
				
				//	Left child
				p = node->getLeftChild();
				ss << "\t\"" << node->getData() << "\" -> ";
				if ( p ) {
					ss << "\"" << p->getData() << "\"";
				}
				else {
					ss << "null" << null_count;
					null_count++;
				}
				ss << " [label=\"left\"]" << endl;
				
				//	Right child
				p = node->getRightChild();
				ss << "\t\"" << node->getData() << "\" -> ";
				if ( p ) {
					ss << "\"" << p->getData() << "\"";
				}
				else {
					ss << "null" << null_count;
					null_count++;
				}
				ss << " [label=\"right\"]" << endl;
				
				return true;
			}
		);
		
		for ( size_t i = 0; i < null_count; i++ ) {
			ss << "\tnull" << i << "[shape=point][color=red][width=0.2][height=0.2]" << endl;
		}
		
		ss
			<< "}" << endl
			;
		
		return ss.str();
	}
	
	/**
	 * Return true if the two Trees are "equal".
	 * 
	 * In this project, we consider two Trees to be equal
	 * when they have the exact same topology, including
	 * all values
	 * 
	 * We do NOT consider whether their pointer addresses are the same,
	 * because we're not supposed to be engaging in pointer-stealing
	 * anyway.
	 */
	template <class T>
	bool MyBST<T>::operator==(const MyBST<T>& other)
	{
		if (this->size_ != other.size_){
			return false;
		}
		if (this->empty() && other.empty()) {
       		return true;
    	}
		std::queue<std::shared_ptr<Node>> this_q, other_q;
		this_q.push(this->root_);
		other_q.push(other.root_);

		while(this_q.empty()==false && other_q.empty()==false){
			auto this_node = this_q.front();
			auto other_node = other_q.front();
			this_q.pop();
			other_q.pop();

			if(this_node->getData() != other_node->getData()){
				return false;
			}
			
			if(this_node->getLeftChild()&&other_node->getLeftChild()){
				this_q.push(this_node->getLeftChild());
				other_q.push(other_node->getLeftChild());
			} else if(this_node->getLeftChild()||other_node->getLeftChild()){
				return false;
			}

			if(this_node->getRightChild()&&other_node->getRightChild()){
				this_q.push(this_node->getRightChild());
				other_q.push(other_node->getRightChild());
			} else if(this_node->getRightChild()||other_node->getRightChild()){
				return false;
			}
		}
		return true;
	}
	
	/// Return true if the Trees are not equal (opposite of ==)
	template <class T>
	bool MyBST<T>::operator!=(const MyBST<T>& other)
	{
		if(*this == other){
			return false;
		}
		else return true;
	}
	
	/**
	 * Assignment operator.
	 * 
	 * In this project, this should accomplish the same thing
	 * as the Copy CTOR.
	 */
	template <class T>
	class MyBST<T>& MyBST<T>::operator=(const MyBST<T>& other)
	{
		//self-assign  check 
		if(this == &other){
			return *this;
		}

		this->clear(); //clear the tree for new copy 

		if(other.empty()==false){
			this->root_ = std::make_shared<Node>(*other.root_);
        	this->size_ = other.size_;

			std::queue<std::shared_ptr<Node>> this_q, other_q; //create 2 queue to store the current node of current tree and rhs tree
			this_q.push(this->root_);
			other_q.push(other.root_);

			while(other_q.empty() == false){
				auto this_node = this_q.front();
				auto other_node = other_q.front();
				this_q.pop();
				other_q.pop();

				//left subtree copy
				if (other_node->getLeftChild()) {
               		auto temp_lc = std::make_shared<Node>(*other_node->getLeftChild()); //temporary left child 
                	this_node->setLeftChild(temp_lc);
                	temp_lc->setParent(this_node);
                	this_q.push(temp_lc);
                	other_q.push(other_node->getLeftChild());
          		 }

				//right subtree copy
           		if (other_node->getRightChild()) {
         	    	auto temp_rc = std::make_shared<Node>(*other_node->getRightChild());//temporary right child
                	this_node->setRightChild(temp_rc);
                	temp_rc->setParent(this_node);
                	this_q.push(temp_rc);
                	other_q.push(other_node->getRightChild());
            	}
			}
		}
		return *this;
	}
	
	/**
	 * YOUR WELCOME
	 * 
	 * You are not required to know level-order traversal at this stage,
	 * so this method has been completed on your behalf.
	 * 
	 * If you are curious, study this method a bit, as it is essentially
	 * "breadth first search", an iterative algorithm we'll learn
	 * later in the semester.
	 * 
	 * DO NOT MODIFY this, as it may be considered tampering with
	 * the unit tests and result in a 0 for the entire assignment.
	 */
	template <class T>
	void MyBST<T>::traverseLevelOrder
	(
		std::shared_ptr<MyBST<T>::Node> node,
		std::function<bool(const MyBST&, std::shared_ptr<MyBST<T>::Node>)> callback
	) const
	{
		//	Ignore empty trees
		if ( this->empty() ) {
			return;
		}
		
		//	Start with a queue, seeded with the root node
		std::queue<std::shared_ptr<MyBST<T>::Node>> q;
		q.push(node);
		
		while ( !q.empty() )
		{
			//	Pluck a node and visit
			auto node = q.front();
			q.pop();
			
			if ( !callback(*this, node) ) {
				return;
			}
			
			//	Enqueue the Node's children, if any
			if ( node->getLeftChild() ) {
				q.push(node->getLeftChild());
			}
			if ( node->getRightChild() ) {
				q.push(node->getRightChild());
			}
		}
	}
	
	/**
	 * YOUR WELCOME
	 * 
	 * You are not required to know level-order traversal at this stage,
	 * so this method has been completed on your behalf.
	 * 
	 * If you are curious, study this method a bit, as it is essentially
	 * "breadth first search", an iterative algorithm we'll learn
	 * later in the semester.
	 * 
	 * DO NOT MODIFY this method, as it may be considered tampering with
	 * the unit tests and result in a 0 for the entire assignment.
	 */
	template <class T>
	void MyBST<T>::traverseLevelOrder
	(
		std::shared_ptr<MyBST<T>::Node> node,
		std::function<bool(MyBST&, std::shared_ptr<MyBST<T>::Node>)> callback
	)
	{
		//	Ignore empty trees
		if ( this->empty() ) {
			return;
		}
		
		//	Start with a queue, seeded with the root node
		std::queue<std::shared_ptr<MyBST<T>::Node>> q;
		q.push(node);
		
		while ( !q.empty() )
		{
			//	Pluck a node and visit
			auto node = q.front();
			q.pop();
			
			if ( !callback(*this, node) ) {
				return;
			}
			
			//	Enqueue the Node's children, if any
			if ( node->getLeftChild() ) {
				q.push(node->getLeftChild());
			}
			if ( node->getRightChild() ) {
				q.push(node->getRightChild());
			}
		}
	}
}
#endif
