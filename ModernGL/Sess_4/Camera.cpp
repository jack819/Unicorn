#include "Camera.h"
#include <GL/glut.h>

#define VIEW_WIDTH  480
#define VIEW_HEIGHT 320
#define FOVY        45.0f

Camera::Camera()
:m_pos(Vec3f(0.0, 0.0, 0.0))
,m_target(Vec3f(0.0, 0.0, 1.0))
,m_up(Vec3f(0.0, 1.0, 0.0))
,m_width(480)
,m_height(320)
,m_mvpMat()
,stepSize(1.0f)
{

}

Camera::Camera(int width, int height, const Vec3f &pos, const Vec3f &target, const Vec3f &up)
:m_pos(pos)
,m_target(target)
,m_up(up)
,m_width(width)
,m_height(height)
,m_mvpMat()
,stepSize(1.0f)
{

}

Camera::~Camera()
{

}

bool 
Camera::onKeyboard(int key)
{
    bool ret = false;
    switch(key) {
        case GLUT_KEY_UP:
        {
            m_pos += (m_target * stepSize);
            ret = true;
            break;
        }
        case GLUT_KEY_DOWN:
        {
            m_pos -= (m_target * stepSize);
            ret = true;
            break;
        }
        case GLUT_KEY_LEFT:
        {
            Vec3f left = m_target.cross(m_up);
            left.normalize();

            left *= stepSize;
            m_pos += left;
            ret = true;
            break;
        }
        case GLUT_KEY_RIGHT:
        {
            Vec3f right = m_up.cross(m_target);
            right.normalize();

            right *= stepSize;
            m_pos += right;
            ret = true;
            break;
        }
        default:
            break;
    }
    return ret;
}


const Vec3f& 
Camera::getPosition() const
{
    return m_pos;
}

const Vec3f& 
Camera::getTarget() const
{
    return m_target;
}

const Vec3f&
Camera::getUp()  const
{
    return m_up;
}

void 
Camera::setPosition(Vec3f& pos)
{
    m_pos = pos;
    update();
}

void 
Camera::setTarget(Vec3f& target)
{
    m_target = target;
    update();
}

void 
Camera::setUp(Vec3f& up)
{
    m_up = up;
    update();
}

void 
Camera::setViewport(int width, int height)
{
    m_width = width;
    m_height = height;
    update();
}

void 
Camera::update()
{
    m_cameraMat = Matrix4f::lookat(m_pos, m_target, m_up);
}

Matrix4f 
Camera::getProjectMatrix()
{
    update();
    
    Matrix4f  projectMat;

    float mNear = 1.0f;
    float mFar =  100.0f;

    float ymax = mNear * tan(FOVY * 0.5);
    float ymin = - ymax;

    float xmin = ymin * ((float)VIEW_WIDTH / VIEW_HEIGHT);
    float xmax = -xmin;

    projectMat = Matrix4f::frustum(xmin, xmax, ymin, ymax, mNear, mFar);

    Matrix4f  projMat;
    projMat = projectMat * m_cameraMat;

    return projMat;
}