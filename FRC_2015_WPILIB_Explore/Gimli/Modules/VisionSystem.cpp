#include "VisionSystem.h"

VisionSystem::VisionSystem(){
	camera = &(AxisCamera::GetInstance("10.2.63.11"));
	dash = new DashboardConnecter();
}

VisionSystem::~VisionSystem(){
	delete dash;
	delete camera;
}
void VisionSystem::RunVision(){
	std::string tempDashString;
	std::stringstream s_data;
	
	TargetReport target;
	Threshold threshold(105, 137, 230, 255, 133, 183);
	ParticleFilterCriteria2 criteria[] = {
			{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}
	};	
	ColorImage* image = camera->GetImage();
	BinaryImage *thresholdImage = image->ThresholdHSV(threshold);
	BinaryImage *filteredImage = thresholdImage->ConvexHull(true);
	filteredImage->ParticleFilter(criteria, 1);
	filteredImage->RemoveSmallObjects(true, 5);
	vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();

	verticalTargetCount = horizontalTargetCount = 0;
	//Iterate through each particle, scoring it and determining whether it is a target or not
	if(reports->size() > 0)
	{
		scores = new Scores[reports->size()];
		for (unsigned int i = 0; i < MAX_PARTICLES && i < reports->size(); i++) {
			ParticleAnalysisReport *report = &(reports->at(i));
			//Score each particle on rectangularity and aspect ratio
			scores[i].rectangularity = ScoreRectangularity(report);
			scores[i].aspectRatioVertical = ScoreAspectRatio(filteredImage, report, true);
			scores[i].aspectRatioHorizontal = ScoreAspectRatio(filteredImage, report, false);			

			//Check if the particle is a horizontal target, if not, check if it's a vertical target
			if(ScoreCompare(scores[i], false))
			{
				printf("particle: %d  is a Horizontal Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
				horizontalTargets[horizontalTargetCount++] = i; //Add particle to target array and increment count
			} else if (ScoreCompare(scores[i], true)) {
				printf("particle: %d  is a Vertical Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
				verticalTargets[verticalTargetCount++] = i;  //Add particle to target array and increment count
			} else {
				printf("particle: %d  is not a Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
			}
			printf("Scores rect: %f  ARvert: %f \n", scores[i].rectangularity, scores[i].aspectRatioVertical);
			printf("ARhoriz: %f  \n", scores[i].aspectRatioHorizontal);	
		}

		//Zero out scores and set verticalIndex to first target in case there are no horizontal targets
		target.totalScore = target.leftScore = target.rightScore = target.tapeWidthScore = target.verticalScore = 0;
		target.verticalIndex = verticalTargets[0];
		for (int i = 0; i < verticalTargetCount; i++)
		{
			ParticleAnalysisReport *verticalReport = &(reports->at(verticalTargets[i]));
			for (int j = 0; j < horizontalTargetCount; j++)
			{
				ParticleAnalysisReport *horizontalReport = &(reports->at(horizontalTargets[j]));
				double horizWidth, horizHeight, vertWidth, leftScore, rightScore, tapeWidthScore, verticalScore, total;

				//Measure equivalent rectangle sides for use in score calculation
				imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizWidth);
				imaqMeasureParticle(filteredImage->GetImaqImage(), verticalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &vertWidth);
				imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizHeight);

				//Determine if the horizontal target is in the expected location to the left of the vertical target
				leftScore = RatioToScore(1.2*(verticalReport->boundingRect.left - horizontalReport->center_mass_x)/horizWidth);
				//Determine if the horizontal target is in the expected location to the right of the  vertical target
				rightScore = RatioToScore(1.2*(horizontalReport->center_mass_x - verticalReport->boundingRect.left - verticalReport->boundingRect.width)/horizWidth);
				//Determine if the width of the tape on the two targets appears to be the same
				tapeWidthScore = RatioToScore(vertWidth/horizHeight);
				//Determine if the vertical location of the horizontal target appears to be correct
				verticalScore = RatioToScore(1-(verticalReport->boundingRect.top - horizontalReport->center_mass_y)/(4*horizHeight));
				total = leftScore > rightScore ? leftScore:rightScore;
				total += tapeWidthScore + verticalScore;

				//If the target is the best detected so far store the information about it
				if(total > target.totalScore)
				{
					target.horizontalIndex = horizontalTargets[j];
					target.verticalIndex = verticalTargets[i];
					target.totalScore = total;
					target.leftScore = leftScore;
					target.rightScore = rightScore;
					target.tapeWidthScore = tapeWidthScore;
					target.verticalScore = verticalScore;
				}
			}
			//Determine if the best target is a Hot target
			target.Hot = HotOrNot(target);
		}

		if(verticalTargetCount > 0)
		{
			//Information about the target is contained in the "target" structure
			//To get measurement information such as sizes or locations use the
			//horizontal or vertical index to get the particle report as shown below
			ParticleAnalysisReport *distanceReport = &(reports->at(target.verticalIndex));
			distance = ComputeDistance(filteredImage, distanceReport);
			if(target.Hot)
			{
				GoalHot = true;
				printf("Hot target located \n");
				printf("Distance: %f \n", distance);
			} 
			else {
				GoalHot = false;
				printf("No hot target present \n");
				printf("Distance: %f \n", distance);
			}
		}
	}
	
	delete filteredImage;
	delete thresholdImage;
	delete image;
	delete scores;
	delete reports;
}

double VisionSystem::ComputeDistance (BinaryImage *image, ParticleAnalysisReport *report) {
	double rectLong, height;
	int targetHeight;

	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	//using the smaller of the estimated rectangle long side and the bounding rectangle height results in better performance
	//on skewed rectangles
	height = min(report->boundingRect.height, rectLong);
	targetHeight = 32;

	return Y_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(VIEW_ANGLE*PI/(180*2)));
}

