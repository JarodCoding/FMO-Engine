/*
 * Universal.hpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */
#ifndef UNIVERSAL_HPP_
#define UNIVERSAL_HPP_

 #include <stdint.h>
#include "Syncable.hpp"
#include "vector"
#include <memory>

namespace Data{
	typedef uint_fast64_t NodeID	 ; // creation thread id + InThread UUID (incremental
	typedef uint_fast8_t  ExtnesionID;
	typedef uint_fast32_t ExtensionTypeID;

	class Node;
	class Extension;

	namespace Universal{

		class Node;
		class Extension;
	}
	typedef Data::Extension *(*ExtensionInitFunction)(Universal::Extension);
	namespace Universal{

		class Node{
			  friend class Extension;
			  friend class Data::Node;
			  friend class Data::Extension;
			protected:
				Data::Node * actualNodes;
				NodeID id;
			public:
				NodeID getID();
				Data::Node *access();
				void populateChanges(Data::Property& changes) ;
				void populateInvaledation() ;
				void populateNewChild() ;
				void populateRemovedChild() ;
				void populateExtension() ;
				void populateReduction() ;



		};
		class Extension{
			  friend class Node;
			  friend class Data::Node;
			  friend class Data::Extension;

			protected:
				Extension(Universal::Node&,ExtensionTypeID type,ExtensionInitFunction);
				Universal::Node& Node;
				Data::Extension *actualExtensions;
				ExtensionTypeID Type;
			public:
				~Extension();
				Universal::Node& getNode();
				Data::Node &access();
				void populateChanges(Data::Property& changes) ;
		};

	}
	class Node: public Syncable {
		  friend class Extension;
		  friend class Universal::Node;
		  friend class Universal::Extension;
		protected:
			Universal::Node& Universal;
			std::vector<std::shared_ptr<Universal::Node>> children;
			Universal::Node& parent;
			std::vector<std::shared_ptr<Universal::Extension>> extensions;
			Node(Universal::Node& Universal);

		public:
			~Node();
			void extend(ExtensionTypeID);
			void reduce(ExtensionTypeID);
			Extension& getExtension(ExtensionTypeID);
			Universal::Node& getUniversal();
			Universal::Node& getParent();
			Universal::Node& getChild(NodeID id);
			Universal::Node& addChild();
			Universal::Node& removeChild(NodeID id);
			virtual void sync(Syncable&);
			virtual char* getTypeName();


	};
	class Extension: public Syncable {
		  friend class Node;
		  friend class Universal::Node;
		  friend class Universal::Extension;
		protected:
			Universal::Node& Universal;
			Extension(Universal::Node& Universal);
			virtual void init() = 0;
		public:
			virtual ~Extension();
			Universal::Node& getUniversal();

	};

}


#endif /* UNIVERSAL_HPP_ */
