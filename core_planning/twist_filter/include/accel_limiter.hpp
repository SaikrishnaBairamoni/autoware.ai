#pragma once
/*
 * Copyright (C) 2018-2020 LEIDOS.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <autoware_msgs/ControlCommandStamped.h>
#include <hardcoded_params/control_limits/control_limits.h>

namespace twist_filter {

constexpr double MAX_LONGITUDINAL_ACCEL_HARDCODED_LIMIT_M_S_2 = hardcoded_params::control_limits::MAX_LONGITUDINAL_ACCEL_MPS2;

/**
 * \brief Class responsible for encapsulating the state related to acceleration
 * limiting of longitudinal speed commands. Keeps track of the previously received
 * message's speeds and times to compute acceleration against the new message's
 * value.
 */
class LongitudinalAccelLimiter 
{
    public:
        /**
         * Default constructor, not recommended for use.
         */
        LongitudinalAccelLimiter():
            _accel_limit(3.5),
            _initialized(false),
            _prev_v(0.0),
            _prev_t(0.0) {};

        /**
         * \brief Constructor for LongitudinalAccelLimiter
         * 
         * \param accel_limit The acceleration limit that should be enforced, in
         * units of m/s/s
         */
        LongitudinalAccelLimiter(double accel_limit):
            _accel_limit(accel_limit),
            _initialized(false),
            _prev_v(0.0),
            _prev_t(0.0) {};

        /**
         * Limit the longitudinal acceleration found in the input ControlCommandStamped
         * 
         * \param msg The message to be evaluated
         * \return A copy of the message with the longitudinal accel limited 
         * based on params or hardcoded limit
         */
        autoware_msgs::ControlCommandStamped
            longitudinalAccelLimitCtrl(const autoware_msgs::ControlCommandStamped& msg);

        /**
         * Limit the longitudinal acceleration found in the input TwistStamped
         * 
         * \param msg The message to be evaluated
         * \return A copy of the message with the longitudinal accel limited 
         * based on params or hardcoded limit
         */
        geometry_msgs::TwistStamped
            longitudinalAccelLimitTwist(const geometry_msgs::TwistStamped& msg);

    private:
        double _accel_limit;
        bool _initialized;
        double _prev_v;
        ros::Time _prev_t;
};

}