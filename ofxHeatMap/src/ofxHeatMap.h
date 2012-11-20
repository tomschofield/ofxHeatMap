//<ofxHeatMap an inverse distance weighting class for producing heatmps over randomly distrubuted data points.>
//Copyright (C) <2012>  <Tom Schofield>
//    
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//    
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>
//implements SHEPARD's METHOD for INVERSE DISTANCE WEIGHTING FOLLOWING FORMULA FOUND AT http://www.ems-i.com/smshelp/Data_Module/Interpolation/Inverse_Distance_Weighted.htm

#ifndef __ofxHeatMap__
#define __ofxHeatMap__

#include "ofMain.h"

using namespace std;
class ofxHeatMap{

	public:
        void setup();
        float getInterpValue(float x, float y, vector<float> xs, vector<float> ys, vector<float> f );

    protected:
        float getMaxDistanceFromPoint(float x, float y, vector<float> xs, vector<float> ys) ;
        vector<float> getAllDistancesFromPoint(float x, float y, vector<float> xs, vector<float> ys);
        float getWeight(float maxDistance, float thisDistance, vector<float> allDistances );

};

#endif