double VisionSystem::ScoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool vertical){
	double rectLong, rectShort, idealAspectRatio, aspectRatio;
	idealAspectRatio = vertical ? (4.0/32) : (23.5/4);	//Vertical reflector 4" wide x 32" tall, horizontal 23.5" wide x 4" tall

	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);

	//Divide width by height to measure aspect ratio
	if(report->boundingRect.width > report->boundingRect.height){
		//particle is wider than it is tall, divide long by short
		aspectRatio = RatioToScore(((rectLong/rectShort)/idealAspectRatio));
	} else {
		//particle is taller than it is wide, divide short by long
		aspectRatio = RatioToScore(((rectShort/rectLong)/idealAspectRatio));
	}
	return aspectRatio;		//force to be in range 0-100
}
double VisionSystem::RatioToScore(double ratio){
	return (max(0, min(100*(1-fabs(1-ratio)), 100)));
}

double VisionSystem::ScoreRectangularity(ParticleAnalysisReport *report){
	if(report->boundingRect.width*report->boundingRect.height !=0){
		return 100*report->particleArea/(report->boundingRect.width*report->boundingRect.height);
	} else {
		return 0;
	}	
}	
bool VisionSystem::HotOrNot(TargetReport target)
{
	bool isHot = true;

	isHot &= target.tapeWidthScore >= TAPE_WIDTH_LIMIT;
	isHot &= target.verticalScore >= VERTICAL_SCORE_LIMIT;
	isHot &= (target.leftScore > LR_SCORE_LIMIT) | (target.rightScore > LR_SCORE_LIMIT);

	return isHot;
}

bool VisionSystem::ScoreCompare(Scores scores, bool vertical){
	bool isTarget = true;

	isTarget &= scores.rectangularity > RECTANGULARITY_LIMIT;
	if(vertical){
		isTarget &= scores.aspectRatioVertical > ASPECT_RATIO_LIMIT;
	} else {
		isTarget &= scores.aspectRatioHorizontal > ASPECT_RATIO_LIMIT;
	}

	return isTarget;
}
