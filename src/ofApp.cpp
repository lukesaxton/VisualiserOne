#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofBackground(0x2e, 0x18, 0x2b);
    ofSetFrameRate(30);
    
    fftLive.setMirrorData(false);
    fftLive.setup();
    
    string guiPath = "audio.xml";
    gui.setup("audio", guiPath, 20, 20);
    gui.add(audioThreshold.setup("audioThreshold", 1.0, 0.0, 1.0));
    gui.add(audioPeakDecay.setup("audioPeakDecay", 0.915, 0.0, 1.0));
    gui.add(audioMaxDecay.setup("audioMaxDecay", 0.995, 0.0, 1.0));
    gui.add(audioMirror.setup("audioMirror", false));
    gui.loadFromFile(guiPath);
    
    //cam.setupPerspective(false, 90, 90);
    
    meshOriginal = meshWarped = ofMesh::sphere(200, 30);
    
    rotationAxis.set(1,0,0);
    cam.setAutoDistance(true);
}

//--------------------------------------------------------------
void ofApp::update() {
    
    fftLive.setThreshold(audioThreshold);
    fftLive.setPeakDecay(audioPeakDecay);
    fftLive.setMaxDecay(audioMaxDecay);
    fftLive.setMirrorData(audioMirror);
    fftLive.update();
    
    //---------------------------------------------------------- dispacing mesh using audio.
    vector<ofVec3f> & vertsOriginal = meshOriginal.getVertices();
    vector<ofVec3f> & vertsWarped = meshWarped.getVertices();
    int numOfVerts = meshOriginal.getNumVertices();
    
    float * audioData = new float[numOfVerts];
    fftLive.getFftPeakData(audioData, numOfVerts);
    
    float meshDisplacement = 100;
    
    float avg = 0;
    for (int i = 0; i < 5; i++)
    {
        avg +=audioData[i];
    }
    avg/=5;
    
    viewDistance = (1-avg) * 100 + 600;
    
    for(int i=0; i<numOfVerts; i++) {
        float audioValue = audioData[i];
        ofVec3f & vertOriginal = vertsOriginal[i];
        ofVec3f & vertWarped = vertsWarped[i];
        
        ofVec3f direction = vertOriginal.getNormalized();
        vertWarped = vertOriginal + direction * meshDisplacement * audioValue;
    }
    
    
    delete[] audioData;
}

//--------------------------------------------------------------
void ofApp::draw()
{
//    static int boomAmount = 1;
    static int upOrDownCounter = 0;
    
    ofSetColor(0x48, 0xa4, 0xcf);
    
    int w = OFX_FFT_WIDTH;
    int h = OFX_FFT_HEIGHT;
    int x = 20;
    int y = ofGetHeight() - h - 20;
    //fftLive.draw(x, y, w, h);
    
    upOrDownCounter++;
    if (upOrDownCounter > 10000)
    {
        upOrDownCounter = 0;
//        
//        if (boomAmount < 0)
//        {
//            boomAmount = 1;
//        }
//        else
//        {
//            boomAmount = -1;
//        }
    }
    
    

    cam.begin();
    //cam.boom(boomAmount);
    meshWarped.drawWireframe();
    cam.ofNode::orbit(upOrDownCounter/10.0, upOrDownCounter/10.0, viewDistance);
    cam.ofNode::roll(1);
    //cam.rotateAround(1, rotationAxis, cam.getTarget().getPosition());
    cam.end();
    
    //gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}