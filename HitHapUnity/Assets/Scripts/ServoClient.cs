using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using uOSC;

[RequireComponent(typeof(uOscClient))]
public class ServoClient : MonoBehaviour
{
    public void SendServoPosition(string address, int position)
    {
        var client = GetComponent<uOscClient>();
        client.Send(address, position);
    }
}
