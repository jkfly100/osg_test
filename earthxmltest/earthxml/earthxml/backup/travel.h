#pragma once
#ifndef _TRAVEL__H__
#define _TRAVEL__H__




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


#include <vector>
#include <utility>

#include <osg/Image>
#include <osgEarthSymbology/Geometry>
#include <osgEarthSymbology/GeometryRasterizer>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarth/ImageToHeightFieldConverter>
#include <osgEarth/ImageUtils>
#include <osgEarth/FileUtils>
#include <osgEarth/Registry>
#include <osgEarth/MapFrame>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>
#include <osgDB/WriteFile>
#include <math.h>
#include <osgGA/NodeTrackerManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osg/PositionAttitudeTransform>


using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace std;

//setPosition()���þ�γ��
//GeoAdd���geopoint
//matrixtrans����·����
//setpath()����·��
//play()��ʼ����

struct viewPoint
{
	string PointName;
	double lon;
	double lat;
	int time;//ͣ����ʱ��
};

class travelPath
	//:public osgGA::GUIEventHandler
	//:public osg::NodeCallback
	:public osg::AnimationPathCallback
{
public:
	friend class UseEventHandler;

	travelPath(osgViewer::Viewer *viewer, MapNode *mapnode);

	void setPosition(double lon, double lat, long int high);

	

	void GeoAdd(int i);

	void matrixTrans();

	void setFirstPoint();

	void setPath();

	void setPath2();

	void play();

	void matrixTrans2();

	void setPosition2();

	void Insert(string name, double lon, double lat);

	//void setpause()//��ͣ
	//{
	//	//osg::ref_ptr<osg::AnimationPathCallback> pathCallback = new osg::AnimationPathCallback();
	//	_pathCallback = dynamic_cast<osg::AnimationPathCallback*>(_mapNode->getChild(0)->getUpdateCallback());
	//}

	osg::AnimationPath * getPath();
	osgGA::AnimationPathManipulator * getAniPathManipulator();
	osgViewer::Viewer * getViewer();

	~travelPath() 
	{}
private:
	vector<GeoPoint> _geoPoint;
	vector<osg::Vec3d> _vPos;
	vector<osg::Quat> _quat;
	int _time;//��ʼ��ʱ��
	osg::ref_ptr<osg::AnimationPath> _animationPath;
	osg::ref_ptr<osgGA::AnimationPathManipulator> _animationPathMp;
	//osgGA::AnimationPathManipulator* _animationPathMp;
	osg::ref_ptr<osgViewer::Viewer> _viewer;//���յ�viewer
	vector<pair<pair<double, double>, double>> _position;//���յ�·����ľ�γ�Ⱥ͸߶�
	int _numPos;//·����ĸ���
	osg::ref_ptr<MapNode> _mapNode;//��ͼ�ڵ�
	vector<viewPoint> _PathPoint;
	int _time1;//ͣ����·�����ʱ��
	int _time2;//·�ϵ�ʱ��
	long int _high1;//ͣ����ĸ߶�
	long int _high2;//������ĸ߶�
};



class UseEventHandler 
	:public::osgGA::GUIEventHandler
	//,public travelPath
	//,public	travelPath
{
public:
	UseEventHandler(osgEarth::MapNode * mapnode, travelPath & travel, osgViewer::Viewer & viewer)
		: _mapNode(mapnode)
		, _travel(&travel)
		, _viewer(&viewer)
		//, _nc(nc)
		//, _root(&root)
	{}

	bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa);

private:
	//osgViewer::Viewer * _viewer;
	osgEarth::MapNode * _mapNode;
	std::shared_ptr<travelPath> _travel;
	osg::ref_ptr< osgViewer::Viewer> _viewer;
	//osg::AnimationPathCallback * _nc;
	osg::MatrixTransform * _root;
};

#endif // !_TRAVEL__H__