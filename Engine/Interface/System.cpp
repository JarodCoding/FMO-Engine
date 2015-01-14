/*
 * System.cpp
 *	
 *  Created on: Sep 17, 2014
 *      Author: Pascal Kuthe
 */
#include "System.hpp"
#include "../CoreEngine/Framework/Universal.hpp"
//INode:

template<typename T>
int INode::postDataChange(std::string name,T &value){
		return postDataChange(translateToID(name),&value,sizeof(value));

}
int INode::postDataChange(std::string name,uint64_t newSize){
	postDataChange(translateToID(name),newSize);
}
int INode::postDataChange(unsigned int id,uint64_t newSize){
	data[id]->updateData(newSize);}




int INode::postDataChange(unsigned int id,void * value,uint64_t newSize){
		if(newSize <= 0 || id <= 0 || value == nullptr)return -1;
		data[id]->updateData(value,newSize);
		return 0;

}
int INode::postDataChange(std::string name ,void * value,uint64_t newSize){
		return postDataChange(translateToID(name),value,newSize);
}

//IScene:
IScene::IScene(Universal::Scene& p_parent):parent(p_parent),data(nullptr){
}

IScene::~IScene(){

}

IObject IScene::createObjectExtension(Universal::Object& object){

}
