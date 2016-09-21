#include "../Execution/TaskManager.hpp"
#include <unistd.h>
int main(){
	Execution::TaskManager::primaryAktive = false;
	Execution::Task newTestChildrenTask0 = Execution::Task();
	newTestChildrenTask0.priority = 2;
	newTestChildrenTask0.function = newTestChildren0;
	Execution::TaskManager::queueTask(newTestChildrenTask0);
	Execution::Task newTestChildrenTask1 = Execution::Task();
	newTestChildrenTask1.priority = 2;
	newTestChildrenTask1.function = newTestChildren1;
	newTestChildrenTask1.addDependency(newTestChildrenTask0);
	Execution::Task moveTestChildrenTask2 = Execution::Task();
	moveTestChildrenTask2.priority = 2;
	moveTestChildrenTask2.function = moveTestChildren2;
	newTestChildrenTask1.addDependency(newTestChildrenTask1);
	Execution::Task newTestChildrenTask1 = Execution::Task();
	newTestChildrenTask1.priority = 2;
	newTestChildrenTask1.function = newTestChildren1;
	newTestChildrenTask1.addDependency(newTestChildrenTask0);
	Execution::TaskManager::start();
	return 0;
}
Data::Universal::Node& n00,n000,n001,n0000,n0001,n0010,n0011;
void newTestChildren0(){
	Data::Universal::Node topNode = Data::getTopNode();
	n00 = topNode.access().addChild();
	n001 = n00.access().addChild();
	Execution::Task newTestChildrenTask2 = Execution::Task();
	newTestChildrenTask2.priority = 2;
	newTestChildrenTask2.function = newTestChildren2;
	Execution::Task moveTestChildrenTask1 = Execution::Task();
	moveTestChildrenTask1.priority = 2;
	moveTestChildrenTask1.function = moveTestChildrenTask1;
	moveTestChildrenTask1.addDependency(moveTestChildrenTask1);
	Execution::TaskManager::queueTask(newTestChildrenTask2);
	n000 = n00.access().addChild();

}
void newTestChildren1(){
	n0000 = n000.access().addChild();
	n0001 = n000.access().addChild();

}
void newTestChildren2(){
	n0010 = n001.access().addChild();
	n0011 = n001.access().addChild();
}
void moveTestChildren1(){
	n0010.access().move(n000);
	n0011.access().move(n000);
}
void moveTestChildren2(){
	n0000.access().move(n001);
	n0001.access().move(n001);
}
void verif(){
	std::cout<<n000.access().getID()<<std::endl;
	std::cout<<n001.access().getID()<<std::endl;
	std::cout<<n0010.access().getParent()->access().getID()<<std::endl;
	std::cout<<n0000.access().getParent()->access().getID()<<std::endl;
	Execution::TaskManager::shutdown();
}
