#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BLENDTESTApp : public AppBasic {
  public:
	void setup();
    void prepareSettings( Settings *settings );

	void mouseDown( MouseEvent event );
	void keyDown( KeyEvent event );
	void update();
	void draw();
    
    
    ci::gl::Texture test1;
    ci::gl::Texture test2;
    
    std::vector<string> blendsName;
    std::vector<int> blends;
    
    float doneTimer;
    
    int blendsSRCIndex;
    int blendsIndex;
};


void BLENDTESTApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize(1200, 600);
}

void BLENDTESTApp::setup()
{
    test1 = loadImage(loadAsset("window.png"));
    test2 = loadImage(loadAsset("scorebackgroundLeft.png"));
    
    
    blendsSRCIndex = 0;
    blendsIndex = 0;
    
    doneTimer = -1;
    
 
     blends.push_back(GL_ZERO);
     blends.push_back(GL_ONE);
     blends.push_back(GL_SRC_COLOR);
     blends.push_back(GL_ONE_MINUS_SRC_COLOR);
     blends.push_back(GL_DST_COLOR);
     blends.push_back(GL_ONE_MINUS_DST_COLOR);
     blends.push_back(GL_SRC_ALPHA);
     blends.push_back(GL_ONE_MINUS_SRC_ALPHA);
     blends.push_back(GL_DST_ALPHA);
     blends.push_back(GL_ONE_MINUS_DST_ALPHA);
     blends.push_back(GL_CONSTANT_COLOR);
     blends.push_back(GL_ONE_MINUS_CONSTANT_COLOR);
     blends.push_back(GL_CONSTANT_ALPHA);
     blends.push_back(GL_ONE_MINUS_CONSTANT_ALPHA);
    
    
    blendsName.push_back("GL_ZERO");
    blendsName.push_back("GL_ONE");
    blendsName.push_back("GL_SRC_COLOR");
    blendsName.push_back("GL_ONE_MINUS_SRC_COLOR");
    blendsName.push_back("GL_DST_COLOR");
    blendsName.push_back("GL_ONE_MINUS_DST_COLOR");
    blendsName.push_back("GL_SRC_ALPHA");
    blendsName.push_back("GL_ONE_MINUS_SRC_ALPHA");
    blendsName.push_back("GL_DST_ALPHA");
    blendsName.push_back("GL_ONE_MINUS_DST_ALPHA");
    blendsName.push_back("GL_CONSTANT_COLOR");
    blendsName.push_back("GL_ONE_MINUS_CONSTANT_COLOR");
    blendsName.push_back("GL_CONSTANT_ALPHA");
    blendsName.push_back("GL_ONE_MINUS_CONSTANT_ALPHA");

//	glBlendFunc( GL_SRC_ALPHA, GL_ONE );

    
}

void BLENDTESTApp::mouseDown( MouseEvent event )
{
}

void BLENDTESTApp::keyDown( KeyEvent event ){
    
    if(event.getCode() == event.KEY_RIGHT){
        if(++blendsSRCIndex >= blends.size()){
            blendsSRCIndex = 0;
            
            if(++blendsIndex >= blends.size()){
                blendsIndex = 0;
                doneTimer = getElapsedSeconds();
            }            
        }
    }else if(event.getCode() == event.KEY_LEFT){
        if(--blendsSRCIndex <0){
            blendsSRCIndex = blends.size()-1;
            
            if(--blendsIndex < 0 ){
                blendsIndex = blends.size()-1;;
            }
        }

    }else if(event.getCode() == event.KEY_ESCAPE){
        quit();
    }

    
    
   }


void BLENDTESTApp::update()
{
}

void BLENDTESTApp::draw()
{
 
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    glColor3f(1, 1, 1);    

    gl::enableAlphaBlending();
    
    glDisable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    glBlendFunc(blends[blendsSRCIndex], blends[blendsIndex]);

    
    gl::draw(test1,Vec2f(0,30));
    gl::draw(test2,Vec2f(200,30));
    
    // reset to default blending mode // glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );

    gl::enableAlphaBlending();
    glColor4f(0, 1, 1,1);
    gl::drawString("source :\t\t" + blendsName[blendsSRCIndex],Vec2f(100,10));
    gl::drawString("destination:\t" +blendsName[blendsIndex],Vec2f(100,20));
    
    if (doneTimer > 0 && (getElapsedSeconds() - doneTimer < 6)){
        gl::drawString("# ALL COMBINATIONS TESTED #",Vec2f(400,10));

    }

}

CINDER_APP_BASIC( BLENDTESTApp, RendererGl )
