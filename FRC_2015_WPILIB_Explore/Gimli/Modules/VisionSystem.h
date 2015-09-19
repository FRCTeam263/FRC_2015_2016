#ifndef VISIONSYSTEM_H_
#define VISIONSYSTEM_H_

/*
#include "Vision/AxisCamera.h"
#include "Vision/ColorImage.h"
#include "Vision/Threshold.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
*/
#include "WPILib.h"
#include "Math.h"
#include "../Misc/DashboardConnecter.h"
#include "../Defines.h"
#include "Utilities.h"
#include "../Globals.h"

class VisionSystem{
public:
	VisionSystem(void);
	~VisionSystem(void);

	struct Scores {
		double rectangularity;
		double aspectRatioVertical;
		double aspectRatioHorizontal;
	};

	struct TargetReport {
		int verticalIndex;
		int horizontalIndex;
		bool Hot;
		double totalScore;
		double leftScore;
		double rightScore;
		double tapeWidthScore;
		double verticalScore;
	};
	Scores *scores;
	int verticalTargets[MAX_PARTICLES];
	int horizontalTargets[MAX_PARTICLES];
	int verticalTargetCount, horizontalTargetCount;
	bool GoalHot;
	
	void RunVision(void);
	double ComputeDistance(BinaryImage *image, ParticleAnalysisReport *report);
	double ScoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool vertical);
	double RatioToScore(double ratio);
	bool HotOrNot(TargetReport target);
	double ScoreRectangularity(ParticleAnalysisReport *report);
	bool ScoreCompare(Scores scores, bool vertical);
	float distance;
private:
	AxisCamera *camera;
	DashboardConnecter *dash;
	std::string s_Packet;
};

#endif
