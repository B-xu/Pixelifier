
#include "stats.h"

stats::stats(PNG & im){
	int x = im.width();
	int y = im.height();
	sumHueX.resize(x, vector<double>(y));
	sumHueY.resize(x, vector<double>(y));
	sumSat.resize(x, vector<double>(y));
	sumLum.resize(x, vector<double>(y));
	hist.resize(x, vector<vector<int>>(y, vector<int>(36)));

	for (int x = 0; x < im.width(); x++) {
		for (int y = 0; y < im.height(); y++) {
			int bucket = im.getPixel(x, y)->h / 10;
			if (x == 0 && y == 0) {
				sumHueX[x][y] = cos(im.getPixel(x, y)->h*PI / 180);
				sumHueY[x][y] = sin(im.getPixel(x, y)->h*PI / 180);
				sumSat[x][y] = im.getPixel(x, y)->s;
				sumLum[x][y] = im.getPixel(x, y)->l;
				hist[x][y][bucket] = 1;
			}
			else if (x == 0) {
				sumHueX[x][y] = cos(im.getPixel(x, y)->h*PI / 180) + sumHueX[x][y - 1];
				sumHueY[x][y] = sin(im.getPixel(x, y)->h*PI / 180) + sumHueY[x][y - 1];
				sumSat[x][y] = im.getPixel(x, y)->s + sumSat[x][y - 1];
				sumLum[x][y] = im.getPixel(x, y)->l + sumLum[x][y - 1];
				for (int h = 0; h < 36; h++) {
					hist[x][y][h] = hist[x][y - 1][h];
					if (h == bucket) {
						hist[x][y][h]++;
					}
				}
			}
			else if (y == 0) {
				sumHueX[x][y] = cos(im.getPixel(x, y)->h*PI / 180) + sumHueX[x - 1][y];
				sumHueY[x][y] = sin(im.getPixel(x, y)->h*PI / 180) + sumHueY[x - 1][y];
				sumSat[x][y] = im.getPixel(x, y)->s + sumSat[x - 1][y];
				sumLum[x][y] = im.getPixel(x, y)->l + sumLum[x - 1][y];
				for (int h = 0; h < 36; h++) {
					hist[x][y][h] = hist[x - 1][y][h];
					if (h == bucket) {
						hist[x][y][h]++;
					}
				}
			}
			else {
				sumHueX[x][y] = cos(im.getPixel(x, y)->h*PI / 180) + sumHueX[x - 1][y] + sumHueX[x][y - 1] - sumHueX[x - 1][y - 1];
				sumHueY[x][y] = sin(im.getPixel(x, y)->h*PI / 180) + sumHueY[x - 1][y] + sumHueY[x][y - 1] - sumHueY[x - 1][y - 1];
				sumSat[x][y] = im.getPixel(x, y)->s + sumSat[x - 1][y] + sumSat[x][y - 1] - sumSat[x - 1][y - 1];
				sumLum[x][y] = im.getPixel(x, y)->l + sumLum[x - 1][y] + sumLum[x][y - 1] - sumLum[x - 1][y - 1];
				for (int h = 0; h < 36; h++) {
					hist[x][y][h] = hist[x - 1][y][h] + hist[x][y - 1][h] - hist[x - 1][y - 1][h];
					if (h == bucket) {
						hist[x][y][h]++;
					}
				}
			}


		}
	}
	
}

void stats::setupSumHuex(PNG & im) {
	for (int x = 0; x < im.width(); x++) {
		for (int y = 0; y < im.height(); y++) {int bucket = im.getPixel(x, y)->h / 10;
			if (x == 0 && y == 0) {
				sumHueX[x][y] = cos(im.getPixel(x, y)->h*PI/180);
				
			}
			else if (x == 0) {
				sumHueX[x][y] = cos(im.getPixel(x, y)->h*PI / 180) + sumHueX[x][ y - 1];
				
			}
			else if (y == 0) {
				sumHueX[x][y] = cos(im.getPixel(x, y)->h*PI / 180) + sumHueX[x - 1][ y];
			}
			else {
				sumHueX[x][y] = cos(im.getPixel(x, y)->h*PI / 180) + sumHueX[x - 1][ y] + sumHueX[x][ y - 1] - sumHueX[x - 1] [y - 1];
			}
		}
	}
}

