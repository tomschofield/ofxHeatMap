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

#include "ofxHeatMap.h"

void ofxHeatMap::setup(){
    
}


//ITERATES THROUGH ALL THE DATA POINTS AND FINDS THE FURTHERS ONE
float ofxHeatMap::getMaxDistanceFromPoint(float x, float y, vector<float> xs, vector<float> ys) {
    float maxDistance=0.0f;
    //get disance between this and each pther point
    for (int i=0;i<xs.size();i++) {
        ofVec2f vec1 =  ofVec2f(x,y);
        ofVec2f vec2 =  ofVec2f(xs[i],ys[i]);

        float thisDist=vec1.distance(vec2);
        //if this distance is greater than previous distances, this is the new max
        if (thisDist>maxDistance) {
            maxDistance=thisDist;
        }
    }
    return maxDistance;
}

//RETURNS AN ARRAY OF THE DISTANCE BETWEEN THIS PIXEL AND ALL DATA POINTS
vector<float>  ofxHeatMap::getAllDistancesFromPoint(float x, float y, vector<float> xs, vector<float> ys) {
    vector<float>  allDistances;
    for (int i=0;i<xs.size();i++) {
        ofVec2f vec1 =  ofVec2f(x,y);
        ofVec2f vec2 =  ofVec2f(xs[i],ys[i]);
        
        float thisDist=vec1.distance(vec2);
        allDistances.push_back(thisDist);
    }
    
    return allDistances;
}


//RETURNS THE ACTUAL WEIGHTED VALUE FOR THIS PIXEL
float ofxHeatMap::getInterpValue(float x, float y, vector<float> xs, vector<float> ys, vector<float> f ){
    float interpValue=0.0f;
    
    for (int i=0;i<xs.size();i++) {
        float maxDist = getMaxDistanceFromPoint( x, y, xs, ys);
        vector<float> allDistances;
        
        allDistances= getAllDistancesFromPoint( x, y, xs, ys);
        ofVec2f vec1 =  ofVec2f(x,y);
        ofVec2f vec2 =  ofVec2f(xs[i],ys[i]);
        
        float thisDistance=vec1.distance(vec2);
       
        interpValue += f[i]*getWeight( maxDist, thisDistance, allDistances );
    }
    return interpValue;
}

//THE WEIGHT IS THE VALUE COEFFICIENT (? RIGHT TERM) BY WHICH WE WILL MULTIPLY EACH VALUE TO GET THE CORRECT WEIGHTING
float ofxHeatMap::getWeight(float maxDistance, float thisDistance, vector<float> allDistances ) {
    float weight=0.0f;
    float firstTerm = pow(((maxDistance - thisDistance   )/( maxDistance * thisDistance  )), 2);
    float secondTerm=0.0f;
    for (int i=0;i<allDistances.size();i++) {
        secondTerm+=pow(((maxDistance - allDistances[i]   )/( maxDistance * allDistances[i]  )), 2);
    }
    weight = firstTerm/secondTerm;
    return weight;
}