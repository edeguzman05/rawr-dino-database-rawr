

/**
 *Name: Minh Tran Nguyen & Emmanuel De Guzman 
 *CWID: 826519571
 *CWID: 884886995
 *Email: minh_nguyen582@csu.fullerton.edu & edeguzmanjr05@csu.fullerton.edu
 */

#include "Dinosaur.hpp"


#include <iostream>
#include <sstream>
#include <string>


using std::cout, std::endl;
using std::string;


namespace CPSC131::Databases::Dinosaurs
{
	///	Constructor
	Dinosaur::Dinosaur()
	{
		id_ = 0;
		name_ = (""); 
		diet_ =  ("");
		period_ = ("");
		lived_in_ =  ("");
		type_ =  ("");
		length_ =  ("");
		taxonomy_ =  ("");
		named_by_ =  ("");
		species_ =  ("");
		link_ =  ("");
	}
	
	///	Copy Constructor (Copy CTOR)
	Dinosaur::Dinosaur(const Dinosaur& other)
	{
		id_ = other.id_;
		name_ = other.name_;
		diet_ = other.diet_;
		period_ = other.period_;
		lived_in_ = other.lived_in_;
		type_ = other.type_;
		length_ = other.length_;
		taxonomy_ = other.taxonomy_;
		named_by_ = other.named_by_;
		species_ = other.species_;
		link_ = other.link_;
		
	}
	/**
	 * Assignment operator
	 * 
	 * What does it mean to copy one Dinosaur object to another?
	 * 
	 * For this project, we'll say this is simply a matter of
	 * copying each member, by value.
	 */
	const Dinosaur& Dinosaur::operator=(const Dinosaur& other)
	{
		if (this != &other) {
			id_ = other.id_;
			name_ = other.name_;
			diet_ = other.diet_;
			period_ = other.period_;
			lived_in_ = other.lived_in_;
			type_ = other.type_;
			length_ = other.length_;
			taxonomy_ = other.taxonomy_;
			named_by_ = other.named_by_;
			species_ = other.species_;
			link_ = other.link_;
		}
		return *this;
	}
	
	/**
	 * Comparison/Equality operator.
	 * 
	 * For this project, we'll say that two Dinosaur objects are "equal"
	 * if they have matching IDs, and nothing else.
	 * 
	 * This will allow our BST to easily compare these objects.
	 */
	bool Dinosaur::operator==(const Dinosaur& other)
	{
		if (id_ == other.id_) {
			return true;		
		}
		
		return false;
	}
	
	///	Inequality operator; The opposite of the equality operator
	bool Dinosaur::operator!=(const Dinosaur& other)
	{
		if (id_ != other.id_) {
			return true;		
		}
		return false;
	}
	
	/**
	 * Greater-than comparison operator.
	 * 
	 * Because our BST will attempt to use this operator to sort
	 * our Dinosaur objects, we'll only consider the ID member
	 * and nothing else.
	 * 
	 * (this is to simplify tests; in your own implementations
	 * later in life, you may wish to do something more complex)
	 */
	bool Dinosaur::operator>(const Dinosaur& other)
	{
		if (id_ > other.id_) {
			return true;
		}
		return false;
	}
	
	/**
	 * Greater-than-or-equal comparison operator.
	 * Again, with all Dinosaur comparison operators
	 * in this project, we'll only consider the ID
	 */
	bool Dinosaur::operator>=(const Dinosaur& other)
	{
		if (id_ >= other.id_) {
			return true;
		}
		return false;
	}
	
	///	Less-than comparison operator
	bool Dinosaur::operator<(const Dinosaur& other)
	{
		if (id_ < other.id_) {
			return true;
		}
		return false;
	}
	
	///	Less-than-or-equal comparison operator
	bool Dinosaur::operator<=(const Dinosaur& other)
	{
		if (id_ <= other.id_) {
			return true;
		}
		return false;
	}
	
	/********************************************
	 * Begin self-explanatory getters and setters
	 *******************************************/
	void Dinosaur::setID(size_t id)
	{
		id_ = id;
	}
	
	size_t Dinosaur::getID()
	{	
		return id_;
	}
	
	void Dinosaur::setName(string s)
	{
		name_ = s;
	}
	
	string Dinosaur::getName()
	{	
		return name_;
	}
	
	void Dinosaur::setDiet(string s)
	{
		diet_ = s;
	}
	string Dinosaur::getDiet()
	{	
		return diet_;
	}
	
	void Dinosaur::setPeriod(string s)
	{
		period_ = s;
	}
	string Dinosaur::getPeriod()
	{	
		return period_;
	}
	
	void Dinosaur::setLivedIn(string s)
	{
		 lived_in_ = s;
	}
	string Dinosaur::getLivedIn()
	{	
		return lived_in_;
	}
	
	void Dinosaur::setType(string s)
	{
		type_ = s;
	}
	string Dinosaur::getType()
	{	
		return type_;
	}
	
	void Dinosaur::setLength(std::string s)
	{
		length_ = s;
	}
	std::string Dinosaur::getLength()
	{	
		return length_;
	}
	
	void Dinosaur::setTaxonomy(std::string s)
	{
		taxonomy_ = s;
	}
	std::string Dinosaur::getTaxonomy()
	{	
		return taxonomy_;
	}
	
	void Dinosaur::setNamedBy(std::string s)
	{
		named_by_ = s;
	}
	std::string Dinosaur::getNamedBy()
	{	
		return named_by_;
	}
	
	void Dinosaur::setSpecies(std::string s)
	{
		species_ = s;
	}
	std::string Dinosaur::getSpecies()
	{	
		return species_;
	}
	
	void Dinosaur::setLink(std::string s)
	{
		link_ = s;
	}
	std::string Dinosaur::getLink()
	{
		return link_;
	}
	
	///	YOUR WELCOME
	string Dinosaur::toString()
	{
		std::stringstream ss;
		
		//
		ss
			<< "*** Dinosaur ***" << endl
			<< "> ID: " << std::to_string(this->id_) << endl
			<< "> Name: " << this->name_ << endl
			<< "> Diet: " << this->diet_ << endl
			<< "> Period: " << this->period_ << endl
			<< "> Lived in: " << this->lived_in_ << endl
			<< "> Type: " << this->type_ << endl
			<< "> Length: " << this->length_ << endl
			<< "> Taxonomy: " << this->taxonomy_ << endl
			<< "> Named by: " << this->named_by_ << endl
			<< "> Species: " << this->species_ << endl
			<< "> Link: " << this->link_ << endl
			;
		
		return ss.str();
	}
}

