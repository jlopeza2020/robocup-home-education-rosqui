// Copyright 2022 ROSqui
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>

#include "luggage/GoToRef.h"
#include "luggage/Dialog.h"
#include "nav_node.cpp"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "move_base_msgs/MoveBaseActionResult.h"

#include "ros/ros.h"


namespace luggage
{

GoToRef::GoToRef(const std::string& name)
: BT::ActionNodeBase(name, {}),
  nh_()
{
    
  ROS_INFO("CONSTRUCTOR GoToRef");
  result_sub_ = nh_.subscribe("/move_base/result", 1, &GoToRef::ResultCallback, this);
  result_ = 0;
  coords_[0] = 2.0;
}

void
GoToRef::halt()
{
  ROS_INFO("GoToRef halt");
}

void
GoToRef::ResultCallback(const move_base_msgs::MoveBaseActionResult::ConstPtr& msg)
{
	result_ = msg->status.status;
}

BT::NodeStatus
GoToRef::tick()

{
	ROS_INFO("GoToRef");

	luggage::Dialog forwarder;
	ros::Duration(1, 0).sleep();
	dialogflow_ros_msgs::DialogflowResult side;
	int controler = 1;

	while (controler) {
		ROS_INFO("bucle");
		forwarder.listen(); 
		ros::spinOnce();
		if (forwarder.get_start() == 0)
			controler = 0;
		ros::Duration(2, 0).sleep();
	}

	ROS_INFO("NAV START");
	MyNode my_node;
	my_node.doWork(200, coords_);

	if (result_ == 3)
	{
		ROS_INFO("LEAVING");
		return BT::NodeStatus::SUCCESS;
	}

  	return BT::NodeStatus::RUNNING;
}
}  // namespace luggage

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<luggage::GoToRef>("GoToRef");
}