#include "../Data/Data.hpp"

int main(){
	Data::Universal::Node &topNode = Data::getTopNode();
	topNode.access().addChild();
	Data::ThreadID = 1;
	topNode.access().addChild();
	topNode.access().syncAll();
	Data::ThreadID = 0;
	topNode.access().syncAll();
	topNode.access().getChild(1);
	return 0;
}
