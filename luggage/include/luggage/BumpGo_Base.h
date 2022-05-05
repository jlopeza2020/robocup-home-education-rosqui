// Copyright 2022 Intelligent Robotics Lab
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

#ifndef luggage_BUMPGO_BASE_H
#define luggage_BUMPGO_BASE_H

#include "ros/ros.h"

#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

namespace luggage
{

class BumpGo_Base
{
public:
  BumpGo_Base(): detected_(false), state_(GOING_FORWARD) {};

  virtual bool scan() = 0;

protected:
  ros::NodeHandle n_;

  static const int GOING_FORWARD = 0;
  static const int GOING_BACK = 1;
  static const int TURNING_LEFT = 2;
  static const int TURNING_RIGHT = 3;

  static constexpr double FORWARD_VEL = 0.2;
  static constexpr double TURNING_VEL_LEFT = 0.3;
  static constexpr double TURNING_VEL_RIGHT = -0.3;
  static constexpr double BACK_VEL = -0.15;

  static constexpr double TURNING_TIME = 5.0;
  static constexpr double BACKING_TIME = 3.0;

  static const int DETECTED_LEFT = 0;
  static const int DETECTED_FRONT = 1;
  static const int DETECTED_RIGHT = 2;

  int state_;

  bool detected_;

  int direction_;

  ros::Time detected_ts_;
  ros::Time turn_ts_;

  ros::Subscriber sub_bumber_;
  ros::Subscriber sub_laser_scan_;
  ros::Publisher pub_vel_;
};

}  // namespace luggage

#endif  // luggage_BUMPGO_BASE_H