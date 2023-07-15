using System;
using System.Runtime.InteropServices;
using UnityEngine;

public class TestNativeLogger : MonoBehaviour
{

    [DllImport("NativeLogPlugin")]
    public static extern void TestLog();

    void Start()
    {
        TestLog();
    }
}
