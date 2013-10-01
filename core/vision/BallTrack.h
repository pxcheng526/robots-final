#ifndef BALLTRACK_H
#define BALLTRACK_H

#include <common/WorldObject.h>
#include <vision/CameraMatrix.h>

#include <Eigen/Core>

/*
 * uses notation from http://robots.stanford.edu/probabilistic-robotics/ppt/kalman.ppt
 */
class BallTracker {
public:
	BallTracker() :
			seen(false) {

		for (int i = 0; i != 4; ++i) {
			for (int j = 0; j != 4; ++j) {
				A(i, j) = 0.0;
			}
		}
		for (int i = 0; i != 4; ++i) {
			A(i, i) = 1.0;
		}
		A(0, 2) = 1.0;
		A(1, 3) = 1.0;

		for (int i = 0; i != 4; ++i) {
			for (int j = 0; j != 4; ++j) {
				cov(i, j) = 0.0;
				R(i, j) = 0.0;
			}
		}
		cov(0, 0) = 10000.0;
		cov(1, 1) = 10000.0;
		cov(2, 2) = 20000.0;
		cov(3, 3) = 20000.0;

		/*
		 * if need less smoother
		 * and follow closer
		 * increase R
		 */
		R(0, 0) = 900.0;
		R(1, 1) = 900.0;
		R(2, 2) = 1800.0;
		R(3, 3) = 1800.0;

		/*
		 * measured Q
		 *
		 *       [,1]      [,2]      [,3]      [,4]
		 * [1,]  8445.970  5126.731 -6635.046 -4263.411
		 * [2,]  5126.731  3143.634 -4144.081 -2683.283
		 * [3,] -6635.046 -4144.081 14479.766  9164.049
		 * [4,] -4263.411 -2683.283  9164.049  5836.146
		 *
		 */

		Q << 8445.970, 5126.731, 5126.731, 3143.634;

		C << 1, 0, 0, 0, 0, 1, 0, 0;
	}

	~BallTracker() {
	}

	/*
	 * x
	 * y
	 * v_x
	 * v_y
	 */
	Eigen::Vector4f state;

	Eigen::Matrix4f cov;

	void initState(float x, float y, float v_x, float v_y);

	/* called in the top camera */
	void track(WorldObject* ball, CameraMatrix &cmatrix_);

private:

	Eigen::Matrix4f R;

	Eigen::Matrix2f Q;

	Eigen::Matrix4f A;

	Eigen::Matrix<float, 2, 4> C;

	bool seen;

	/*
	 * The model:
	 *
	 * X = [ position \\
		 * 		 velocity ]
	 *
	 * X_{n+1} = ( 1 delta_T \\ X_n
	 *             0       1 )
	 */
	void updateState(float x, float y); /* observed values */

};

#endif /* BALLTRACK_H */
