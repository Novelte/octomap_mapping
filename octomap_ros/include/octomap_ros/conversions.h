// $Id$

/**
 * OctoMap ROS integration
 *
 * @author A. Hornung, University of Freiburg, Copyright (C) 2011.
 * @see http://www.ros.org/wiki/octomap_ros
 * License: BSD
 */

/*
 * Copyright (c) 2010, A. Hornung, University of Freiburg
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of Freiburg nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef OCTOMAP_CONVERT_MSGS_H
#define OCTOMAP_CONVERT_MSGS_H

#include <octomap/octomap.h>
#include <octomap_ros/OctomapBinary.h>
#include <octomap_ros/OctomapBinaryWithPose.h>

namespace octomap {
  /**
   * Converts an octomap map structure to a ROS octomap msg as binary data
   *
   * @param octomap input OcTree
   * @param mapMsg output msg
   */
  static inline void octomapMapToMsg(const OcTree& octomap, octomap_ros::OctomapBinary& mapMsg){
    // conversion via stringstream

    // TODO: read directly into buffer? see
    // http://stackoverflow.com/questions/132358/how-to-read-file-content-into-istringstream
    std::stringstream datastream;
    octomap.writeBinaryConst(datastream);
    std::string datastring = datastream.str();
    mapMsg.header.stamp = ros::Time::now();
    mapMsg.data = std::vector<int8_t>(datastring.begin(), datastring.end());
  }

  /**
   * Converts a ROS octomap msg (binary data) to an octomap map structure
   *
   * @param mapMsg
   * @param octomap
   */
  static inline void octomapMsgToMap(const octomap_ros::OctomapBinary& mapMsg, octomap::OcTree& octomap){
    std::stringstream datastream;
    assert(mapMsg.data.size() > 0);
    datastream.write((const char*) &mapMsg.data[0], mapMsg.data.size());
    octomap.readBinary(datastream);
  }

  // TODO point3d_listToPCL

//  PointCloud MapNode::generatePointCloud() {
//    octomap::point3d_list node_centers;
//    node_map->getOccupiedGlobal(node_centers);
//    PointCloud cloud;
//    cloud.points.reserve(node_centers.size());
//    for (octomap::point3d_list::const_iterator it = node_centers.begin();
//         it != node_centers.end(); ++it) {
//      cloud.push_back(Point(it->x(), it->y(), it->z()));
//    }
//    return cloud;
//  }


}


#endif
