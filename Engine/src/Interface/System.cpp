/*
 * System.cpp
 *	
 *  Created on: Sep 17, 2014
 *      Author: Pascal Kuthe
 */
#include "System.hpp"
#include "../CoreEngine/Framework/Universal.hpp"
//INode:
INode::INode(INode &parent):parent(parent),dataSize(0)data(nullptr),names(){

}
virtual ~INode();
int INode::postDataChange(std::string name){
	return postDataChange(translateToID(name));

}
int INode::postDataChange(unsigned int id ){
	if(id<0||dataSize<id)return -1;
	//TODO: Populate Changes
	return 0;
}
int INode::postDataChange(std::string name,uint64_t newSize){
	unsigned int id = translateToID(name);
	int res =  postDataChange(id);
	if(res < 0)return res;

	BaseTypes::CustomData *d  = (BaseTypes::CustomData *)data[id];
	d->update(newSize);
	return res;
}
int INode::postDataChange(unsigned int id,uint64_t newSize){
	int res =  postDataChange(id);
	if(res < 0)return res;
	BaseTypes::CustomData *tmp = (BaseTypes::CustomData *) data[id];
	tmp->update(newSize);
	return res;

}
int INode::postDataChange(unsigned int id,void * value,uint64_t newSize){
		if(newSize <= 0)return -1;
		BaseTypes::CustomData *tmp = (BaseTypes::CustomData *)data[id];
		tmp->update(value,newSize);
		return 0;

}


//IScene:
IScene::IScene(Universal::Scene& p_parent):parent(p_parent), INode((INode &)p_parent){
}

IScene::~IScene(){

}

IObject IScene::createObjectExtension(Universal::Object& object){

}
