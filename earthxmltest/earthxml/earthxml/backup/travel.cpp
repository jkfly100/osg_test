#include "travel.h"
#include<osgDB\ReadFile>
#include<osgViewer\Viewer>
#include<osg\Node>
#include <osgGA/NodeTrackerManipulator>


inline travelPath::travelPath(osgViewer::Viewer * viewer, MapNode * mapnode)
	: _time(0)
	, _viewer(viewer)
	, _mapNode(mapnode)
	, _numPos(0)
	, _animationPathMp(new osgGA::AnimationPathManipulator)
	, _animationPath(new osg::AnimationPath)
	, _time1(2)
	, _time2(2)
	, _high1(59999)
	, _high2(3999999)
{
}

inline void travelPath::setPosition(double lon, double lat, long int high)//添加经纬度和高度
{
	auto temp = make_pair(lon, lat);
	auto temp2 = make_pair(temp, high);
	_position.push_back(temp2);
	auto a1 = _position[0].first.first;
	auto a2 = _position[0].first.second;
	auto a3 = _position[0].second;
	_numPos++;
	//auto a = _position[_numPos].first.first;// = lon;
	//_position[_numPos].first.second = lat;
	//_position[_numPos].second = high;
}


inline void travelPath::GeoAdd(int i)//添加geopoint
{
	//it->set(_mapNode->getMapSRS(), _position[i].first.first, _position[i].first.second, _position[i].second, ALTMODE_ABSOLUTE);
	auto a = _position[i].first.first;
	GeoPoint geo(_mapNode->getMap()->getSRS(), _position[i].first.first, _position[i].first.second, _position[i].second);
	_geoPoint.push_back(geo);
	
}

inline void travelPath::Insert(string name, double lon, double lat)
{
	viewPoint temp;
	temp.PointName = name;
	temp.lon = lon;
	temp.lat = lat;
	temp.time = 2;

	_PathPoint.push_back(temp);
}

inline void travelPath::setPosition2()
{
	auto it = _PathPoint.begin();
	while (it != _PathPoint.end())
	{
		auto temp = make_pair(it->lon, it->lat);
		auto temp2 = make_pair(temp, _high1);
		_position.push_back(temp2);
		_position.push_back(temp2);
		auto temp3 = temp2;
		_numPos += 2;
		it++;
		//找到与下个停留点之间的中点
		if (it != _PathPoint.end())
		{
			auto tempMidle1 = make_pair((temp3.first.first + it->lon) / 2, (temp3.first.second + it->lat) / 2);
			auto tempMidle2 = make_pair(tempMidle1, _high2);
			_position.push_back(tempMidle2);
			_numPos++;
		}
	}
	
}

inline void travelPath::matrixTrans2()//未完成(已放弃)
{
	auto it = _PathPoint.begin();
	int i = 0;
	while (it != _PathPoint.end())
	{
		GeoAdd(i);
		osg::Matrix gMatrix;
		_geoPoint[i].createLocalToWorld(gMatrix);
		gMatrix.preMultRotate(osg::Quat(osg::DegreesToRadians(45.0), osg::X_AXIS));
		osg::Quat q;
		gMatrix.get(q);
		_quat.push_back(q);
		_vPos.push_back(gMatrix.getTrans());
		
		++i;
	}
}

inline void travelPath::matrixTrans()//设置剩余路径点
{
	setFirstPoint();

	int i = 1;
	int j = 0;

	while (j < _numPos - 1)
	{
		//it->set(_mapNode->getMapSRS(), _position[i].first.first, _position[i].first.second, _position[i].second, ALTMODE_ABSOLUTE);
		GeoAdd(i);
		osg::Matrix gMatrix;
		_geoPoint[i].createLocalToWorld(gMatrix);
		gMatrix.preMultRotate(osg::Quat(osg::DegreesToRadians(45.0), osg::X_AXIS));
		osg::Quat q;
		gMatrix.get(q);
		_quat.push_back(q);
		_vPos.push_back(gMatrix.getTrans());
		i++;
		j++;
	}
}

inline void travelPath::setFirstPoint()//设置起始点
{
	
	//auto a = _position[0].second;
	//itt->set(_mapNode->getMapSRS(), _position[0].first.first, _position[0].first.second, _position[0].second, ALTMODE_ABSOLUTE);
	GeoAdd(0);
	//auto itt = _geoPoint.begin();
	osg::Matrix gMatrix1;
	_geoPoint[0].createLocalToWorld(gMatrix1);//获取当前地球上的正确姿态
	gMatrix1.preMultRotate(osg::Quat(osg::DegreesToRadians(45.0), osg::X_AXIS));
	osg::Quat q;
	//gMatrix1.get(q);//获取当前矩阵姿态
	//gMatrix1.makeRotate(q);
	gMatrix1.get(q);
	_quat.push_back(q);
	_vPos.push_back(gMatrix1.getTrans());//获取当前矩阵位置
}