void stats::setupSumHuey(PNG & im) {
	for (int x = 0; x < im.width(); x++) {
		for (int y = 0; y < im.height(); y++) {
			if (x == 0 && y == 0) {
				sumHueY[x][y] = sin(im.getPixel(x, y)->h*PI / 180);
			}
			else if (x == 0) {
				sumHueY[x][y] = sin(im.getPixel(x, y)->h*PI / 180) + sumHueY[x][ y - 1];
			}
			else if (y == 0) {
				sumHueY[x][y] = sin(im.getPixel(x, y)->h*PI / 180) + sumHueY[x - 1][ y];
			}
			else {
				sumHueY[x][y] = sin(im.getPixel(x, y)->h*PI / 180) + sumHueY[x - 1][ y] + sumHueY[x][ y - 1] - sumHueY[x - 1][ y - 1];
			}
		}
	}
}

void stats::setupSumSat(PNG & im) {
	for (int x = 0; x < im.width(); x++) {
		for (int y = 0; y < im.height(); y++) {
			if (x == 0 && y == 0) {
				sumSat[x][y] = im.getPixel(x, y)->s;
			}
			else if (x == 0) {
				sumSat[x][y] = im.getPixel(x, y)->s + sumSat[x][ y - 1];
			}
			else if (y == 0) {
				sumSat[x][y] = im.getPixel(x, y)->s + sumSat[x - 1][ y];
			}
			else {
				sumSat[x][y] = im.getPixel(x, y)->s + sumSat[x - 1][ y] + sumSat[x][ y - 1] - sumSat[x - 1][ y - 1];
			}
		}
	}
}

void stats::setupSumLum(PNG & im) {
	for (int x = 0; x < im.width(); x++) {
		for (int y = 0; y < im.height(); y++) {
			if (x == 0 && y == 0) {
				sumLum[x][y] = im.getPixel(x, y)->l;
			}
			else if (x == 0) {
				sumLum[x][y] = im.getPixel(x, y)->l + sumLum[x][ y - 1];
			}
			else if (y == 0) {
				sumLum[x][y] = im.getPixel(x, y)->l+ sumLum[x - 1][ y];
			}
			else {
				sumLum[x][y] = im.getPixel(x, y)->l + sumLum[x - 1][ y] + sumLum[x][ y - 1] - sumLum[x - 1][ y - 1];
			}
		}
	}
}

void stats::setupHist(PNG & im) {
	for (int x = 0; x < im.width(); x++) {
		for (int y = 0; y < im.height(); y++) {
			int bucket = im.getPixel(x, y)->h / 10;
			putintobuckets(im, x, y, bucket);
		}
	}
}

