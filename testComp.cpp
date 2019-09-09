#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "stats.h"
#include "toqutree.h"

using namespace std;
using namespace cs221util;

/*
TEST_CASE("stats::basic rectArea","[weight=1][part=stats]"){
                                                                    
    PNG data; data.resize(2,2);

    stats s(data);
    pair<int,int> ul(0,0);
    pair<int,int> lr(1,1);
    long result = s.rectArea(ul,lr);

    REQUIRE(result == 4);
    
}



TEST_CASE("stats::basic getAvg","[weight=1][part=stats]"){
    PNG data; data.resize(2,2);
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j++){
            HSLAPixel * p = data.getPixel(i,j);
            p->h = 135*j + i * 90;
            p->s = 1.0;
            p->l = 0.5;
            p->a = 1.0;
        }
    }
    stats s(data);
    pair<int,int> ul(0,0);
    pair<int,int> lr(1,1);
    HSLAPixel result = s.getAvg(ul,lr);
    HSLAPixel expected(112.5,1.0, 0.5);

    REQUIRE(result == expected);
}




TEST_CASE("stats::advanced getAvg", "[weight=1][part=stats]") {
	PNG data; data.resize(4, 4);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			HSLAPixel * p = data.getPixel(i, j);
			p->h = 135 * j + i * 90;
			p->s = 1.0;
			p->l = 0.5;
			p->a = 1.0;
		}
	}
	stats s(data);
	pair<int, int> ul(0, 1);
	pair<int, int> lr(3, 3);

	HSLAPixel result = s.getAvg(ul, lr);
	HSLAPixel expected(112.5, 1.0, 0.5);

	pair<int, int> ul1(1, 0);
	HSLAPixel result1 = s.getAvg(ul1, lr);	

	pair<int, int> ul2(1, 1);
	HSLAPixel result2 = s.getAvg(ul2, lr);

	REQUIRE(result == expected);
	REQUIRE(result1 == expected); 
	REQUIRE(result2 == expected);
}


TEST_CASE("stats::basic entropy","[weight=1][part=stats]"){     
    PNG data; data.resize(2,2);
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j++){
            HSLAPixel * p = data.getPixel(i,j);
            p->h = 135*j + i * 90;
            p->s = 1.0;
            p->l = 0.5;
            p->a = 1.0;
        }
    }
    stats s(data);
    pair<int,int> ul(0,0);
    pair<int,int> lr(1,1);
    long result = s.entropy(ul,lr);

    REQUIRE(result == 2);
}

TEST_CASE("stats::adv entropy", "[weight=1][part=stats]") {
	PNG data; data.resize(6, 6);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			HSLAPixel * p = data.getPixel(i, j);
			p->h = 10*i;
			p->s = 1.0;
			p->l = 0.5;
			p->a = 1.0;
		}
	}
	stats s(data);
	pair<int, int> ul(2, 1);
	pair<int, int> lr(5, 5);
	long result = s.entropy(ul, lr);

	REQUIRE(result == 2);
}
*/

/*
TEST_CASE("toqutree::basic ctor render","[weight=1][part=toqutree]"){
    PNG img;
    img.readFromFile("images/ada.png");

    toqutree t1(img,9);
	cout << "Good so far" << endl;

    PNG out = t1.render();
    out.convert();
	out.writeToFile("images/ada-sw.png");

    REQUIRE(out==img);
}
*/



/*
TEST_CASE("toqutree::basic copy","[weight=1][part=toqutree]"){
    PNG img;
    img.readFromFile("images/geo.png");

    toqutree t1(img,5);
    toqutree t1copy(t1);

    PNG out = t1copy.render();

    REQUIRE(out==img);
}
*/


TEST_CASE("toqutree::basic prune","[weight=1][part=toqutree]"){
    PNG img;
    img.readFromFile("images/oneSmall.png");
    
    toqutree t1(img,3);

    t1.prune(0.1);
    PNG result = t1.render();
    PNG expected; expected.readFromFile("images/oneSmall.png");
    result.convert();

	result.writeToFile("images/onePruned.png");
    REQUIRE(expected==result);
}




