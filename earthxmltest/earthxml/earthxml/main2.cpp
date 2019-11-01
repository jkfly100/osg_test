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
	//������.earth�ļ�����
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

	//ģ��������
	osgGA::NodeTrackerManipulator* nodeTrack = new osgGA::NodeTrackerManipulator();
	nodeTrack->setTrackNode(root);


	/*************************************����������**��*********************************/
	GeoPoint gPoint1(s_mapNode->getMap()->getSRS(), 32, 118, 400);
	osg::Matrix gMatrix1;
	gPoint1.createLocalToWorld(gMatrix1);//��ȡ��ǰ�����ϵ���ȷ��̬
	//����������������¿��������ڵ�ǰ��̬������̧��60�ȣ�ע����ǰ�ˣ�
	gMatrix1.preMultRotate(osg::Quat(osg::DegreesToRadians(60.0), osg::X_AXIS));
	osg::Quat q1;    gMatrix1.get(q1);//��ȡ��ǰ������̬
	osg::Vec3d vPos1 = gMatrix1.getTrans();//��ȡ��ǰ����λ��

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
	//��ȡ���֮����˳��ת,��ʵ�Ǵ������̬
	//osg::Quat qbuf(osg::DegreesToRadians(60.0), osg::X_AXIS);
	//q3 *= qbuf;

	//ʹ�ö���������
	osgGA::AnimationPathManipulator *animationPathMp = new osgGA::AnimationPathManipulator();
	//��������������ӹؼ�֡
	osg::AnimationPath* _animationPath = new osg::AnimationPath;
	_animationPath->insert(0.0, osg::AnimationPath::ControlPoint(vPos1, q1));//��̬��ȷ
	_animationPath->insert(3.0, osg::AnimationPath::ControlPoint(vPos2, q2));//��̬��ȷ
	_animationPath->insert(6.0, osg::AnimationPath::ControlPoint(vPos3, q3));//��̬����
	_animationPath->setLoopMode(osg::AnimationPath::SWING);//����·���ǻذڵ�
	animationPathMp->setAnimationPath(_animationPath);
	/*************************************����������**��*********************************/

	auto manip = new osgEarth::Util::EarthManipulator();



	//�������������������ʹ��һ������������ѡ�񣬰����̡�3�����л���·��������������
	osgGA::KeySwitchMatrixManipulator* keyPtr = new osgGA::KeySwitchMatrixManipulator();
	keyPtr->addMatrixManipulator('1', "earthMan", new EarthManipulator());
	keyPtr->addMatrixManipulator('2', "trakerMan", nodeTrack);
	keyPtr->addMatrixManipulator('3', "animationPathMan", animationPathMp);
	viewer.setCameraManipulator(keyPtr);

	return viewer.run();
}