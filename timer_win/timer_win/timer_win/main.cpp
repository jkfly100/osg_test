#include "viewPoint.cpp"

using namespace osg_jk;

#if 0
	static int num = 0;

	void CALLBACK callBack(osgViewer::Viewer * viewer)
	{
		shared_ptr<SetViewPoint> setNewPoint(new SetViewPoint(viewer));
		setNewPoint->setpoint(num);
		num++;
		if (num == 3)
		{
			num = 0;
		}

	}
#endif
	int travel()
	{
		osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

		osgEarth::Map * map = new osgEarth::Map();
		osgEarth::MapNode * mapNode = new osgEarth::MapNode(map);

		osgEarth::Drivers::TMSOptions imgOption;
		imgOption.url() = "http://readymap.org/readymap/tiles/1.0.0/7/";
		map->addLayer(new osgEarth::ImageLayer("image", imgOption));

		viewer->setCameraManipulator(new osgEarth::Util::EarthManipulator());
		viewer->setSceneData(mapNode);

		


		return viewer->run();
#if 0
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
#endif
	}

	int main()
	{

		travel();

		return 0;
	}
