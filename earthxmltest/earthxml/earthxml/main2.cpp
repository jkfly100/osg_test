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


int main(int argc, char** argv)
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


	/*************************************动画漫游器**下*********************************/
	GeoPoint gPoint1(s_mapNode->getMap()->getSRS(), 32, 118, 400);
	osg::Matrix gMatrix1;
	gPoint1.createLocalToWorld(gMatrix1);//获取当前地球上的正确姿态
	//由于相机，自身向下看，所以在当前姿态基础上抬起60度，注意是前乘！
	gMatrix1.preMultRotate(osg::Quat(osg::DegreesToRadians(60.0), osg::X_AXIS));
	osg::Quat q1;    gMatrix1.get(q1);//获取当前矩阵姿态
	osg::Vec3d vPos1 = gMatrix1.getTrans();//获取当前矩阵位置

	GeoPoint gPoint2(s_mapNode->getMap()->getSRS(), 32.01, 118.01, 400);
	osg::Matrix gMatrix2;
	gPoint2.createLocalToWorld(gMatrix2);
	gMatrix2.preMultRotate(osg::Quat(osg::DegreesToRadians(60.0), osg::X_AXIS));
	osg::Quat q2;
	gMatrix2.get(q2);
	osg::Vec3d vPos2 = gMatrix2.getTrans();

	GeoPoint gPoint3(s_mapNode->getMap()->getSRS(), 32.02, 118.02, 400);
	osg::Matrix gMatrix3;
	gPoint3.createLocalToWorld(gMatrix3);
	osg::Quat q3;
	gMatrix3.get(q3);
	osg::Vec3d vPos3 = gMatrix3.getTrans();
	//获取相机之后再顺旋转,其实是错误的姿态
	//osg::Quat qbuf(osg::DegreesToRadians(60.0), osg::X_AXIS);
	//q3 *= qbuf;

	//使用动画漫游器
	osgGA::AnimationPathManipulator *animationPathMp = new osgGA::AnimationPathManipulator();
	//给动画漫游器添加关键帧
	osg::AnimationPath* _animationPath = new osg::AnimationPath;
	_animationPath->insert(0.0, osg::AnimationPath::ControlPoint(vPos1, q1));//姿态正确
	_animationPath->insert(3.0, osg::AnimationPath::ControlPoint(vPos2, q2));//姿态正确
	_animationPath->insert(6.0, osg::AnimationPath::ControlPoint(vPos3, q3));//姿态错误！
	_animationPath->setLoopMode(osg::AnimationPath::SWING);//设置路径是回摆的
	animationPathMp->setAnimationPath(_animationPath);
	/*************************************动画漫游器**上*********************************/

	auto manip = new osgEarth::Util::EarthManipulator();



	//这里添加三个漫游器，使用一个控制漫游器选择，按键盘‘3’就切换到路径动画漫游器了
	osgGA::KeySwitchMatrixManipulator* keyPtr = new osgGA::KeySwitchMatrixManipulator();
	keyPtr->addMatrixManipulator('1', "earthMan", new EarthManipulator());
	keyPtr->addMatrixManipulator('2', "trakerMan", nodeTrack);
	keyPtr->addMatrixManipulator('3', "animationPathMan", animationPathMp);
	viewer.setCameraManipulator(keyPtr);

	return viewer.run();
}