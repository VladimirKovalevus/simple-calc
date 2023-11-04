#include "controlnode.h"

ControlNode::ControlNode()
{

}



ControlNode& ControlNode::getControlNode(){

    static ControlNode instance;

    return instance;
}
