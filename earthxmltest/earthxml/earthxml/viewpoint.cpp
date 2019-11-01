#include "viewpoint.h"

inline SetViewPoint::SetViewPoint(osgViewer::Viewer * viewer)
	:_viewer(viewer)
{}

inline void SetViewPoint::inPut()
{
	string name = "beijing";
	double lon = 32;
	double lat = 116;

	string name2 = "chongqing";
	double lon2 = 35;
	double lat2 = 17;

	/*cout << "position name:" << endl;
	cin >> name;
	cout << "lon:" << endl;
	cin >> lon;
	cout << "lat:" << endl;
	cin >> lat;*/

	auto temp = make_pair(lon, lat);
	auto temp2 = make_pair(name.c_str(), temp);

	_viewPointNum.push_back(temp2);

	auto _temp = make_pair(lon2, lat2);
	auto _temp2 = make_pair(name2.c_str(), _temp);

	_viewPointNum.push_back(_temp2);
}

inline void SetViewPoint::setpoint(int num)
{
	osg::ref_ptr<osgEarth::Util::EarthManipulator> earthManip = new osgEarth::Util::EarthManipulator;

	_viewer->setCameraManipulator(earthManip);//必须在setViewpoint之前
	earthManip->setViewpoint(osgEarth::Util::Viewpoint(_viewPointNum[num].first, _viewPointNum[num].second.first, _viewPointNum[num].second.second, 0, -2.5, -10, 1.57e7), 1);

}
/*
inline bool SetViewPoint::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
{

	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::KEYDOWN:
		if (ea.getKey() == 0xFFBE)
		{

			/*int num;
			cout << "三组视点：" << endl;
			for (int i = 0; i < 2; i++)
			{
			inPut();
			}
			cin >> num;
			setpoint(num);*/
/*/
			inPut();

		}
		if (ea.getKey() == 0xFFBF)
		{
			setpoint(0);
		}
		if (ea.getKey() == 0xFFC0)
		{
			setpoint(1);
		}
	default:
		break;
	}
	return false;
}
*/