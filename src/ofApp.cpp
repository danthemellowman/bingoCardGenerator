#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    width = (2550/5);
    height = (2550/5);
    for(int i = 0; i < 30; i++){
        ofxTextBlock foo;
        words.push_back(foo);
    }
    
    BingoCard.setName("ITPGO!");
    BingoCard.add(lineWidth.set("lineWidth", 3, 1, 10));
    BingoCard.add(record.set("record", true));
    BingoCard.add(bMakeCards.set("bMakeCards", false));
    panel.setup(BingoCard);
    
    
    
    
    fbo.allocate(2550, 2550+height, GL_RGB);
    fbo.begin();
    ofClear(0, 0, 0);
    fbo.end();
    
    pixelBufferBack.allocate(fbo.getWidth()*fbo.getHeight()*3,GL_DYNAMIC_READ);
    pixelBufferFront.allocate(fbo.getWidth()*fbo.getHeight()*3,GL_DYNAMIC_READ);
    
    ofBuffer buff = ofBufferFromFile("wordlist");
    ofBuffer::Lines list = buff.getLines();
    for(auto key : list){
        wordlist.push_back(key);
    }
    makeBingoCard();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(bMakeCards){
        makeBingoCard();
    }else{
        count = 0;
    }
    if(count >= 100){
        ofExit();
    }
}

void ofApp::makeBingoCard(){
    
//    used.clear();
    ofSetLineWidth(lineWidth);
    for(int i = 0; i < words.size(); i++){
        if(i < 5){
            words[i].init(ofToDataPath("fonts/Chandstate.otf"), 250);
            switch(i){
                case 0:
                    words[i].setText("I");
                    break;
                case 1:
                    words[i].setText("T");
                    break;
                case 2:
                    words[i].setText("P");
                    break;
                case 3:
                    words[i].setText("G");
                    break;
                case 4:
                    words[i].setText("O");
                    break;
                    
            }
            words[i].wrapTextX((width-40));
        }else{
            ofSeedRandom();
            string random = wordlist[((int)ofRandom(wordlist.size()-1))%wordlist.size()];
            while(find(used.begin(), used.end(), random)!=used.end()){
                random = wordlist[((int)ofRandom(wordlist.size()))%wordlist.size()];
            }
            used.push_back(random);
            words[i].init(ofToDataPath("fonts/orbitron/Orbitron-Medium.ttf"), 45);
            if(i != 12+5){
                words[i].setText(ofToLower(random));
            }else{
                words[i].setText(" I. T. P.!!! ");
            }
            words[i].wrapTextX((width-40)*0.85);
        }
    }
    fbo.begin();
    ofClear(0, 0, 0);
    ofSetColor(0, 0, 0);
    ofFill();
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    int x = width/2;
    int y = height/2;
    
    for(int i = 0; i < 5; i++){
        if(i%2 == 1){
            ofSetColor(33, 161, 255);
        }else{
            ofSetColor(55, 104, 140);
        }
        words[i].drawCenter(x,(height-words[i].getHeight())/2);
        x+=width;
        if(x >= fbo.getWidth()){
            x = width/2;
            y+=height;
        }
    }
    
    for(int i = 5; i < words.size(); i++){
        
        ofFill();
        if(i%2 == 0){
            ofSetColor(33, 161, 255);
        }else{
            ofSetColor(55, 104, 140);
        }
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofDrawRectangle(x, y, width, height);
        if(i%2 == 1){
            ofSetColor(33, 161, 255);
        }else{
            ofSetColor(55, 104, 140);
        }
        ofSetColor(0, 0, 0);
        ofDrawRectangle(x, y, width-20, height-20);
        
        if(i%2 == 1){
            ofSetColor(33, 161, 255);
        }else{
            ofSetColor(55, 104, 140);
        }
        words[i].drawCenter(x,y-words[i].getHeight()/2);
        
        x+=width;
        if(x >= fbo.getWidth()){
            x = width/2;
            y+=height;
        }
    }
    fbo.end();
    
    
    if(record){
        
        fbo.getTexture().copyTo(pixelBufferBack);
        pixelBufferFront.bind(GL_PIXEL_UNPACK_BUFFER);
        unsigned char * p = pixelBufferFront.map<unsigned char>(GL_READ_ONLY);
        pixels.setFromExternalPixels(p,fbo.getWidth(),fbo.getHeight(),OF_PIXELS_RGB);
        ofSaveImage(pixels,"ITPGO-"+ofToString(count)+".jpg");
        pixelBufferFront.unmap();
        swap(pixelBufferBack,pixelBufferFront);
        count++;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255, 255, 255);
    fbo.draw(0, 0, ofGetWindowWidth(), ofGetWindowWidth()*fbo.getHeight()/fbo.getWidth());
    
    panel.draw();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        record=!record;
    }
}

