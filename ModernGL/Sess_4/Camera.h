

#include "Matrix4f.h"
class Camera
{
    public:
        Camera();
        Camera(int width, int height, const Vec3f &pos, const Vec3f &target, const Vec3f &up);
        ~Camera();

        bool onKeyboard(int key);

        const Vec3f& getPosition() const;
        const Vec3f& getTarget() const;
        const Vec3f& getUp()  const;
     
        void setPosition(Vec3f& pos);
        void setTarget(Vec3f& target);
        void setUp(Vec3f& up);
        void setViewport(int width, int height);

        void update();
        Matrix4f getProjectMatrix();

    private:
        Vec3f  m_pos;
        Vec3f  m_target;
        Vec3f  m_up;
        int    m_width;
        int    m_height;
        Matrix4f m_mvpMat;
        Matrix4f m_cameraMat;
        float    stepSize;

};