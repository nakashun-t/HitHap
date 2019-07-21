using uOSC;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ServoCallibrator : MonoBehaviour
{
    public ServoClient servoClient;
    void Start()
    {
        string address = "/servo";
        int servoPosition = 0;
        servoClient.SendServoPosition(address, servoPosition);
    }
}
