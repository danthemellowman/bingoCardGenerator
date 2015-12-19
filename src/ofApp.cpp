#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    width = (2550/5);
    height = (2550/5);
    for(int i = 0; i < 30; i++){
        ofxTextBlock foo;
        words.push_back(foo);
    }
    
    
    fbo.allocate(2550, 2550+height, GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0);
    fbo.end();
    
    ofBuffer buff = ofBufferFromFile("wordlist");
    ofBuffer::Lines list = buff.getLines();
    for(auto key : list){
        wordlist.push_back(key);
    }
    
    for(int i = 0; i < 30; i++){
        if(i < 5){
            words[i].init("VCR_OSD_MONO 2.ttf", 150);
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
            string random = wordlist[((int)ofRandom(wordlist.size()))%wordlist.size()];
            while(find(used.begin(), used.end(), random)!=used.end()){
                random = wordlist[((int)ofRandom(wordlist.size()))%wordlist.size()];
            }
            used.push_back(random);
            words[i].init("VCR_OSD_MONO 2.ttf", 42);
            if(i != 12+5){
                words[i].setText(random);
            }else{
                words[i].setText("I.T.P.");
            }
            words[i].wrapTextX(width*0.75);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofPixels pix;
    pix.allocate(fbo.getWidth(), fbo.getHeight(), 4);
    fbo.readToPixels(pix);
    
    ofImage img;
    img.setFromPixels(pix);
    img.save(ofGetTimestampString()+".png");
    
    used.clear();
    for(int i = 0; i < 30; i++){
        if(i < 5){
            words[i].init("VCR_OSD_MONO 2.ttf", 150);
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
            string random = wordlist[((int)ofRandom(wordlist.size()))%wordlist.size()];
            while(find(used.begin(), used.end(), random)!=used.end()){
                random = wordlist[((int)ofRandom(wordlist.size()))%wordlist.size()];
            }
            used.push_back(random);
            words[i].init("VCR_OSD_MONO 2.ttf", 42);
            if(i != 12+5){
                words[i].setText(random);
            }else{
                words[i].setText("I.T.P.");
            }
            words[i].wrapTextX(width*0.85);
        }
    }

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    fbo.begin();
    ofClear(0, 0, 0);
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight()-fbo.getWidth());
    int x = width/2;
    int y = height/2;
    for(int i = 0; i < words.size(); i++){
        if(i%2 == 0){
            ofSetColor(255, 255, 0);
        }else{
            ofSetColor(255, 0, 255);
        }
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofDrawRectangle(x, y, width, height);
        ofSetColor(0, 0, 0);
        words[i].drawCenter(x, y-words[i].getHeight()/2);
        x+=width;
        if(x >= fbo.getWidth()){
            x = width/2;
            y+=height;
        }
    }
    fbo.end();
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255, 255, 255);
    fbo.draw(0, 0);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        ofPixels pix;
        pix.allocate(fbo.getWidth(), fbo.getHeight(), 4);
        fbo.readToPixels(pix);
        
        ofImage img;
        img.setFromPixels(pix);
        img.save(ofGetTimestampString()+".png");
        
        used.clear();
        for(int i = 0; i < 30; i++){
            if(i < 5){
                words[i].init("VCR_OSD_MONO 2.ttf", 150);
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
                string random = wordlist[((int)ofRandom(wordlist.size()))%wordlist.size()];
                while(find(used.begin(), used.end(), random)!=used.end()){
                    random = wordlist[((int)ofRandom(wordlist.size()))%wordlist.size()];
                }
                used.push_back(random);
                words[i].init("VCR_OSD_MONO 2.ttf", 42);
                if(i != 12+5){
                    words[i].setText(random);
                }else{
                    words[i].setText("I.T.P.");
                }
                words[i].wrapTextX(width*0.85);
            }
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
