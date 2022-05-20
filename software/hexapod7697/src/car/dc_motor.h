#pragma once

namespace car { 

    class DCMotor {
    public:
        static void init(void);

    public:
        DCMotor(int wheelIndex);

        // angle: 0 means center, range is -60~60
        void setSpeed(float value);
        float getSpeed(void);

    private:
        float speed_;
        int wheel_;
        int pwmIndex_;
        int wheelIndex_;
    };

}