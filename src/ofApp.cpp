#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    w = 960;
    h = 540;
    cubeMapTileSize = 540;
    
    ofSetWindowShape(w,h);
    ofSetFrameRate(30);
    ofDisableArbTex();
    
    //fogShader.load("FogShaderTex.vert", "FogShaderTex.frag");
    embossShader.load("base.vert", "emboss.frag");
    blurHShader.load("blurH.vert", "blur.frag");
    blurVShader.load("blurV.vert", "blur.frag");
    displaceShader.load("displace.vert", "FogShaderTex.frag");
    bumpShader.load("base.vert", "bump.frag");
    rgbShader.load("base.vert", "rgb.frag");
    glowShader.load("base.vert", "glow.frag");
    blurHShader2.load("base.vert", "blurH.frag");
    blurVShader2.load("base.vert", "blurV.frag");
    compositeShader.load("base.vert", "composite.frag");
    fxaaShader.load("base.vert", "fxaa.frag");
    finalShader.load("base.vert", "final.frag");
    
    fbPix.allocate(w, h, OF_PIXELS_RGB);
    fbTex.allocate(w, h, GL_RGB);
    
    fbPix2.allocate(w, h, OF_PIXELS_RGB);
    fbTex2.allocate(w, h, GL_RGB);
    
    ofFbo::Settings s;
    
    s.width = w;
    s.height = h;
    s.textureTarget = GL_TEXTURE_2D;
    s.useDepth = true;
    s.depthStencilInternalFormat = GL_DEPTH_COMPONENT24;
    s.depthStencilAsTexture = true;
    s.numSamples = 1;
    
    //calm.loadMovie("calm.mov");
    //angry.loadMovie("angry.mov");
    //calm.setLoopState(OF_LOOP_NORMAL);
    //angry.setLoopState(OF_LOOP_NORMAL);
    //calm.play();
    //angry.play();
    
    int numSamples = 1;
    
    embossFbo.allocate(w, h, GL_RGB, numSamples);
    embossFbo2.allocate(w, h, GL_RGB, numSamples);
    blurHFbo.allocate(w, h, GL_RGB, numSamples);
    blurVFbo.allocate(w, h, GL_RGB, numSamples);
    embossBlurHFbo.allocate(w, h, GL_RGB, numSamples);
    embossBlurVFbo.allocate(w, h, GL_RGB, numSamples);
    embossBlurHFbo2.allocate(w, h, GL_RGB, numSamples);
    embossBlurVFbo2.allocate(w, h, GL_RGB, numSamples);
    bumpFbo.allocate(w, h, GL_RGB, numSamples);
    sceneFbo.allocate(w, h, GL_RGB, numSamples);
    compositeFbo.allocate(w, h, GL_RGB, numSamples);
    glowFbo.allocate(w, h, GL_RGB, numSamples);
    blurHFbo2.allocate(w, h, GL_RGB, numSamples);
    blurVFbo2.allocate(w, h, GL_RGB, numSamples);
    fxaaFbo.allocate(w, h, GL_RGB, numSamples);
    
    pp.allocate(w, h, GL_RGB);
    
    
    save = false;
    
    ofColor *colors = new ofColor[w*h];
    
    for(int i = 0; i<w*h*3; i++){
        //colors[i] = ofRandom(255);
        int r = ofRandom(255);
        int r2 = ofRandom(255);
        fbPix[i] = r;
        fbPix2[i] = r2;
    }
    
    img.setFromPixels(fbPix);
    img2.setFromPixels(fbPix2);

    
    embossFbo.begin();
    ofClear(0);
    ofBackground(255);
    ofSetColor(255);
    //ofRect(100, 0, w-200, 500 );
    img.draw(0,0, w, h);
    embossFbo.end();
    
    embossFbo2.begin();
    ofClear(0);
    ofBackground(255);
    ofSetColor(255);
    //ofRect(100, 0, w-200, 500 );
    img2.draw(0,0, w, h);
    embossFbo2.end();
    
    cam.setFarClip(1000000000);
    
    
    
    embossFbo.readToPixels(fbPix);
    fbTex.loadData(fbPix);
    
    embossFbo2.readToPixels(fbPix2);
    fbTex2.loadData(fbPix2);
    
    //cube.set(100,100,10000, 1,1,1);
    //cube.mapTexCoords(0, 0, w, h);
    

    
    cylinder.set(500, 40000, 500, 500);
    cylinder.setCapped(false);
    cylinder.mapTexCoords(0, 0, 1, 1);
    
    sphere.set(100000, 100);
    sphere.mapTexCoords(0, 0, 1, 1);

    //fogShader.begin();
    //fogShader.setUniform1f("density", 0.5f);
    //fogShader.setUniform4f("fogColor", 1.0, 0.0, 0.0, 1.0);
    //fogShader.end();
    
    cam.setFov(90);
    
    noiseTex.load("noise.jpg");
    noiseTex.getTexture().setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    sceneFbo.getTexture().setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    blurHFbo.getTexture().setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    blurVFbo.getTexture().setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    embossFbo.getTexture().setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    sceneFbo.getTexture().setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    bumpFbo.getTexture().setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    fbTex.setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    
    //ofSetTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    
    
    displaceShader.begin();
       // displaceShader.setUniformTexture("noise", noiseTex.getTexture(), 2);
    displaceShader.end();
    
    //m = plane.getMesh();
    
    recorder.setVideoBitrate("50000k");
    recorder.setVideoCodec("mpeg4");
    
    planeScale = 450;
    
    plane.set((w)*planeScale, w*2*planeScale, 1000, 1000);
    plane.mapTexCoords(0, 0, 1,1);
    
    //////////////////////
    renderCubeMap = false;
    //////////////////////
    
    if(renderCubeMap){
        setupCubeMap();
        savePix.allocate(cubeMapTileSize*4, cubeMapTileSize*3, OF_PIXELS_RGB);
        saveFbo.allocate(cubeMapTileSize*4, cubeMapTileSize*3, GL_RGB, numSamples);
        bumpFbo.allocate(cubeMapTileSize, cubeMapTileSize, GL_RGB, numSamples);
        compositeFbo.allocate(cubeMapTileSize, cubeMapTileSize, GL_RGB, numSamples);
        glowFbo.allocate(cubeMapTileSize, cubeMapTileSize, GL_RGB, numSamples);
        blurHFbo2.allocate(cubeMapTileSize, cubeMapTileSize, GL_RGB, numSamples);
        blurVFbo2.allocate(cubeMapTileSize, cubeMapTileSize, GL_RGB, numSamples);
        blurHFbo.allocate(cubeMapTileSize, cubeMapTileSize, GL_RGB, numSamples);
        blurVFbo.allocate(cubeMapTileSize, cubeMapTileSize, GL_RGB, numSamples);
        fxaaFbo.allocate(cubeMapTileSize, cubeMapTileSize, GL_RGB, numSamples);
    } else{
        savePix.allocate(w,h, OF_PIXELS_RGB);
        saveFbo.allocate(w,h, GL_RGB);
    }
    
    saveFbo.begin();
        ofClear(0);
    saveFbo.end();
    
    embossBlurHFbo.begin();
        ofClear(0);
    embossBlurHFbo.end();
    
    embossBlurVFbo.begin();
        ofClear(0);
    embossBlurVFbo.end();
    
    saveFbo.begin();
        ofClear(0);
    saveFbo.end();
    
    texDirection = 1.0;
    
    
    
    hello = 6452;
    goodBye = 7126;
    
    inc = hello;
    
    beginFrame = 6602;
    frameCounter = hello;

    endFrame = 6976;
    
    angryMix = 0;
    isAngry = 0.0;
    
    boom = 6703;
    endBoom = boom+30;
    
    wait = 0;
    
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    ofRectangle bounds = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());

    pad = gui->add2dPad("pad");
    colorslider = gui->addSlider("color", 0.0, 1.0);
    colorslider->setPrecision(4);
    
    fogSlider = gui->addSlider("fog", 0.0, 1.0);
    fogSlider->setPrecision(4);
    
    angryButton = gui->addSlider("angry", 0.0,1.0);
    angryButton->setPrecision(4);
    
