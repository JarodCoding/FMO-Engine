/*
 * Universal.cpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */

#include "Data.hpp"
#include "ClonableWrapper.hpp"
#include "ExtensionType.hpp"
#include <type_traits>
#include <atomic>

namespace Data{
	std::atomic<NodeID> currentID;
	std::unique_ptr<Universal::Node> topNode = std::make_unique<Universal::Node>(0,nullptr);
	NodeID nextNodeID(){
		return currentID++;

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
			    new(&actualNodes[i]) Data::Node(parent,*this,ID);
			}
		}
		Node::~Node(){
			for(uint_fast8_t i = 0;i < Thread::Amount;i++){
				actualNodes[i].~Node();
			}
			delete[] reinterpret_cast<RawNode *>(actualNodes);
		}
		Data::Node &Node::access(){

			return actualNodes[Execution::TaskManager::getCurrentThreadID()];
		}

		Data::Node &Node::access(Thread::ID t_id){

			return actualNodes[t_id];
		}
		void Node::populateChanges(Data::Property& changes){

			uint_fast8_t i = 0;
			Thread::ID t_id = Execution::TaskManager::getCurrentThreadID();
			while(i < Thread::Amount){
				if(i==t_id){
					i++;
					continue;
				}

				actualNodes[i].notify(changes);
				i++;
			}

		}
		void Node::populateChanges(Data::Property& changes,Thread::ID t_id){
			uint_fast8_t i = 0;
			while(i < Thread::Amount){
				if(i==t_id){
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
			}
			void Node::populateReduction(ExtensionTypeID ID){
				ClonableWrapper<ExtensionTypeID> * tmp = new ClonableWrapper<ExtensionTypeID>(ID);
				Property res = Property(populate_remove_extension,tmp);
				populateChanges(res);
			}
			void Node::populateNewChild(std::shared_ptr<Node> NewChild){
				ClonableWrapper<std::shared_ptr<Node>> * tmp =new ClonableWrapper<std::shared_ptr<Node>>(NewChild);
				Property res = Property(populate_new_child,tmp);
				populateChanges(res);
			}
			void Node::populateRemovedChild(NodeID id){
				ClonableWrapper<NodeID> * tmp = new ClonableWrapper<NodeID>(id);
				Property res = Property(populate_remove_child,tmp);
				populateChanges(res);
			}
			void Node::populateMove(Node& newParent){
				ClonableWrapper<Node *> * tmp = new ClonableWrapper<Node *>(&newParent);
				Property res = Property(populate_move_node,tmp);
				populateChanges(res);
			}
			void Node::populateMove(Node& newParent,Thread::ID t_id){
				ClonableWrapper<Node *> * tmp = new ClonableWrapper<Node *>(&newParent);
				Property res = Property(populate_move_node,tmp);
				populateChanges(res,t_id);
			}
			void Node::populateNewID(NodeID newID){
				ClonableWrapper<NodeID> * tmp = new ClonableWrapper<NodeID>(newID);
				Property res = Property(populate_new_node_id,tmp);
				populateChanges(res);
			}
			void Node::populateNewID(NodeID newID,Thread::ID t_id){
				ClonableWrapper<NodeID> * tmp = new ClonableWrapper<NodeID>(newID);
				Property res = Property(populate_new_node_id,tmp);
				populateChanges(res,t_id);
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

				return actualExtensions[Execution::TaskManager::getCurrentThreadID()];
			}
			Data::Extension *Extension::access(Thread::ID t_id){

				return actualExtensions[t_id];
			}

			void Extension::populateChanges(Data::Property& changes){

				uint_fast8_t i = 0;
				Thread::ID t_id = Execution::TaskManager::getCurrentThreadID();
				while(i < Thread::Amount){
					if(i==t_id){
						i++;
						continue;
					}
					actualExtensions[i]->notify(changes);
					i++;
				}
			}
			void Extension::populateChanges(Data::Property& changes,Thread::ID t_id){

				uint_fast8_t i = 0;
				while(i < Thread::Amount){
					if(i==t_id){
						i++;
						continue;
					}
					actualExtensions[i]->notify(changes);
					i++;
				}
			}
			void Extension::populateMove(Universal::Node& newNode){
				ClonableWrapper<Universal::Node *> * tmp = new ClonableWrapper<Universal::Node *>(&newNode);
				Property res = Property(populate_move_extension,tmp);
				populateChanges(res);
			}
			void Extension::populateMove(Universal::Node& newNode,Thread::ID t_id){
				ClonableWrapper<Universal::Node *> * tmp = new ClonableWrapper<Universal::Node *>(&newNode);
				Property res = Property(populate_move_extension,tmp);
				populateChanges(res,t_id);
			}


			Universal::Node& Extension::getNode(){
				return Node;
			}
			ExtensionTypeID Extension::getType(){
				return Type;
			}
	}


	//Node

	Node::Node(Universal::Node *p_parent,Universal::Node& p_universal,NodeID id):parent(p_parent),Universal(p_universal),children(),extensions(),ID(id){}

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
	Universal::Node& Node::addChild(){
		NodeID id = nextNodeID();
		std::shared_ptr<Universal::Node> newChild = std::make_shared<Universal::Node>(id,parent);
		local_addChild(newChild);
		Universal.populateNewChild(newChild);
		return *newChild.get();
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
	void Node::removeChild(std::unordered_map<NodeID,std::shared_ptr<Universal::Node>>::iterator i){
		Universal.populateRemovedChild(i->first);
		children.erase(i);
	}
	void Node::destroy(){
		parent->access().removeChild(ID);
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
		NodeID Node::move(Universal::Node &newParent){
			Thread::ID t_id = Execution::TaskManager::getCurrentThreadID();
			newParent.access(t_id).addChild(parent->access().getChildOwnership(ID));
			parent->access(t_id).removeChild(ID);
			parent = &newParent;
			if(ID<parent->access(t_id).ID)ID = nextNodeID();
			Universal.populateMove(newParent,t_id);
			Universal.populateNewID(ID,t_id);
			return ID;
		}
		void Node::sync(Property *prop){
			if(prop->name==populate_new_child){
							local_addChild(((ClonableWrapper<std::shared_ptr<Universal::Node>> *)prop->data)->data);
			}else if(prop->name==populate_new_extension){
				local_extend(((ClonableWrapper<std::shared_ptr<Universal::Extension>> *)prop->data)->data);
			}else if(prop->name==populate_remove_extension){
				local_reduce(((ClonableWrapper<ExtensionTypeID> *)prop->data)->data);
			}else if(prop->name==populate_remove_child){
				local_removeChild(((ClonableWrapper<NodeID> *)prop->data)->data);
			}else if(prop->name==populate_move_node){
				parent = (((ClonableWrapper<Universal::Node *> *)prop->data)->data);
			}else if(prop->name==populate_new_node_id){
				ID = ((ClonableWrapper<NodeID> *)prop->data)->data;
			}
		}
		void Node::syncNode(std::vector<ExtensionTypeID>& sortedExtensionsOfInterest){
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
		//TODO implement cloning
		Clonable* Node::clone(){
			return nullptr;
		}
		//DOES NOT CLONE DUE CHANGES
		void Node::clone(Clonable *dest){
			if(dest->getTypeName().compare(getTypeName()))return;
			Node *res = (Node *)dest;
			res->ID = ID;
			res->Universal = Universal; //TODO clone universal
			res->parent = parent;
			//TODO clone extensions and children
		}


		Extension::Extension(Universal::Node& node,Universal::Extension& universal): Node(&node),Universal(universal) {}
		Universal::Extension& Extension::getUniversal(){
			return Universal;
		}
		Universal::Node& Extension::getNode(){
			return *Node;
		}
		void Extension::sync(Property *p){
				if(p->name == populate_move_extension){
					local_move(*((ClonableWrapper<Universal::Node *> *)p->data)->data);
				}
				sync(*p);
		}
		void Data::Extension::move(Universal::Node& newNode){
			Thread::ID t_id = Execution::TaskManager::getCurrentThreadID();
			auto iterator = Node->access(t_id).extensions.find(Universal.Type);
			newNode.access(t_id).extensions.emplace(Universal.Type,iterator->second);
			Node->access(t_id).extensions.erase(iterator);
			Node = &newNode;
			getUniversal().populateMove(newNode,t_id);
		}
		void Data::Extension::local_move(Universal::Node& newNode){
			Thread::ID t_id = Execution::TaskManager::getCurrentThreadID();
			auto iterator = Node->access(t_id).extensions.find(Universal.Type);
			newNode.access(t_id).extensions.emplace(Universal.Type,iterator->second);
			Node->access(t_id).extensions.erase(iterator);
			Node = &newNode;
		}






}