inline void travelPath::setPath2()
{
	for (int i = 1; i <= _vPos.size(); i++)
	{
		if ((i % 3) == 0)
		{
			_time += _time2;
		}
		else
		{
			_time += _time1;
		}
		_animationPath->insert(_time, osg::AnimationPath::ControlPoint(_vPos[i-1], _quat[i-1]));
		
		
	}
	_animationPath->setLoopMode(osg::AnimationPath::SWING);//设置路径是回摆的
	_animationPathMp->setAnimationPath(_animationPath);
	//_viewer->setCameraManipulator(_animationPath);


	//osg::ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
	//root->addChild(_mapNode);
	//osg::ref_ptr<osg::AnimationPathCallback> _animationcallpath = new osg::AnimationPathCallback(_animationPath.get());
	//root->setUpdateCallback(_animationcallpath);
	//_animationcallpath->setPause(true);

	auto nodetrack = new osgGA::NodeTrackerManipulator();
	osgGA::KeySwitchMatrixManipulator* keyPtr = new osgGA::KeySwitchMatrixManipulator();
	keyPtr->addMatrixManipulator('1', "earthMan", new EarthManipulator());
	keyPtr->addMatrixManipulator('2', "trakerMan", new osgGA::NodeTrackerManipulator());
	keyPtr->addMatrixManipulator('3', "animationPathMan", _animationPathMp);

	_viewer->setCameraManipulator(keyPtr);
}



inline void travelPath::setPath()//添加路径(已放弃)
{
	for (unsigned int i = 0; i < _vPos.size(); i++)
	{
		_animationPath->insert(_time, osg::AnimationPath::ControlPoint(_vPos[i], _quat[i]));
		_time += 2;
	}
	_animationPath->setLoopMode(osg::AnimationPath::SWING);//设置路径是回摆的
	_animationPathMp->setAnimationPath(_animationPath);

	//osg::NodeCallback * nc = nullptr;
	

	auto nodetrack = new osgGA::NodeTrackerManipulator();
	osgGA::KeySwitchMatrixManipulator* keyPtr = new osgGA::KeySwitchMatrixManipulator();
	keyPtr->addMatrixManipulator('1', "earthMan", new EarthManipulator());
	keyPtr->addMatrixManipulator('2', "trakerMan", new osgGA::NodeTrackerManipulator());
	keyPtr->addMatrixManipulator('3', "animationPathMan", _animationPathMp);
	_viewer->setCameraManipulator(keyPtr);
}

inline void travelPath::play()//开始漫游
{
	setPosition2();
	matrixTrans();
	setPath2();
}

inline osgViewer::Viewer * travelPath::getViewer()
{
	return _viewer;
}

inline osg::AnimationPath * travelPath::getPath()
{
	return _animationPath;
}

inline osgGA::AnimationPathManipulator * travelPath::getAniPathManipulator()
{
	return _animationPathMp;
}



inline bool UseEventHandler::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
{
	//osg::ref_ptr<osg::AnimationPathCallback> _animationcallpath = new osg::AnimationPathCallback();
	//_animationcallpath->setAnimationPath(_travel->getPath());
	//_mapNode->addUpdateCallback(_animationcallpath);
	//osg::ref_ptr<osg::Group> group = dynamic_cast<osg::Group*>(_viewer->getSceneData());
	//osg::ref_ptr<osgEarth::MapNode> group = dynamic_cast<osgEarth::MapNode*>(_viewer->getSceneData());
	//_animationcallpath = dynamic_cast<osg::AnimationPathCallback*>(group->getChild(0)->getUpdateCallback());
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	//设置更新回调
	auto _animationcallpath = new osg::AnimationPathCallback(_travel->getPath(), 0.0f, 1.0f);
	pat->setUpdateCallback(_animationcallpath);
	_mapNode->addChild(pat.get());

	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::KEYDOWN:
		if (ea.getKey() == 0xFFBE)
		{
			if (_animationcallpath == nullptr)
			{
				cout << "animationcallpath == nullptr" << endl;
				break;
			}
			_animationcallpath->_pauseTime = 2;
			_animationcallpath->setPause(true);

			
			return true;
		}
	default:
		break;
	}
	return false;
}


