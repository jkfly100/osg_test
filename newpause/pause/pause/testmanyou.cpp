#include <iostream>
#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA\AnimationPathManipulator>
#include <osgDB\ReadFile>

int test(int argc, char** argv)
{
	osg::ArgumentParser arguments(&argc, argv);
	osgViewer::Viewer viewer(arguments);

	viewer.addEventHandler(new osgViewer::StatsHandler());
	viewer.addEventHandler(new osgViewer::WindowSizeHandler());
	osg::Group* root = new osg::Group();

	root->addChild(osgDB::readNodeFile("cow.osg"));
	root->addChild(osgDB::readNodeFile("glider.osg"));

	viewer.setSceneData(root);

	//ʹ�ö���������
	osgGA::AnimationPathManipulator *animationPathMp = new osgGA::AnimationPathManipulator();
	//��������������ӹؼ�֡
	osg::AnimationPath* _animationPath = new osg::AnimationPath;

	//������ģ���ұߣ���x����20����Ϊ�˿���ģ��
	//Ҫʹ�������Y��˳ʱ����ת90��
	osg::Quat q1(osg::DegreesToRadians(90.0), osg::Y_AXIS);
	osg::Quat q2(osg::DegreesToRadians(90.0), osg::X_AXIS);
	q1 *= q2;

	osg::Quat q3(osg::DegreesToRadians(-90.0), osg::X_AXIS);
	osg::Quat q4(osg::DegreesToRadians(180.0), osg::Y_AXIS);
	q3 *= q4;

	osg::Quat q5(osg::DegreesToRadians(-90.0), osg::Z_AXIS);

	_animationPath->insert(0.0, osg::AnimationPath::ControlPoint(osg::Vec3d(30, 0, 0), q1));
	_animationPath->insert(4.0, osg::AnimationPath::ControlPoint(osg::Vec3d(0, 30, 0), q3));
	_animationPath->insert(8.0, osg::AnimationPath::ControlPoint(osg::Vec3d(0, 0, 30), q5));
	//����·���ǻذڵ�
	_animationPath->setLoopMode(osg::AnimationPath::SWING);
	animationPathMp->setAnimationPath(_animationPath);
	viewer.setCameraManipulator(animationPathMp);

	return viewer.run();
}