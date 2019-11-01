#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__


#include <Windows.h>
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

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

namespace osg_jk
{
	struct viewPoint2
	{
		string name;
		double lon;
		double lat;
	};

	using namespace std;

	class SetViewPoint
		:public osgGA::GUIEventHandler
	{
	public:
		SetViewPoint(osgViewer::Viewer * viewer);
		SetViewPoint() {}

		void inPut();

		void setpoint(int num);

		//void start();

		//void CALLBACK callBack();

		//bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa);

	private:
		vector<pair<const char *, pair<double, double>>> _viewPointNum;
		osg::ref_ptr<osgViewer::Viewer> _viewer;
		vector<viewPoint2> _viewPointArry;
		//string _name;
	};

}

#endif // !__MAIN_H__
