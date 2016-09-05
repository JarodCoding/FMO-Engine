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
#define populate_new_extension pne
#define populate_remove_extension pre
#define populate_new_child pnc
#define populate_remove_child rmc

namespace Data{
	typedef uint_fast64_t NodeID	 ; // creation thread id + InThread UUID (incremental
	typedef uint_fast32_t ExtensionTypeID;
	typedef uint_fast8_t LocalID;

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
			  	Node(NodeID);
				NodeID getID();
				Data::Node &access();
				void populateChanges(Data::Property& changes) ;
 				void populateNewChild(std::shared_ptr<Universal::Node>) ;
				void populateRemovedChild(LocalID id) ;
				void populateExtension(std::shared_ptr<Universal::Extension>) ;
				void populateReduction(ExtensionTypeID) ;



		};
		class Extension{
			  friend class Node;
			  friend class Data::Node;
			  friend class Data::Extension;

			protected:
				Extension(Universal::Node&,ExtensionTypeID type,ExtensionInitFunction);
				Universal::Node& Node;
				Data::Extension **actualExtensions;
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
			Universal::Node *parent;
			std::vector<std::shared_ptr<Universal::Extension>> extensions;
			Node(Universal::Node& Universal);

		public:
			Node(Universal::Node *,std::shared_ptr<Universal::Node>);
			~Node();
			void extend(ExtensionTypeID);
			void reduce(ExtensionTypeID);
			Extension& getExtension(ExtensionTypeID);
			Universal::Node& getUniversal();
			Universal::Node& getParent();
			Universal::Node& getChild(LocalID id);
			Universal::Node& getChild(NodeID id);
			Universal::Node& addChild();
			Universal::Node& addChild(NodeID id);
			Universal::Node& removeChild(LocalID id);
			Universal::Node& removeChild(NodeID id);
			virtual void sync(Property *);
			virtual char* getTypeName();
			virtual Clonable* clone();
			virtual void clone(Clonable *);


	};
	class Extension: public Syncable {
		  friend class Node;
		  friend class Universal::Node;
		  friend class Universal::Extension;
		protected:
			Universal::Node& Node;
			Universal::Extension& Universal;
			Extension(Universal::Node&,Universal::Extension&);
		public:
			virtual ~Extension();
			Universal::Node& getUniversal();

	};

}


#endif /* UNIVERSAL_HPP_ */
