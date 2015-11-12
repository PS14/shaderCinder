#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/Font.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GradationApp : public AppNative
{
public:
	void setup();
	void update();
	void draw();

	

	gl::TextureRef myTexture;
	gl::GlslProg myShader;
};

void GradationApp::setup()
{
	myTexture = gl::Texture::create(loadImage(loadAsset("free.png")));

	try
	{
		myShader = gl::GlslProg(loadFile("../data/passThru_vert.glsl"),
			loadFile("../data/gaussianBlur_frag.glsl"));
	}
	catch (...)
	{
		console() << "File could not be read!!" << std::endl;
	}
}

void GradationApp::update()
{
}

void GradationApp::draw()
{
	gl::clear();

	myTexture->enableAndBind();
	myShader.bind();
	myShader.uniform("tex0", 0);
	myShader.uniform("sampleOffset", Vec2f(5, 5) * (1.f / getWindowWidth()));
	gl::drawSolidRect(getWindowBounds());

	myTexture->unbind();
}

CINDER_APP_NATIVE(GradationApp, RendererGl)
