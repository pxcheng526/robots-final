#include "BallDetector.h"

using namespace Eigen;

#define getball() (&vblocks_.world_object->objects_[WO_BALL])
#define getself() (&vblocks_.world_object->objects_[vblocks_.robot_state->WO_SELF])
#define getframe() vblocks_.frame_info->frame_id

BallDetector::BallDetector(DETECTOR_DECLARE_ARGS, Classifier*& classifier,
		BlobDetector*& blob_detector) :
		DETECTOR_INITIALIZE, classifier_(classifier), blob_detector_(
				blob_detector) {
	candidateCount = 0;
}

void BallDetector::detectBall() {
	WorldObject* ball = &vblocks_.world_object->objects_[WO_BALL];
	ball->seen = false;

	for (int i = 0; i != iparams_.width; ++i) {
		for (int j = 0; j != iparams_.height; ++j) {
			if (getSegPixelValueAt(i,j) == c_ORANGE) {
				ball->seen = true;
			}
		}
	}
}
