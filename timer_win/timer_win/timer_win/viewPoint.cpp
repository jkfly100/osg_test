#include "viewPoint.h"

namespace osg_jk
{
	static int num = 0;
#if 0
	void CALLBACK SetViewPoint::callBack()
	{
		shared_ptr<SetViewPoint> setNewPoint(new SetViewPoint(_viewer));
		setNewPoint->setpoint(num);
		num++;
		if (num == 3)
		{
			num = 0;
		}

	}
#endif

	inline SetViewPoint::SetViewPoint(osgViewer::Viewer * viewer)
		:_viewer(viewer)
	{
		inPut();
	}

	inline void SetViewPoint::inPut()
	{
		string name = "beijing";
		double lon = 32;
		double lat = 116;

		string name2 = "chongqing";
		double lon2 = 35;
		double lat2 = 17;

		string name3 = "guangzhou";
		double lon3 = 189;
		double lat3 = -60;

		auto temp = make_pair(lon, lat);
		auto temp2 = make_pair(name.c_str(), temp);
		_viewPointNum.push_back(temp2);

		viewPoint2 vtemp;
		vtemp.name = name;
		vtemp.lon = lon;
		vtemp.lat = lat;
		_viewPointArry.push_back(vtemp);

		memset(&vtemp, 0, sizeof(viewPoint2));
		vtemp.name = name2;
		vtemp.lon = lon2;
		vtemp.lat = lat2;
		_viewPointArry.push_back(vtemp);

		memset(&vtemp, 0, sizeof(viewPoint2));
		vtemp.name = name3;
		vtemp.lon = lon3;
		vtemp.lat = lat3;
		_viewPointArry.push_back(vtemp);

		auto _temp = make_pair(lon2, lat2);
		auto _temp2 = make_pair(name2.c_str(), _temp);
		_viewPointNum.push_back(_temp2);

		auto _temp_ = make_pair(lon3, lat3);
		auto _temp2_ = make_pair(name3.c_str(), _temp_);
		_viewPointNum.push_back(_temp2_);
	}

	inline void SetViewPoint::setpoint(int num)
	{
		osg::ref_ptr<osgEarth::Util::EarthManipulator> earthManip = new osgEarth::Util::EarthManipulator;

		_viewer->setCameraManipulator(earthManip);//必须在setViewpoint之前
		//earthManip->setViewpoint(osgEarth::Viewpoint(_viewPointNum[num].first, _viewPointNum[num].second.first, _viewPointNum[num].second.second, 0, -2.5, -10, 1.57e7), 1);
		
		earthManip->setViewpoint(osgEarth::Viewpoint(_viewPointArry[num].name.c_str(), _viewPointArry[num].lon, _viewPointArry[num].lat, 0, -2.5, -10, 1.57e7), 1);

	}
#if 0
	inline void SetViewPoint::start()
	{
		MSG msg;
		SetTimer(NULL, 1, 2000, (TIMERPROC)callBack);
		while (GetMessage(&msg, NULL, NULL, NULL))
		{
			if (msg.message == WM_TIMER)
			{
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
		}
	}
#endif
}