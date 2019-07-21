using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UniRx;
using System;

public class ServoController : MonoBehaviour
{
    public HingeJoint hingeJoint;
    public ServoClient servoClient;

    void Start()
    {
        Observable.Interval(TimeSpan.FromMilliseconds(20)).Subscribe(_ =>
        {
            string address = "/servo";
            float stickAngle = hingeJoint.angle;
            int servoAngle = 0;
            if (stickAngle > 0 && stickAngle <= 23)
            {
                servoAngle = (int)stickAngle;
            }
            else if (stickAngle >= 23)
            {
                servoAngle = 23;
            }
            servoClient.SendServoPosition(address, servoAngle);
        }).AddTo(this);
    }
}
