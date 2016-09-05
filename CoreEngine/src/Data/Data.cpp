/*
 * Universal.cpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */

#include "Data.hpp"

namespace Data{
	namespace Universal{
		NodeID Node::getID(){
			return id;
		}
		Data::Node *Node::access(){
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
		void Node::populateInvaledation(){
			Property invaledation = Property("Invalid",nullptr);
			populateChanges(invaledation);
		}
	}
}