//    fadeToBlackSlider = gui->addSlider("fade to black", 0.0,1.0);
//    fadeToBlackSlider->setPrecision(4);
//    
//    fadeInColorSlider = gui->addSlider("fade in color", 0.0,1.0);
//    fadeInColorSlider->setPrecision(4);
    
    colorMixSlider = gui->addSlider("colorMix", 0.0,1.0);
    colorMixSlider->setPrecision(4);
    
    increaseDispSlider = gui->addSlider("inc disp", 0.01, 20);
    increaseDispSlider->setPrecision(4);
    
    
    //  pad->setBounds(bounds);
    showGui = true;
    cam.disableMouseInput();
    
    ofxDatGuiLog::quiet();
}

//--------------------------------------------------------------
void ofApp::update(){

    if(save){
        //if(ofGetFrameNum()%30 == 0){
            //embossFbo.readToPixels(savePix);
            //recorder.addFrame(fbPix);
            //ofSaveImage(savePix, "frames/okeefe_"+ofGetTimestampString()+".jpg");
        //}
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    embossFbo.begin();
    ofPushMatrix();
    ofTranslate(0,0,ofMap(pad->getPoint().x, 0.0,w,1.0,20));//1.979);

    //ofRotate(-0.019  * -hueCycle, 1, 0, 1);
        embossShader.begin();
            embossShader.setUniformTexture("src_tex_unit0", fbTex, 0);
            embossShader.setUniform1f("imgWidth", ofGetWidth());
            embossShader.setUniform1f("imgHeight", ofGetHeight());
            embossShader.setUniform1f("step_w", ofMap(pad->getPoint().y,0,h, 1.0/ofGetWidth(), 1.0/ofGetWidth()*20) );
            embossShader.setUniform1f("step_h", ofMap(pad->getPoint().y,0,h, 1.0/ofGetHeight(), 1.0/ofGetHeight()*20) );
            embossShader.setUniform1f("angry", angryButton->getValue());
                fbTex.draw(0,0);
        embossShader.end();
    ofPopMatrix();
    embossFbo.end();
    
    
    for(int i = 0; i<2; i++){
        ofTexture tex;
        if(i == 0){
            tex = embossFbo.getTexture();
        } else{
            tex = embossBlurVFbo.getTexture();
        }
        
    embossBlurHFbo.begin();
        blurHShader.begin();
            blurHShader.setUniformTexture("s_texture", tex, 0);
            tex.draw(0,0);
        blurHShader.end();
    embossBlurHFbo.end();
    
    embossBlurVFbo.begin();
        blurVShader.begin();
            blurVShader.setUniformTexture("s_texture", embossBlurHFbo.getTexture(), 0);
                embossBlurHFbo.draw(0,0);
        blurVShader.end();
    embossBlurVFbo.end();
        
    }
    
    
    //embossFbo.readToPixels(fbPix);
    //fbTex.loadData(fbPix);
    
    fbTex = embossFbo.getTexture();
    //end feedback loop
    
    //animation settings/////////////////////////////////////////////////////
    colorMixPct = ofClamp(ofMap(frameCounter, boom, boom+2000, 0, 1), 0, 1);
    //colorMixPct = ofClamp(ofMap(frameCounter, endBoom, endFrame, 0, 1), 0, 1);
    colorMix = (( 1.0 - colorMixPct) * 0.2 ) + (colorMixPct * 1);
    fadeInColor = ofxTween::map(frameCounter, boom, boom+2000, 0.6, 1.0, true, easingCubic, ofxTween::easeInOut);
    
    hueCycle = 0.9;//ofxTween::map(frameCounter, boom+150, goodBye-75, 1.0, -30.1, true, easingCubic, ofxTween::easeInOut);

    //fogOscPct = ofClamp(ofMap(frameCounter, beginFrame, endFrame, 0, 1), 0, 1);
    //fogOsc = (( 1.0 - fogOscPct) * -1 ) + (fogOscPct * 0);
    
    fogOsc = ofxTween::map(frameCounter, boom, boom+2000, 0.7, 0.2, true, easingCubic, ofxTween::easeInOut);
    
    texScale = ofxTween::map(frameCounter, hello+75, boom+3000, 30.0, 1.0, true, easingCubic, ofxTween::easeOut);
    zScale = ofxTween::map(frameCounter, hello+95, boom+3000, 30.0, 1.0, true, easingCubic, ofxTween::easeOut);
    
    //angryPct = ofClamp(ofMap(frameCounter, boom, 6732, 0, 1), 0, 1);
    angryPct = ofxTween::map(frameCounter, boom, boom+1000, 0.0, 1.0, true, easingCubic, ofxTween::easeInOut);
    increaseDisp = ofxTween::map(frameCounter, boom, boom+1000, 0, 15, true, easingCubic, ofxTween::easeInOut);
    //increaseDisp = ofxTween::map(frameCounter, boom, 6762, 0, -500, true, easingCubic, ofxTween::easeInOut);
    //angryMix = 0.0;
    
    spikyMix = ofxTween::map(frameCounter, endFrame-90, endFrame-30, 0.0, 0.5, true, easingLinear, ofxTween::easeIn);
    
    if(frameCounter > boom && frameCounter < endBoom + 20){
        //angryMix = ((1.0 - angryPct) * 0.0 ) + (angryPct * 1.0);
        angryMix = angryPct;
        isAngry = true;
    } else if (frameCounter >= endBoom + 20){
        angryMix -= 0.0025;
        angryMix = ofClamp(angryMix, 0.0, 1.0);
        
        increaseDisp = ofxTween::map(frameCounter, boom+10, endFrame, 15, 15, true, easingCubic, ofxTween::easeInOut);
    }
    
    dispPct = ofClamp(ofMap(frameCounter, beginFrame, endFrame*10, 0, 1), 0, 1);
    dispAmt = ((1.0 - dispPct) * 10.0 ) + (dispPct * 10.0);

    beatHitPct = ofClamp(ofMap(frameCounter, boom, endFrame*10, 0, 1), 0, 1);
    beatHit = ((1.0 - beatHitPct) * 1.0) + (beatHitPct * 1.15);
    

    
    fogPct = ofClamp(ofMap(frameCounter, beginFrame, goodBye+1000, 0, 1), 0, 1);
    fogDist = ((1.0 - fogPct) * 500000 ) + (fogPct * 400000);
    
    if(frameCounter >= beginFrame && frameCounter < boom ){
     //   fogDist = ofxTween::map(frameCounter, beginFrame, boom, 500000, 600000, true, easingCubic, ofxTween::easeOut);
    }
    
    if(frameCounter < beginFrame){
        fogDist = ofxTween::map(frameCounter, hello+55, beginFrame, 2500000, 500000, true, easingCubic, ofxTween::easeOut);
    }
    
    fadeToBlack = 1.0;
    
    
    if(frameCounter >= goodBye - 150 ){
        fogPct = ofClamp(ofMap(frameCounter, goodBye-150, goodBye-100, 0, 1), 0, 1);
        fogDist = ((1.0 - fogPct) * 400000 ) + (fogPct * 100);
        fadeToBlack = ((1.0 - fogPct) * 1 ) + (fogPct * 0);
    }
    ///////////////////////////////////////////////////////////////
    
    
    if(!renderCubeMap){
        
        
        sceneFbo.begin();
            cam.begin();
                draw3dScene();
            cam.end();
        sceneFbo.end();
        
        pp = postProcess(sceneFbo.getTexture());
        
        
        pp.draw(0,0);
        
        //pp.readToPixels(savePix);
        //ofSaveImage(savePix, "chap11FlyThrough3/chap11FlyThrough_"+ofToString(frameCounter)+".jpg");
     
        //sceneFbo.draw(0,0);
       

        
    } else if(renderCubeMap){
        drawCubeMap();
    }
    
    

    if(ofGetKeyPressed('r')){
        embossFbo.draw(0,0);
    }
    
    
//    ofSetColor(0);
//    ofDrawRectangle(25,15,50,20);
//    ofSetColor(255);
//    ofDrawBitmapString(ofToString(frameCounter), 30,30);
    
    wait++;
    
    if(wait > 0){
    frameCounter++;
    }
    
}
//--------------------------------------------------------------
void ofApp::draw3dScene(){
    //ofRotate(ofClamp(ofMap(sin(ofGetFrameNum()*0.01), -1, 1, 360, 0), 0,360), 0, 0, 1);
    //ofRotate(sin(ofGetFrameNum()*0.1), 0,0,1);
    
    
    ofPushMatrix();
    ofClear(255*fadeToBlack);
        glEnable(GL_DEPTH_TEST);
        finalShader.begin();
        finalShader.setUniform1f("mX", 1.0);
        finalShader.setUniformTexture("u_image", fbTex, 0);
            sphere.draw();
        finalShader.end();
    ofPopMatrix();
    
    ofRotate(90, 0, 1, 0);
    ofPushMatrix();
        glEnable(GL_DEPTH_TEST);
    
            displaceShader.begin();
            displaceShader.setUniform1f("angryMix", 0.5);
            displaceShader.setUniform1f("dispAmt", increaseDispSlider->getValue());
            displaceShader.setUniform1f("beat", 1.0);
            displaceShader.setUniform1f("uFogDist", fogDist);
            displaceShader.setUniform1f("increaseDisp", increaseDisp);
//            displaceShader.setUniform1f("fadeToBlack", fadeToBlackSlider->getValue());
//            displaceShader.setUniform1f("fadeInColor", fadeInColorSlider->getValue());
            displaceShader.setUniform1f("texScale", texScale);
            displaceShader.setUniform1f("zScale", increaseDispSlider->getValue());
//            displaceShader.setUniform1f("spikyMix", spikyMix);
            displaceShader.setUniform1f("texDirection", texDirection);
    
            displaceShader.setUniformTexture("u_image", embossBlurVFbo.getTexture(), 0);
            displaceShader.setUniformTexture("angryTex", embossFbo.getTexture(), 3);
            displaceShader.setUniform1f("time", ofGetFrameNum()*0.1);
            displaceShader.setUniformTexture("baseMap", embossBlurVFbo.getTexture(), 1);
            displaceShader.setUniformTexture("noise", noiseTex.getTexture(), 2);
            displaceShader.setUniform1f("mouseX", ofMap(ofGetMouseX(), 0, ofGetWidth(), 1, 200));
            updateNormalMatrix(displaceShader);
    
            ofPushMatrix();
            //ofRotate(ofGetFrameNum()*0.5, 0, 1, 0);
//                ofPushMatrix();
//                ofTranslate(0,0,-10000);
//                ofRotate(ofGetFrameNum()*-0.1, 0, 1, 0);
//                    cylinder.draw();
//                ofPopMatrix();
//
//                ofPushMatrix();
//                ofTranslate(0,0,10000);
//                ofRotate(ofGetFrameNum()*0.1, 0, 1, 0);
//                    cylinder.draw();
//                ofPopMatrix();
    
                ofPushMatrix();
                ofTranslate(0,0,0);
                ofRotate(180, 0, 1, 0);
                    ofPushMatrix();
                    ofRotate(90, 1, 0, 0);
                        cylinder.draw();
                    ofPopMatrix();
                ofPopMatrix();
    
            ofPopMatrix();
    
            displaceShader.end();
    
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
}
//--------------------------------------------------------------
ofTexture ofApp::postProcess(ofTexture threeDSceneTex){
    bumpFbo.begin();
        bumpShader.begin();

            bumpShader.setUniform1f("fogOsc", fogSlider->getValue());
        

            bumpShader.setUniform1f("colorMix", colorMixSlider->getValue());
        
            bumpShader.setUniform2f("res", 1.0/ofGetWidth(), 1.0/ofGetHeight());
            bumpShader.setUniformTexture("u_image", threeDSceneTex, 0);
            
            bumpShader.setUniformTexture("bump2", threeDSceneTex, 1);
            bumpShader.setUniform1f("time", ofGetFrameNum()*0.1);

//            bumpShader.setUniform1f("fadeToBlack", fadeToBlackSlider->getValue());
//            bumpShader.setUniform1f("fadeInColor", fadeInColorSlider->getValue());
            bumpShader.setUniform1f("hueCycle", hueCycle);
    
            bumpShader.setUniform1f("colorSlider", colorslider->getValue());
            threeDSceneTex.draw(0,0);
        bumpShader.end();
    bumpFbo.end();
    
    
    glowFbo.begin();
    glowShader.begin();
        glowShader.setUniformTexture("srcTex", bumpFbo.getTexture(), 0);
        glowShader.setUniform2f("step", 5.0/w, 5.0/h);
        glowShader.setUniform1f("time", ofGetFrameNum()*0.1);
        
        bumpFbo.draw(0,0);
    glowShader.end();
    glowFbo.end();
        
    //glowFbo.draw(0,0);
        
    
    for(int i = 0; i<1; i++){
        ofTexture blurTex;
        if(i == 0){
            blurTex = glowFbo.getTexture();
        } else{
            blurTex = blurVFbo2.getTexture();
        }
        
        blurHFbo2.begin();
            blurHShader2.begin();
                blurHShader2.setUniformTexture("srcTex", blurTex, 0);
                blurHShader2.setUniform2f("res", 1.0,1.0);
                blurHShader2.setUniform2f("step", 1.0/w, 1.0/h);
                blurTex.draw(0,0);
            blurHShader2.end();
        blurHFbo2.end();
            
        blurVFbo2.begin();
            blurVShader2.begin();
                blurVShader2.setUniformTexture("srcTex", blurHFbo2.getTexture(), 0);
                blurVShader2.setUniform2f("res", 1.0,1.0);
                blurVShader2.setUniform2f("step", 1.0/w, 1.0/h);
                blurHFbo2.draw(0,0);
            blurVShader2.end();
        blurVFbo2.end();
    }
      
        
    for(int i = 0; i<1; i++){
        ofTexture blurTex;
        if(i == 0){
            blurTex = bumpFbo.getTexture();
        } else{
            blurTex = blurVFbo.getTexture();
        }
        
        blurHFbo.begin();
            blurHShader2.begin();
                blurHShader2.setUniformTexture("srcTex", blurTex, 0);
                blurHShader2.setUniform2f("res", 1.0,1.0);
                blurHShader2.setUniform2f("step", 1.0/w, 1.0/h);
                blurTex.draw(0,0);
            blurHShader2.end();
        blurHFbo.end();
            
        blurVFbo.begin();
            blurVShader2.begin();
                blurVShader2.setUniformTexture("srcTex", blurHFbo.getTexture(), 0);
                blurVShader2.setUniform2f("res", 1.0,1.0);
                blurVShader2.setUniform2f("step", 1.0/w, 1.0/h);
                blurHFbo.draw(0,0);
            blurVShader2.end();
        blurVFbo.end();
    }
        
    
        compositeFbo.begin();
            compositeShader.begin();
            compositeShader.setUniformTexture("bumpTex", bumpFbo.getTexture(), 0);
            compositeShader.setUniformTexture("edgeTex", blurVFbo2.getTexture(), 1);
            compositeShader.setUniformTexture("blurTex", blurVFbo.getTexture(), 2);
            bumpFbo.draw(0,0);
            compositeShader.end();
        compositeFbo.end();
    
        //compositeFbo.draw(0,0);
        //bumpFbo.draw(0,0);
    
    
     fxaaFbo.begin();
         fxaaShader.begin();
         fxaaShader.setUniformTexture("tDiffuse", compositeFbo.getTexture(), 0);
        if(renderCubeMap){
            fxaaShader.setUniform2f("resolution", 1.0/(cubeMapTileSize), 1.0/(cubeMapTileSize));
        } else{
            fxaaShader.setUniform2f("resolution", 1.0/(w), 1.0/(h));
        }
            compositeFbo.draw(0,0);
         fxaaShader.end();
     fxaaFbo.end();
    
    
    
    return fxaaFbo.getTexture();
    
}

//--------------------------------------------------------------
void ofApp::setupCubeMap(){
    cubeCamera.setVFlip(true);
    cubeCamera.setPosition(0, 0, 0);
    cubeCamera.setFov(90);
    cubeCamera.setFarClip(1000000);
    cubeCamera.setForceAspectRatio(true);
    cubeCamera.setAspectRatio(w/w);
    
    cubeSize = cubeMapTileSize;
    cubeFbo.allocate(cubeSize, cubeSize, GL_RGB);
    
    degrees.push_back(0);
    degrees.push_back(90);
    degrees.push_back(90);
    degrees.push_back(90);
    degrees.push_back(180);
    degrees.push_back(270);
    
    axis.push_back(ofVec3f(1,0,0));
    axis.push_back(ofVec3f(-1,0,0));
    axis.push_back(ofVec3f(1,0,0));
    axis.push_back(ofVec3f(0,-1,0));
    axis.push_back(ofVec3f(0,1,0));
    axis.push_back(ofVec3f(0,-1,0));
    
    cubeIndex = 0;
    
    cubeFbo.begin();
    ofClear(0);
    cubeFbo.end();
    
}

//--------------------------------------------------------------
void ofApp::drawCubeMap(){
    ofTexture pp, pp2, pp3, pp4, pp5, pp6;
    
    saveFbo.begin();
    
    cubeCamera.setGlobalPosition(0, 0, 0);
    cubeFbo.begin();
    ofClear(0);
    cubeCamera.setOrientation(ofQuaternion(degrees[0], axis[0]));
    cubeCamera.begin();
    draw3dScene();
    cubeCamera.end();
    cubeFbo.end();
    
    pp = postProcess(cubeFbo.getTexture());
    pp.draw(cubeSize, cubeSize, cubeSize, cubeSize);
    
    
    
    
    cubeCamera.setGlobalPosition(0, 0, 0);
    cubeFbo.begin();
    ofClear(0);
    cubeCamera.setOrientation(ofQuaternion(degrees[1], axis[1]));
    cubeCamera.begin();
    draw3dScene();
    cubeCamera.end();
    cubeFbo.end();
    
    pp2 = postProcess(cubeFbo.getTexture());
    pp2.draw(cubeSize, 0, cubeSize, cubeSize);
    
    
    
    
    cubeCamera.setGlobalPosition(0, 0, 0);
    cubeFbo.begin();
    ofClear(0);
    cubeCamera.setOrientation(ofQuaternion(degrees[2], axis[2]));
    cubeCamera.begin();
    draw3dScene();
    cubeCamera.end();
    cubeFbo.end();
    
    pp3 = postProcess(cubeFbo.getTexture());
    pp3.draw(cubeSize, cubeSize*2, cubeSize, cubeSize);
    
    
    
    
    cubeCamera.setGlobalPosition(0, 0, 0);
    cubeFbo.begin();
    ofClear(0);
    cubeCamera.setOrientation(ofQuaternion(degrees[3], axis[3]));
    cubeCamera.begin();
    draw3dScene();
    cubeCamera.end();
    cubeFbo.end();
    
    pp4 = postProcess(cubeFbo.getTexture());
    pp4.draw(cubeSize*2, cubeSize, cubeSize, cubeSize);
    
    
    

    cubeCamera.setGlobalPosition(0, 0, 0);
    cubeFbo.begin();
    ofClear(0);
    cubeCamera.setOrientation(ofQuaternion(degrees[4], axis[4]));
    cubeCamera.begin();
    draw3dScene();
    cubeCamera.end();
    cubeFbo.end();
    
    pp5 = postProcess(cubeFbo.getTexture());
    pp5.draw(cubeSize*3, cubeSize, cubeSize, cubeSize);

    
    
    
    cubeCamera.setGlobalPosition(0, 0, 0);
    cubeFbo.begin();
    ofClear(0);
    cubeCamera.setOrientation(ofQuaternion(degrees[5], axis[5]));
    cubeCamera.begin();
    draw3dScene();
    cubeCamera.end();
    cubeFbo.end();
    
    pp6 = postProcess(cubeFbo.getTexture());
    pp6.draw(0,cubeSize, cubeSize, cubeSize);
    
    
    
    
    saveFbo.end();
    

    
    saveFbo.readToPixels(savePix);

    ofSaveImage(savePix, "cubeImages/final/ch13_"+ofToString(inc)+".tga");
    inc++;
    
    
    saveFbo.draw(0,0, w, h);
    
    //video.nextFrame();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        save = !save;
        recorder.setup("embossLandScape_"+ofGetTimestampString()+"_.mov", w, h, 30);
        recorder.start();
    }
    if(key == '1'){
        frameCounter = hello;
        isAngry = false;
        fbTex.loadData(img.getPixels());
        fbTex2.loadData(img2.getPixels());
        wait = 0;
    }
    
    if(key == '2'){
        fbTex.loadData(img.getPixels());
    }
    
    if(key == '3'){
        frameCounter = endFrame-30;
    }
    
    if(key == 'h'){
        showGui = !showGui;
        gui->setVisible(showGui);
        if(showGui){
            cam.disableMouseInput();
        } else{
            cam.enableMouseInput();
        }
    }
    
    
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


void ofApp::updateNormalMatrix(ofShader& shader)
{
    updateNormalMatrix();
    shader.setUniform3f("firstRow", normalMatrix.a, normalMatrix.b, normalMatrix.c);
    shader.setUniform3f("secondRow", normalMatrix.d, normalMatrix.e, normalMatrix.f);
    shader.setUniform3f("thirdRow", normalMatrix.g, normalMatrix.h, normalMatrix.i);
}

ofMatrix3x3 ofApp::mat4ToMat3(ofMatrix4x4 mat4)
{
    return ofMatrix3x3(mat4._mat[0][0], mat4._mat[0][1], mat4._mat[0][2], mat4._mat[1][0], mat4._mat[1][1], mat4._mat[1][2], mat4._mat[2][0], mat4._mat[2][1], mat4._mat[2][2]);
}

void ofApp::updateNormalMatrix()
{
    normalMatrix = mat4ToMat3(ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
    normalMatrix.invert();
    normalMatrix.transpose();
}

