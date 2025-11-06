#ifndef CPSC131_DATA_DINOSAURS_DINOSAUR_HPP
#define CPSC131_DATA_DINOSAURS_DINOSAUR_HPP


/**
 * You probably don't need to work on this class declaration.
 * 
 * Don't modify any existing prototypes.
 * 
 * You may add more helper functions, if you wish.
 */


#include <sstream>
#include <string>


namespace CPSC131::Databases::Dinosaurs
{
	class Dinosaur
	{
		public:
			
			Dinosaur();
			Dinosaur(const Dinosaur& other);
			
			const Dinosaur& operator=(const Dinosaur& other);
			bool operator==(const Dinosaur& other);
			bool operator!=(const Dinosaur& other);
			bool operator>(const Dinosaur& other);
			bool operator>=(const Dinosaur& other);
			bool operator<(const Dinosaur& other);
			bool operator<=(const Dinosaur& other);
			
			///	So the stream operator works
			///	(your welcome)
			friend std::ostream& operator<<(std::ostream& os, const Dinosaur& me) 
			{
				std::stringstream ss;
				
				ss << me.name_ << " (" << me.id_ << ")";
				
				os << ss.str();
				
				return os;
			}
			
			void setID(size_t id);
			size_t getID();
			
			void setName(std::string s);
			std::string getName();
			
			void setDiet(std::string s);
			std::string getDiet();
			
			void setPeriod(std::string s);
			std::string getPeriod();
			
			void setLivedIn(std::string s);
			std::string getLivedIn();
			
			void setType(std::string s);
			std::string getType();
			
			void setLength(std::string s);
			std::string getLength();
			
			void setTaxonomy(std::string s);
			std::string getTaxonomy();
			
			void setNamedBy(std::string s);
			std::string getNamedBy();
			
			void setSpecies(std::string s);
			std::string getSpecies();
			
			void setLink(std::string s);
			std::string getLink();
			
			std::string toString();
		
		private:
			
			size_t id_;
			
			std::string
				name_,
				diet_,
				period_,
				lived_in_,
				type_,
				length_,
				taxonomy_,
				named_by_,
				species_,
				link_
				;
			
	};
}

#endif
