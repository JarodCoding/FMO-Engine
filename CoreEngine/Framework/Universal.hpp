/*
 * Universal.hpp
 *	
 *  Created on: Sep 14, 2014
 *      Author: Pascal Kuthe
 */
#include "../BaseTypes/Data.hpp"
#include "list"
#include "boost/lockfree/queue.hpp"
#ifndef UNIVERSAL_HPP_
#define UNIVERSAL_HPP_

namespace Universal{
class Scene;


class Object{
	friend class Scene;
	protected:

	inline Object(Scene * p_scene,std::string p_name):scene(p_scene),parent(nullptr),name(p_name),DataUpdateQue(),childs(){

	}
	inline Object(Object * p_parent,std::string p_name):scene(p_parent->scene),parent(p_parent),name(p_name),DataUpdateQue(),childs(){

	}

public:
		virtual ~Object();

		std::vector<Object *> getChilds();

		Object * addChild(std::string name);
		void removeChild(std::string name);
		void removeChild(Object * pointer);



		// std::vector<IObject *> getExtensions();

		// IObject* extend(ISystem& system);
		// void reduce(IObject* extension);

		void tick();
		void postData(BaseTypes::Data data);

		private:

		// std::vector<IObject *> Extensions;

		Scene  *scene ;
		Object *parent;
		std::string name;
		std::list<boost::lockfree::queue<BaseTypes::Data>> DataUpdateQue;
		std::vector<Object *> childs;
	};


class Scene{
	public:
		Scene();
		virtual ~Scene();


		std::vector<Object *> getObjects() ;

		Object * addObject   (std::string name);
		void removeObject(std::string name);
		void removeObject(Object * pointer);


		// std::vector<IScene *> getExtensions( );

		// IScene * extend(ISystem& 	system);
		// void		reduce(IScene * extension );

		void tick();
		void postData(BaseTypes::Data data);


	private:
		// std::vector<IScene*> Extensions;
			std::vector<boost::lockfree::queue<BaseTypes::Data>> DataUpdateQue;

		std::vector<Object *> Objects;
	};

}



#endif /* UNIVERSAL_HPP_ */
