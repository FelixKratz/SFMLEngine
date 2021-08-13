//
//  UpdatePipeline.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include "Pipeline.hpp"

// All objects that need to be updated should inherit from this class
// Dummy Class at the moment
class UpdateProcessor : public PipelineProcessor<int> {};

// The UpdatePipeline can be used to group the update event for many UpdateProcessors
// Dummy Class at the moment
class UpdatePipeline : public Pipeline<UpdateProcessor> {};
