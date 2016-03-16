#pragma once

#include "ofMain.h"
#include "ofxVideoRecorder.h"
#include "ofxTween.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        ofTexture postProcess(ofTexture threeDSceneTex);
        //cube map stuff///////////////
        void setupCubeMap();
        void draw3dScene();
        ofCamera cubeCamera;
        ofFbo cubeFbo, saveFbo;
        void drawCubeMap();
        int cubeMapTileSize;
        float cubeSize;
        bool renderCubeMap;
        vector<float> degrees;
        vector<ofVec3f> axis;
        vector<ofTexture> cubeTextures;
        vector<ofPixels> cubePixels;
        int cubeIndex;
        float frameCounter;
        float endFrame;
        float beginFrame;
        float hello, goodBye;
        float boom, endBoom;
        float hueCycle;
        float texDirection;
        float fadeToBlack, fadeInColor;
        float texScale, zScale;
        //////////////////////////////
        float spikyMix;
        float increaseDisp;
        ofMatrix3x3         mat4ToMat3(ofMatrix4x4 mat4);
        void                updateNormalMatrix(ofShader& shader);
        void                updateNormalMatrix();
    
        ofShader embossShader, blurHShader, blurVShader,
                 displaceShader, fogShader, bumpShader,
                 rgbShader, glowShader, blurHShader2, blurVShader2, compositeShader, fxaaShader, finalShader;
    
        ofFbo embossFbo, embossBlurHFbo, embossBlurVFbo, blurHFbo, blurVFbo, bumpFbo, sceneFbo, compositeFbo, glowFbo, blurHFbo2, blurVFbo2, fxaaFbo;
        ofFbo embossFbo2, embossBlurHFbo2, embossBlurVFbo2;
        ofImage img, img2;
        ofPixels fbPix, fbPix2;
        ofTexture fbTex, fbTex2;
    
        int w, h;
        ofVideoPlayer calm, angry;
        ofPlanePrimitive plane;
        ofCylinderPrimitive cylinder;
        ofSpherePrimitive sphere;
        ofBoxPrimitive cube;
        ofEasyCam cam;
        ofImage noiseTex;
        ofMatrix3x3         normalMatrix;
    
        ofxEasingCubic easingCubic;
        ofxEasingElastic easingElastic;
        ofxEasingLinear easingLinear;
        ofTexture pp;
        ofxVideoRecorder recorder;
        ofPixels savePix;
        bool save;
        float angryMix, angryPct, dispPct, dispAmt, beatPct, beatAmt, beatHit, beatHitPct, fogPct, fogDist;
        float isAngry;
        int planeScale;
        int inc;
        float fogOsc, fogOscPct, colorMix, colorMixPct;
        float wait;
        bool showGui;
        ofxDatGui* gui;
        ofxDatGui2dPad* pad;
        ofxDatGuiSlider* colorslider;
        ofxDatGuiSlider* fogSlider;
        ofxDatGuiSlider* angryButton;
        ofxDatGuiSlider* fadeToBlackSlider;
        ofxDatGuiSlider* fadeInColorSlider;
        ofxDatGuiSlider* colorMixSlider;
        ofxDatGuiSlider* increaseDispSlider;

};


