#pragma once
#include "Animation.h"
#include "IMoveable.h"
#include <map>

class AnimationManager {
private:
	
public:
	std::map<IMoveable::State, Animation> animations;
	AnimationManager();
	Animation get(IMoveable::State state);
	void add(IMoveable::State state, const std::string path, int frame_count);
};
