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
    
    BingoCard.add(lineWidth.set("lineWidth", 3, 1, 10));
     BingoCard.add(record.set("record", true));
    ofSetLineWidth(5);
    
    fbo.allocate(2550, 2550+height, GL_RGBA);
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
    
}

//--------------------------------------------------------------
void ofApp::update(){
    makeBingoCard();
}

void ofApp::makeBingoCard(){
    used.clear();
    for(int i = 0; i < words.size(); i++){
        if(i < 5){
            words[i].init("edunline.ttf", 200);
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
            words[i].wrapTextX(width);
        }else{
            ofSeedRandom();
            string random = wordlist[((int)ofRandom(wordlist.size()-1))%wordlist.size()];
            while(find(used.begin(), used.end(), random)!=used.end()){
                random = wordlist[((int)ofRandom(wordlist.size()))%wordlist.size()];
            }
            used.push_back(random);
            words[i].init("edunline.ttf", 42);
            if(i != 12+5){
                words[i].setText(random);
            }else{
                words[i].setText("I.T.P.");
            }
            words[i].wrapTextX(width*0.85);
        }
    }
    fbo.begin();
    ofClear(0, 0, 0);
    ofSetColor(0, 0, 0);
    ofFill();
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    int x = width/2;
    int y = height/2;
    for(int i = 0; i < words.size(); i++){
        if(i%2 == 0){
            ofSetColor(255, 255, 0);
        }else{
            ofSetColor(255, 0, 255);
        }
        ofNoFill();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofDrawRectangle(x+lineWidth/2, y+lineWidth/2, width-lineWidth*2, height-lineWidth*2);
        if(i%2 == 1){
            ofSetColor(255, 255, 0);
        }else{
            ofSetColor(255, 0, 255);
        }
        words[i].drawCenter(x, y-words[i].getHeight()/2);
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
        ofSaveImage(pixels,"ITPGO-"+ofToString(ofGetFrameNum())+".jpg");
        pixelBufferFront.unmap();
        swap(pixelBufferBack,pixelBufferFront);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255, 255, 255);
    fbo.draw(0, 0, ofGetWindowWidth(), ofGetWindowWidth()*fbo.getHeight()/fbo.getWidth());
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        record=!record;
    }
}

