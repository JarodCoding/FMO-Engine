/*
 * Universal.hpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */
#ifndef UNIVERSAL_HPP_
#define UNIVERSAL_HPP_
#include "../BaseTypes/Data.hpp"
#include "list"
#include "vector"
#include "System.hpp"
#include "boost/lockfree/queue.hpp"


namespace Universal{
class Scene;


class Object{
	friend class Scene;
	protected:

	inline Object(Scene * p_scene,std::string p_name):scene(p_scene),parent(nullptr),name(p_name),childs(){

	}
	inline Object(Object * p_parent,std::string p_name):scene(p_parent->scene),parent(p_parent),name(p_name),childs(){

	}

public:
		virtual ~Object();

		std::vector<Object *> getChilds();

		uint_fast32_t addChild(std::string name);
		void removeChild(std::string name);
		void removeChild(uint_fast32_t);
		void removeChild(Object * pointer);



		// std::vector<IObject *> getExtensions();

		// IObject* extend(ISystem& system);
		// void reduce(IObject* extension);

		void tick();
		void postData(BaseTypes::Data *data);

		private:

		// std::vector<IObject *> Extensions;

		Scene  *scene ;
		Object *parent;
		std::string name;
		boost::lockfree::queue<void*> DataUpdateQue;
		std::vector<Object *> childs;
	};


class Scene{
	public:
		Scene();
		virtual ~Scene();


		std::vector<Object *> getObjects() ;

		uint_fast32_t addObject(std::string name);
		void removeObject(std::string name);
		void removeObject(Object * pointer);


		std::vector<IScene *> getExtensions();

		IScene * extend(uint16_t SystemID);
		void	 reduce(uint16_t SystemID);

		void tick();
		void postData(BaseTypes::Data *data);


	private:
		std::vector<IScene*> Extensions;
		boost::lockfree::queue<void*> DataUpdateQue;
		std::vector<Object *> Objects;
		uint64_t **ObservingData;	//TODO ObjectOrientiert
	};

}



#endif /* UNIVERSAL_HPP_ */
