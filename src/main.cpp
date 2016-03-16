#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    ofGLWindowSettings settings;    
    settings.setGLVersion(3,2);   
    ofCreateWindow(settings);     // this kicks off the running of my app    
    ofRunApp(new ofApp());

}
