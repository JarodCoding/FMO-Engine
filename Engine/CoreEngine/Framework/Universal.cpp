/*
 * Universal.cpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */

#include "Universal.hpp"
#include "boost/lockfree/queue.hpp"
	class UpdateObjectData{
			public:
				inline UpdateObjectData(Universal::Object* obj):object(obj){

				}
				Universal::Object* object;
				inline void operator()(BaseTypes::Data *data){

				}
		};
	class UpdateSceneData{
			public:
				inline UpdateSceneData(Universal::Scene* scn):scene(scn){

				}
				Universal::Scene* scene;
				inline void operator()(BaseTypes::Data *data){

				}
		};
namespace  Universal{
Object::~Object(){

}
	uint_fast32_t Object::addChild(std::string name){
		Object * tmp = new Object(this,name);
		childs.push_back(tmp);
		return childs.size()-1;
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
	//Use this each ID is (obviously) unique. You get the ID by using addChild(std::string name)
	void Object::removeChild(uint_fast32_t id){
		delete childs[id];
		childs.erase(childs.begin()+id);
	}
	//Pointers can't be double so this is safe calling
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
		DataUpdateQue.consume_all(UpdateData(this));

	}
	void Object::postData(BaseTypes::Data *data){

	}
	Scene::Scene():DataUpdateQue(),Objects(){

	}
	Scene::~Scene(){

	}
	uint_fast32_t Scene::addObject(std::string name){
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

	//Use this each ID is (obviously) unique. You get the ID by using addChild(std::string name)
	void Object::removeObject(uint_fast32_t id){
		delete childs[id];
		childs.erase(childs.begin()+id);
	}

	//Pointers can't be double so this is safe calling
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
		DataUpdateQue.consume_all(UpdateData(this));
	}
	void Scene::postData(BaseTypes::Data* data){
		DataUpdateQue.push(data);
	}
}