void stats::putintobuckets(PNG &im, int x, int y, int bucket) {
	for (int i = 0; i < im.width(); i++) {
		for (int j = 0; j < im.height(); j++) {
			if (j >= y && i>=x ) {
				hist[i][j][bucket]++;
				//cout << "row: " << i << " column " << j << " histogram bucket "<<bucket<< " incremented to " <<hist[i][j][bucket] << endl;
			}
		}
	}
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
	return (lr.second-ul.second+1) * (lr.first-ul.first+1);
}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
	// compute sums
	double totHuex, totHuey, totSat, totLum;
	if (ul.first == 0 && ul.second == 0) {
		totHuex = sumHueX[lr.first][lr.second];
		totHuey = sumHueY[lr.first][lr.second];
		totSat = sumSat[lr.first][lr.second];
		totLum = sumLum[lr.first][lr.second];
	}
	else if (ul.second == 0) {
		totHuex = sumHueX[lr.first][lr.second]-sumHueX[ul.first-1][lr.second];
		totHuey = sumHueY[lr.first][lr.second] - sumHueY[ul.first - 1][lr.second];
		totSat = sumSat[lr.first][lr.second] - sumSat[ul.first - 1][lr.second];
		totLum = sumLum[lr.first][lr.second] - sumLum[ul.first - 1][lr.second];
	}
	else if (ul.first == 0) {
		totHuex = sumHueX[lr.first][lr.second] - sumHueX[lr.first][ul.second-1];
		totHuey = sumHueY[lr.first][lr.second] - sumHueY[lr.first][ul.second - 1];
		totSat = sumSat[lr.first][lr.second] - sumSat[lr.first][ul.second - 1];
		totLum = sumLum[lr.first][lr.second] - sumLum[lr.first][ul.second - 1];
	}
	else {
		totHuex = sumHueX[lr.first][lr.second] - sumHueX[ul.first - 1][lr.second] - sumHueX[lr.first][ul.second - 1] + sumHueX[ul.first - 1][ul.second - 1];
		totHuey = sumHueY[lr.first][lr.second] - sumHueY[ul.first - 1][lr.second] - sumHueY[lr.first][ul.second - 1] + sumHueY[ul.first - 1][ul.second - 1];
		totSat = sumSat[lr.first][lr.second] - sumSat[ul.first - 1][lr.second] - sumSat[lr.first][ul.second - 1] + sumSat[ul.first - 1][ul.second - 1];
		totLum = sumLum[lr.first][lr.second] - sumLum[ul.first - 1][lr.second] - sumLum[lr.first][ul.second - 1] + sumLum[ul.first - 1][ul.second - 1];
	}
	// compute average huex
	
	double avgHuex = totHuex / rectArea(ul, lr);
	
	// compute average huey
	
	double avgHuey = totHuey / rectArea(ul, lr);

	// compute average hue
	double avgHue = atan2(avgHuey, avgHuex) * 180 / PI;
	while (avgHue < 0) {
		avgHue += 360;
	}
	
	// compute average saturation
	
	double avgSat = totSat / rectArea(ul, lr);

	// compute average luminosity
	
	double avgLum = totLum / rectArea(ul, lr);

	return HSLAPixel(avgHue, avgSat, avgLum, 1.0);
}

vector<int> stats::buildHist(pair<int,int> ul, pair<int,int> lr){
	vector<int> storer, smaller, smallest, adder;
	vector<int> bigger= hist[lr.first][lr.second];
	smaller.assign(36, 0);
	smallest.assign(36, 0);
	adder.assign(36, 0);
	if (ul.first == 0 && ul.second == 0) {
	}
	else if (ul.second == 0) {
		smaller = hist[ul.first-1][lr.second];
	}
	else if (ul.first == 0) {
		smaller = hist[lr.first][ul.second-1];
	}
	else {
		smaller =hist[ul.first-1][lr.second];
		smallest = hist[lr.first][ul.second - 1];
		adder = hist[ul.first - 1][ul.second - 1];
	}


	storer.resize(36);
	
	for (int i = 0; i < bigger.size(); i++) {
		int holder = bigger[i] - smaller[i]-smallest[i]+adder[i];
		while (holder < 0) {
			holder += 360;
		}
		storer[i] = holder;
	}

	return storer;
}

// takes a distribution and returns entropy
// partially implemented so as to avoid rounding issues.
double stats::entropy(vector<int> & distn,int area){

    double entropy = 0.0;


    for (int i = 0; i < 36; i++) {
        if (distn[i] > 0 ) 
            entropy += ((double) distn[i]/(double) area) 
                                    * log2((double) distn[i]/(double) area);
    }

    return  -1 * entropy;

}

double stats::entropy(pair<int,int> ul, pair<int,int> lr){
	vector<int> values = buildHist(ul, lr);
	/*
	for (int i = 0; i < values.size(); i++) {
		cout << values[i] << endl;
	}
	*/
	int area = rectArea(ul, lr);
	return stats::entropy(values, area);

}
