#include "travel.cpp"

#include <osg/Image>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarth/Registry>
#include <osgEarthSymbology/Geometry>
#include <osgEarthSymbology/GeometryRasterizer>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarth/ImageToHeightFieldConverter>
#include <osgEarth/ImageUtils>
#include <osgEarth/FileUtils>
#include <osgEarth/Registry>
#include <osgEarth/MapFrame>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgEarthUtil/ExampleResources>
#include <math.h>

#include <osgGA/NodeTrackerManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;

int main(int argc, char ** argv)
{
	//正常的.earth文件加载
	osg::ArgumentParser arguments(&argc, argv);
	osgViewer::Viewer viewer(arguments);
	MapNode* s_mapNode = 0L;
	osg::Node* earthFile = MapNodeHelper().load(arguments, &viewer);
	if (earthFile)
		s_mapNode = MapNode::get(earthFile);
	if (!s_mapNode)
	{
		OE_WARN << "Unable to load earth file." << std::endl;
		return -1;
	}
	osg::Group* root = new osg::Group();
	root->addChild(earthFile);
	viewer.setSceneData(root);

	//模型漫游器
	osgGA::NodeTrackerManipulator* nodeTrack = new osgGA::NodeTrackerManipulator();
	nodeTrack->setTrackNode(root);


	//***********************************************************************************************
	shared_ptr<travelPath> travel(new travelPath(&viewer, s_mapNode));
	
	travel->setPosition(42.350849, -71.089399, 10);
	travel->setPosition(42.355359, -71.072663, 900);
	travel->setPosition(42.348092, -71.069221, 20);
	travel->play();

	//***********************************************************************************************
	//setPause(mapNode, travel->getPath());
	//stopPause(mapNode, travel->getPath());
	osgGA::KeySwitchMatrixManipulator* keyPtr = new osgGA::KeySwitchMatrixManipulator();
	keyPtr->addMatrixManipulator('3', "animationPathMan", travel->getAniPathManipulator());
	//keyPtr->addMatrixManipulator('3', "animationPathMan", new EarthManipulator());
	viewer.setCameraManipulator(keyPtr);

	viewer.run();
}