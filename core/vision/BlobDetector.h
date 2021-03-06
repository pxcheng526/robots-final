#ifndef BLOBDETECTOR_H
#define BLOBDETECTOR_H

#include <memory/TextLogger.h>
#include <constants/VisionConstants.h>
#include <vision/Classifier.h>
#include <vision/structures/Blob.h>
#include <vision/structures/VisionParams.h>
#include <vision/Macros.h>
#include <vision/ObjectDetector.h>

#include <vision/enums/Colors.h>

typedef std::vector<Blob> BlobCollection;

class BlobDetector: public ObjectDetector {
public:
	BlobDetector(DETECTOR_DECLARE_ARGS, Classifier*& classifier);
	void init(TextLogger* tl) {
		textlogger = tl;
	}
	;
	std::vector<BlobCollection> horizontalBlob, verticalBlob;
	void formWhiteLineBlobs();
	void formBlobs(Color color);

private:
	Classifier*& classifier_;
	VisionPoint ***verticalPoint, ***horizontalPoint;
	uint32_t **verticalPointCount, **horizontalPointCount;
	TextLogger* textlogger;
};

#endif
