/*
 * Universal.cpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */

#include "Data.hpp"
#include "ClonableWrapper.hpp"
#include "ExtensionType.hpp"
#include "../Execution/Flags.hpp"
#include <type_traits>

namespace Data{
	unsigned int ThreadID = 0; //TODO get actual thread id

	std::unique_ptr<Universal::Node> topNode = std::make_unique<Universal::Node>(0,nullptr);
	NodeID nextNodeID(){
		static NodeID currentID = 0;
		return __sync_add_and_fetch (&currentID,1);

	}

	Universal::Node& getTopNode(){
		return *topNode.get();
	}
	namespace Universal{

	//Node
	typedef std::aligned_storage<sizeof(Data::Node), alignof(Data::Node)>::type RawNode;
		Node::Node(NodeID ID,Universal::Node *parent):actualNodes (reinterpret_cast<Data::Node *>( new RawNode[Thread::Amount]))
{
			for(uint_fast8_t i = 0;i < Thread::Amount;i++){
			    new(&actualNodes[i]) Data::Node(parent,*this);
			}
		}
		Node::~Node(){
			for(uint_fast8_t i = 0;i < Thread::Amount;i++){
				actualNodes[i].~Node();
			}
			delete[] reinterpret_cast<RawNode *>(actualNodes);
		}
		Data::Node &Node::access(){

			return actualNodes[ThreadID];
		}
		void Node::populateChanges(Data::Property& changes){

			uint_fast8_t i = 0;

			while(i < Thread::Amount){
				if(i==ThreadID){
					i++;
					continue;
				}

				actualNodes[i].notify(changes);
				i++;
			}

		}
			void Node::populateExtension(std::shared_ptr<Universal::Extension> NewExtension){
				ClonableWrapper<std::shared_ptr<Universal::Extension>> * tmp = new ClonableWrapper<std::shared_ptr<Universal::Extension>>(NewExtension);
				Property res = Property(populate_new_extension,tmp);
				populateChanges(res);
				delete tmp;
			}
			void Node::populateReduction(ExtensionTypeID ID){
				ClonableWrapper<ExtensionTypeID> * tmp = new ClonableWrapper<ExtensionTypeID>(ID);
				Property res = Property(populate_remove_extension,tmp);
				populateChanges(res);
				delete tmp;
			}
			void Node::populateNewChild(std::shared_ptr<Node> NewChild){
				ClonableWrapper<std::shared_ptr<Node>> * tmp =new ClonableWrapper<std::shared_ptr<Node>>(NewChild);
				Property res = Property(populate_new_child,tmp);

				populateChanges(res);

				delete tmp;
			}
			void Node::populateRemovedChild(NodeID id){
				ClonableWrapper<NodeID> * tmp = new ClonableWrapper<NodeID>(id);
				Property res = Property(populate_remove_child,tmp);
				populateChanges(res);
				delete tmp;
			}
			void Node::populateMove(Node * newParent){
				ClonableWrapper<Node *> * tmp = new ClonableWrapper<Node *>(newParent);
				Property res = Property(populate_move_node,tmp);
				populateChanges(res);
				delete tmp;
			}
			void Node::populateNewID(NodeID newID){
				ClonableWrapper<NodeID> * tmp = new ClonableWrapper<NodeID>(newID);
				Property res = Property(populate_new_id,tmp);
				populateChanges(res);
				delete tmp;
			}


			//Extension

			Extension::Extension(Universal::Node& parent,ExtensionTypeID type): actualExtensions(new Data::Extension *[Thread::Amount]),Type(type),Node(parent){
				for(uint_fast8_t i = 0;i < Thread::Amount;i++){
					actualExtensions[i] = Data::ExtensionType::getInitFunction(type)(parent,*this);
				}
			}
			Extension::~Extension(){
				for(uint_fast8_t i = 0;i < Thread::Amount;i++){
					delete actualExtensions[i];
				}
				delete[] actualExtensions;
			}

			Data::Extension *Extension::access(){

				return actualExtensions[ThreadID];
			}

			void Extension::populateChanges(Data::Property& changes){

				uint_fast8_t i = 0;
				while(i < Thread::Amount){
					if(i==ThreadID){
						i++;
						continue;
					}
					actualExtensions[i]->notify(changes);
					i++;
				}
			}

			Universal::Node& Extension::getNode(){
				return Node;
			}
			ExtensionTypeID Extension::getType(){
				return Type;
			}
	}


	//Node

	Node::Node(Universal::Node *p_parent,Universal::Node& p_universal):parent(p_parent),Universal(p_universal),children(),extensions(),ID(nextNodeID()){}

