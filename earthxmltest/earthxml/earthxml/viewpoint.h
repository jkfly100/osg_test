#pragma once
#ifndef _VIEWPOINT__H__
#define _VIEWPOINT__H__


#include <osgDB/ReadFile>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarthDrivers/tms/TMSOptions>
#include <osgEarth/ImageLayer>
#include <osgEarth/ModelLayer>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthAnnotation/AnnotationUtils>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osg/MatrixTransform>
#include <osgGA/TrackballManipulator>
#include <osgEarthDrivers/model_feature_geom/FeatureGeomModelOptions>
#include <osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include <osgEarthDrivers/cache_filesystem/FileSystemCache>
#include <osgUtil\optimizer>  
#include <osgGA\KeySwitchMatrixManipulator>

#include <string>
#include <vector>
#include <iostream>

using namespace std;


class SetViewPoint
	:public osgGA::GUIEventHandler
{
public:
	SetViewPoint(osgViewer::Viewer * viewer);
	SetViewPoint() {}

	void inPut();

	void setpoint(int num);

	//bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa);

private:
	vector<pair<const char *, pair<double, double>>> _viewPointNum;
	osg::ref_ptr<osgViewer::Viewer> _viewer;
	//string _name;
};

#endif // !_TRAVEL__H__

