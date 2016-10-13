#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofBackground(0x2e, 0x18, 0x2b);
    ofSetFrameRate(120);
    
    fftLive.setMirrorData(false);
    fftLive.setup();
    
    //string guiPath = "audio.xml";
    //gui.setup("audio", guiPath, 20, 20);
    
    gui.setup();
    gui.add(audioThreshold.setup("audioThreshold", 1.0, 0.0, 1.0));
    gui.add(audioPeakDecay.setup("audioPeakDecay", 0.935, 0.0, 1.0));
    gui.add(audioMaxDecay.setup("audioMaxDecay", 1, 0.0, 1.0));
    gui.add(audioMirror.setup("audioMirror", false));
    //gui.loadFromFile(guiPath);
    
    //cam.setupPerspective(false, 90, 90);
    
    meshOriginal = meshWarped = ofMesh::sphere(200, 30); //(200, 30);
    
    rotationAxis.set(1,0,0);
    cam.setAutoDistance(true);
    cam.disableMouseInput();
    
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
    
    if(!directionToggle)
    {
        upOrDownCounter++;
    }
    else
    {
        upOrDownCounter--;
    }
    if (upOrDownCounter > 10000)
    {
        directionToggle = !directionToggle;
    }
    
    

    cam.begin();
    //cam.boom(boomAmount);
    //meshWarped.drawFaces();
    //ofSetColor(0);
    meshWarped.drawWireframe();
    cam.ofNode::orbit(upOrDownCounter/10.0, upOrDownCounter/11.0, viewDistance);
    cam.ofNode::roll(1);
    //cam.rotateAround(1, rotationAxis, cam.getTarget().getPosition());
    cam.end();
    
    if(guiToggle)
    {
        gui.draw();
    }
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
void ofApp::mousePressed(int x, int y, int button)
{
    guiToggle = !guiToggle;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
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