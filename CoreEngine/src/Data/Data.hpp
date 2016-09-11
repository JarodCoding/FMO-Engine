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
#include <unordered_map>
#include <map>
#define populate_new_extension "pne"
#define populate_remove_extension "prme"
#define populate_new_child "pnc"
#define populate_remove_child "prmc"
#define populate_move_node "pmn"
#define populate_new_node_id "pnni"
#define populate_move_extension "pme"

namespace Data{
	extern unsigned int ThreadID; //TODO get actual thread id

	typedef uint_fast64_t NodeID	 ; // creation thread id + InThread UUID (incremental
	typedef uint_fast32_t ExtensionTypeID;
	typedef uint_fast8_t LocalID;

	class Node;
	class Extension;

	namespace Universal{

		class Node;
		class Extension;
	}
	namespace Universal{

		class Node{
			private:
			  friend class Extension;
			  friend class Data::Node;
			  friend class Data::Extension
				Data::Node * actualNodes;
			protected:
				void populateChanges(Data::Property& changes) ;
 				void populateNewChild(std::shared_ptr<Universal::Node>) ;
				void populateRemovedChild(NodeID id) ;
				void populateExtension(std::shared_ptr<Universal::Extension>) ;
				void populateMove(Node& newParent) ;
				void populateNewID(NodeID newID);
				void populateReduction(ExtensionTypeID) ;
			public:
			  	Node(NodeID,Universal::Node *);
			  	~Node();
				Data::Node &access();




		};
		class Extension{
			  friend class Node;
			  friend class Data::Node;
			  friend class Data::Extension;

			protected:
				Data::Extension **actualExtensions;
				ExtensionTypeID Type;
				Universal::Node& Node;
				void populateMove(Universal::Node&);

			public:
				Extension(Universal::Node&,ExtensionTypeID type);
				~Extension();
				Universal::Node& getNode();
				ExtensionTypeID getType();
				Data::Extension *access();
				void populateChanges(Data::Property& changes) ;
		};

	}
	extern NodeID nextNodeID();
	class Node: public Syncable {
		  friend class Extension;
		  friend class Universal::Node;
		  friend class Universal::Extension;
		protected:
			Universal::Node *parent;
			Universal::Node& Universal;
			std::unordered_map<NodeID,std::shared_ptr<Universal::Node>> children;
			std::map<ExtensionTypeID,std::shared_ptr<Universal::Extension>> extensions;
			NodeID ID;
			void local_addChild(std::shared_ptr<Universal::Node>);
			bool local_removeChild(NodeID id);
			void local_extend(std::shared_ptr<Universal::Extension>);
			bool local_reduce(ExtensionTypeID);
			void addChild(std::shared_ptr<Universal::Node>);
			std::shared_ptr<Universal::Node> getChildOwnership(NodeID id);
		public:
			Node(Universal::Node *parent,Universal::Node& Universal,NodeID id);
		  	~Node() = default;
			void extend(ExtensionTypeID);
			void reduce(ExtensionTypeID);
			NodeID addChild();
			NodeID move(Universal::Node &newParent);
			void removeChild(NodeID id);
			Universal::Extension *getExtension(ExtensionTypeID);
			Universal::Node& getUniversal();
			Universal::Node *getParent();
			Universal::Node *getChild(NodeID id);
			NodeID getID();
			//very resource intensive should only be called if performance is of no concern
			Universal::Node *searchForNode(NodeID id);
			void sync(Property *);
			void syncNode(std::vector<ExtensionTypeID> sortedExtensionsOfInterest);
			std::string getTypeName();
			Clonable* clone();
			void clone(Clonable *);


	};
	class Extension: public Syncable {
		  friend class Node;
		  friend class Universal::Node;
		  friend class Universal::Extension;
		private:
			Universal::Node *Node;
			Universal::Extension& Universal;
			void local_move(Universal::Node& newNode);
		public:
			Extension(Universal::Node&,Universal::Extension&);
			virtual ~Extension() = default;
			Universal::Extension& getUniversal();
			Universal::Node& getNode();
			void sync(Property *);
			void move(Universal::Node& newNode);
			virtual void sync(Property&) = 0;

	};

	extern Universal::Node& getTopNode();
}

#endif /* UNIVERSAL_HPP_ */
