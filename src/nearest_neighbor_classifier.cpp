// Copyright (c) 2012, 2019 Scott Niekum, Joshua Whitley
// All rights reserved.
// 
// Software License Agreement (BSD License 2.0)
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//  * Neither the name of {copyright_holder} nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "ml_classifiers/nearest_neighbor_classifier.hpp"
#include <pluginlib/class_list_macros.hpp>

#include <string>
#include <vector>
#include <cmath>

PLUGINLIB_EXPORT_CLASS(ml_classifiers::NearestNeighborClassifier, ml_classifiers::Classifier)

namespace ml_classifiers
{

NearestNeighborClassifier::NearestNeighborClassifier() {}

NearestNeighborClassifier::~NearestNeighborClassifier() {}

void NearestNeighborClassifier::save(const std::string filename) {}

bool NearestNeighborClassifier::load(const std::string filename)
{
  return false;
}

void NearestNeighborClassifier::addTrainingPoint(std::string target_class, const std::vector<double> point)
{
  class_data[target_class].push_back(point);
}

void NearestNeighborClassifier::train() {}

void NearestNeighborClassifier::clear()
{
  class_data.clear();
}

std::string NearestNeighborClassifier::classifyPoint(const std::vector<double> point)
{
  size_t dims = point.size();
  double min_diff = 0;
  std::string ans;
  bool first = true;

  for (ClassMap::iterator iter = class_data.begin(); iter != class_data.end(); iter++)
  {
    std::string cname = iter->first;
    CPointList cpl = iter->second;

    for (size_t i = 0; i < cpl.size(); i++)
    {
      double diff = 0;
      for (size_t j = 0; j < dims; j++)
      {
        diff += std::fabs(cpl[i][j] - point[j]);
      }
      if (first)
      {
        first = false;
        min_diff = diff;
        ans = cname;
      }
      else if (diff < min_diff)
      {
        min_diff = diff;
        ans = cname;
      }
    }
  }
  return ans;
}

}  // namespace ml_classifiers
