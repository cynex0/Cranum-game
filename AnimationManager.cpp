#include "AnimationManager.h"

AnimationManager::AnimationManager() { }

Animation AnimationManager::get(IMoveable::State state) {
	return this->animations[state];
}

void AnimationManager::add(IMoveable::State state, const std::string path, int frame_count) {
	Animation animation;
	animation.fromDir(path, frame_count);
	animations[state] = animation;
}
