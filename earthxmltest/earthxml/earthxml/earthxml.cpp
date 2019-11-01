#include "travel.cpp"
//#include "viewpoint.cpp"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osgGA/TrackballManipulator>
#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarthDrivers/tms/TMSOptions>
#include <osgEarthDrivers/model_feature_geom/FeatureGeomModelOptions>
#include <osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include <osgEarthDrivers/cache_filesystem/FileSystemCache>
#include <osgEarth/ImageLayer>
#include <osgEarth/ModelLayer>
#include <osgEarthDrivers/tms/TMSOptions>
#include <osgEarthUtil/EarthManipulator>
#include <osgUtil\optimizer>  
#include <osgGA\KeySwitchMatrixManipulator>

void setPause(osgEarth::MapNode * _mapNode, osg::AnimationPath * _path)
{
	osg::ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
	root->addChild(_mapNode);
	osg::ref_ptr<osg::AnimationPathCallback> _animationcallpath = new osg::AnimationPathCallback(_path);
	root->setUpdateCallback(_animationcallpath);
	_animationcallpath->setPause(true);
}

//void stopPause(osgEarth::MapNode * _mapNode, osg::AnimationPath * _path)
//{
//	osg::ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
//	root->addChild(_mapNode);
//	osg::ref_ptr<osg::AnimationPathCallback> _animationcallpath = new osg::AnimationPathCallback(_path);
//	root->setUpdateCallback(_animationcallpath);
//	_animationcallpath->setPause(false);
//}


/** @brief 创建场景 */
int Create()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	// create the map.创建一个地图
	osgEarth::Map* map = new osgEarth::Map();
	osgEarth::MapNode* mapNode = new osgEarth::MapNode( map );
	
	//add a TMS imager layer:添加一个TMS图片层
	//影像
	osgEarth::Drivers::TMSOptions imgOption;
	imgOption.url() = "http://readymap.org/readymap/tiles/1.0.0/7/";
	map->addLayer(new osgEarth::ImageLayer("image", imgOption));



	// initialize a viewer:
	viewer->setCameraManipulator(new osgEarth::Util::EarthManipulator());
	viewer->setSceneData(mapNode);

	/*osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("D:\\osgtest\\earthxmltest\\earthxml\\earthxml\\x64\\Debug\\boston.earth");
	root->addChild(node.get());
	osgUtil::Optimizer optimizer;

	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());*/

	// add some stock OSG handlers:
	viewer->addEventHandler(new osgViewer::StatsHandler());
	viewer->addEventHandler(new osgViewer::WindowSizeHandler());
	viewer->addEventHandler(new osgViewer::ThreadingHandler());
	viewer->addEventHandler(new osgViewer::LODScaleHandler());
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));
	
	//viewer->dEventHandler(new osgViewer::HelpHandler(arguments.getApplicationUsage()));

	//***********************************************************************************************
	shared_ptr<travelPath> travel(new travelPath(viewer, mapNode));

	travel->Insert("beijing", 32, 116);
	travel->Insert("beijing", 32, 120);
	travel->Insert("beijing", -62, 130);
	travel->Insert("beijing", -80, 77);
	

	travel->play();
	viewer->setCameraManipulator(travel->getAniPathManipulator());
	//viewer->addEventHandler(new UseEventHandler(mapNode, *travel,*viewer,))
	//***********************************************************************************************
	/*osg::ref_ptr<osg::AnimationPathCallback> _animationcallpath = new osg::AnimationPathCallback();
	_animationcallpath->setAnimationPath(travel->getPath());
	mapNode->addUpdateCallback(_animationcallpath);
	_animationcallpath->setPause(true);*/
	viewer->addEventHandler(new UseEventHandler(mapNode, *travel, *(viewer.get())));

	/*osg::ref_ptr<SetViewPoint> setPoint = new SetViewPoint(viewer.get());
	setPoint->inPut();
	setPoint->setpoint(0);*/

	return viewer->run();
	//return 0;
	
}



void main() {
	Create();
}