/*
 * Universal.cpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */

#include "Universal.hpp"
#include "boost/lockfree/queue.hpp"
namespace  Universal{
Object::~Object(){

}
	Object * Object::addChild(std::string name){
		Object * tmp = new Object(this,name);
		childs.push_back(tmp);
		return tmp;
	}
	//Deprecated: Names can potentially be doubled and only the first match will be removed but someone may intend exactly that behavior so it is in there..
	void Object::removeChild(std::string name){

		int i = 0;
			while(i < childs.size()){
				if(childs[i]->name == name){
					delete childs[i];
					childs.erase(childs.begin()+i);
				}
				i++;

			}
	}
	//Pointers can't be double so this really is the way to go you get the Pointer by using addChild(std::string name)
	void Object::removeChild(Object * ptr){

			int i = 0;
				while(i < childs.size()){
					if(childs[i] == ptr){
						delete childs[i];
						childs.erase(childs.begin()+i);
					}
					i++;

				}
		}

	std::vector<Object *> Object::getChilds(){
		return childs;
	}
	void Object::tick(){

	}
	void Object::postData(BaseTypes::Data data){

	}
	Scene::Scene():DataUpdateQue(),Objects(){

	}
	Scene::~Scene(){

	}
	Object * Scene::addObject(std::string name){
		Object * tmp = new Object(this,name);
		Objects.push_back(tmp);
		return tmp;
	}
	//Deprecated: Names can potentially be doubled and only the first match will be removed but someone may intend exactly that behavior so it is in there..
	void Scene::removeObject(std::string name){

		int i = 0;
			while(i < Objects.size()){
				if(Objects[i]->name == name){
					delete Objects[i];
					Objects.erase(Objects.begin()+i);
				}
				i++;

			}
	}
	//Pointers can't be double so this really is the way to go you get the Pointer by using addChild(std::string name)
	void Scene::removeObject(Object * ptr){

			int i = 0;
				while(i < Objects.size()){
					if(Objects[i] == ptr){
						delete Objects[i];
						Objects.erase(Objects.begin()+i);
					}
					i++;

				}
		}

	std::vector<Object *> Scene::getObjects(){
		return Objects;
	}
	void Scene::tick(){

	}
	void Scene::postData(BaseTypes::Data data){

	}
}

