#pragma once

#include "ofMain.h"
#include "ofxFFTLive.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    double sine(const double phase);
    
    ofxFFTLive fftLive;
    
    ofxPanel gui;
    ofxSlider<float> audioThreshold;
    ofxSlider<float> audioPeakDecay;
    ofxSlider<float> audioMaxDecay;
    ofxToggle audioMirror;
    ofxSlider<float> shaderPhase, shaderDistortion;
    
    
    ofMesh meshOriginal;
    ofMesh meshWarped;
    ofEasyCam cam;
    float viewDistance;
    ofFbo fbo;
    
    ofVec3f rotationAxis;
    
    bool guiToggle = false;
    bool directionToggle = false;
    
    ofShader shader;
    //ofCamera cam;
};
