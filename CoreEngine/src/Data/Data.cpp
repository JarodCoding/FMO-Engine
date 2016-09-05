/*
 * Universal.cpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */

#include "Data.hpp"
#include "ClonableWrapper.hpp"

namespace Data{
	namespace Universal{


		NodeID Node::getID(){
			return id;
		}
#define ThreadAmount 1 //TODO get actual ThreadAmount
		Node::Node(NodeID ID):actualNodes(new Data::Node[ThreadAmount]),id(ID){
			for(int i = 0;i < ThreadAmount;i++){
				actualNodes[i] = Data::Node( ,)
			}
		}

		Data::Node &Node::access(){
			unsigned int ThreadID; //TODO get current ThreadID
			return actualNodes[ThreadID];
		}
		void Node::populateChanges(Data::Property& changes){
			unsigned int ThreadID; //TODO get current ThreadID
			unsigned int i = 0; //TODO UseThreadID
			while(i < Thread::Amount){
				if(ThreadID != i)actualNodes[i].notify(changes);
				i++;
			}
		}
		void Node::populateExtension(std::shared_ptr<Universal::Extension> NewExtension){
			ClonableWrapper * tmp = new ClonableWrapper<std::shared_ptr<Universal::Extension>>(NewExtension);
			Property res = Property("populate_new_extension",tmp);
			populateChanges(res);
			delete tmp;
		}
		void Node::populateReduction(ExtensionTypeID ID){
			ClonableWrapper * tmp = new ClonableWrapper<ExtensionTypeID>(ID);
			Property res = Property("populate_remove_extension",tmp);
			populateChanges(res);
			delete tmp;
		}
		void Node::populateNewChild(std::shared_ptr<Node> NewChild){
			ClonableWrapper * tmp =new ClonableWrapper<std::shared_ptr<Node>>(NewChild);
			Property res = Property("populate_new_child",tmp);
			populateChanges(res);
			delete tmp;
		}
		void Node::populateRemovedChild(LocalID id){
			ClonableWrapper * tmp = new ClonableWrapper<LocalID>(id);
			Property res = Property("populate_remove_child",tmp);
			populateChanges(res);
			delete tmp;
		}


		Extension::Extension(Universal::Node& parent,ExtensionTypeID type,ExtensionInitFunction): actualExtensions(new Data::Extension *[ThreadAmount]),Type(type),Node(parent){
			for(int i = 0;i < ThreadAmount;i++){
				actualExtensions[i] = Data::ExtensionType::getInitFunction(type)(parent,*this);
			}

		}

	}
}