	void Node::extend(ExtensionTypeID type){
		std::shared_ptr<Universal::Extension> newExtension = std::make_shared<Universal::Extension>(Universal,type);
		//TODO local_extend extensions.push_back(newExtension);
		local_extend(newExtension);
		Universal.populateExtension(newExtension);
	}
		void Node::local_extend(std::shared_ptr<Universal::Extension> newExtension){
			extensions.emplace(newExtension->Type,newExtension);
		}
	void Node::reduce(ExtensionTypeID type){
		if(local_reduce(type))Universal.populateReduction(type);
	}
		bool Node::local_reduce(ExtensionTypeID type){
			return extensions.erase(type)>0;
		}
	NodeID Node::addChild(){
		NodeID id = nextNodeID();
		std::shared_ptr<Universal::Node> newChild = std::make_shared<Universal::Node>(id,parent);
		local_addChild(newChild);
		Universal.populateNewChild(newChild);
		return id;
	}
	void Node::addChild(std::shared_ptr<Universal::Node> newChild){
		local_addChild(newChild);
		Universal.populateNewChild(newChild);
	}
		void Node::local_addChild(std::shared_ptr<Universal::Node> newChild){
			children.emplace(newChild->access().getID(),newChild);
		}

	void Node::removeChild(NodeID id){
		if(local_removeChild(id))Universal.populateRemovedChild(id);
	}
		bool Node::local_removeChild(NodeID id){
			return children.erase(id)>0;
		}

		Universal::Extension *Node::getExtension(ExtensionTypeID type){
			return extensions.at(type).get();

		}
		NodeID Node::getID(){
			return ID;
		}
		Universal::Node *Node::getParent(){
			return parent;
		}
		Universal::Node& Node::getUniversal(){
			return Universal;
		}
		Universal::Node *Node::getChild(NodeID id){
			return children.at(id).get();
		}
		std::shared_ptr<Universal::Node> Node::getChildOwnership(NodeID id){
			return children.at(id);

		}
		//very resource intensive should only be called if performance is of no concern
		Universal::Node *Node::searchForNode(NodeID id){
			if(id < ID)return nullptr;//performance optimisation we can do this since the ids are always increasing and child nodes are always constructed by their parents

			try{
				return children.at(id).get();
			}catch (...) {
				Universal::Node * res;
				for(auto i = children.begin(); i !=children.end();i++){
					res = i->second->access().searchForNode(id);
					if(res != nullptr) return res;
				}
			}

			return nullptr;
		}
		NodeID Node::move(Universal::Node *newParent){
			newParent->access().addChild(parent->access().getChildOwnership(ID));
			parent->access().removeChild(ID);
			parent = newParent;
			if(ID<parent->access().ID)ID = nextNodeID();
			Universal.populateMove(newParent);
			Universal.populateNewID(ID);
			return ID;
		}
		void Node::sync(Property *prop){
			if(prop->name.compare(populate_new_extension)){
				local_extend(((ClonableWrapper<std::shared_ptr<Universal::Extension>> *)prop->data)->data);
			}else if(prop->name.compare(populate_remove_extension)){
				local_reduce(((ClonableWrapper<ExtensionTypeID> *)prop->data)->data);
			}else if(prop->name.compare(populate_new_child)){
				local_addChild(((ClonableWrapper<std::shared_ptr<Universal::Node>> *)prop->data)->data);
			}else if(prop->name.compare(populate_remove_child)){
				local_removeChild(((ClonableWrapper<NodeID> *)prop->data)->data);
			}else if(prop->name.compare(populate_move_node)){
				parent = (((ClonableWrapper<Universal::Node *> *)prop->data)->data);
			}else if(prop->name.compare(populate_new_id)){
				ID = ((ClonableWrapper<NodeID> *)prop->data)->data;
			}
		}
		void Node::syncNode(std::vector<ExtensionTypeID> sortedExtensionsOfInterest){
			syncAll();
			size_t i = 0;
			auto extensionIterator = extensions.begin();
			if(sortedExtensionsOfInterest[i]==extensionIterator->first)extensionIterator->second->access()->syncAll();
			while(i <sortedExtensionsOfInterest.size() && extensionIterator!=extensions.end()){
				if(sortedExtensionsOfInterest[i]==extensionIterator->first)extensionIterator->second->access()->syncAll();
				while(i <sortedExtensionsOfInterest.size()&&sortedExtensionsOfInterest[i]<extensionIterator->first){i++;}
				if(i >= sortedExtensionsOfInterest.size())continue;
				if(sortedExtensionsOfInterest[i]==extensionIterator->first)extensionIterator->second->access()->syncAll();
				while(extensionIterator!=extensions.end()&&extensionIterator->first<sortedExtensionsOfInterest[i]){extensionIterator++;}
			}
			for(auto childIterator = children.begin();childIterator != children.end();childIterator++){
				childIterator->second->access().syncNode(sortedExtensionsOfInterest);
			}
		}
		std::string Node::getTypeName(){
			return "Data::Node";
		}
		//TODO implement cloneing
		Clonable* Node::clone(){
			return nullptr;
		}
		void Node::clone(Clonable *){

		}









}
