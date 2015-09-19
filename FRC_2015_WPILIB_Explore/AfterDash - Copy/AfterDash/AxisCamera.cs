using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using AxAXISMEDIACONTROLLib;
using AquaControls;
using Dundas;

namespace AfterDash
{
    class AxisCamera
    {

        Thread recvThread;
        AfterDash dashboard;

        string sourceURL = "http://10.2.63.11/axis-cgi/jpg/image.cgi?resolution=640x480";
        byte[] buffer = new byte[100000];
        int read, total = 0;

        public AxisCamera(AfterDash dash)
        {
            dashboard = dash;
            recvThread = new Thread(recv);
        }

        public void StartStream()
        {
            recvThread.Start();
        }

        public void StopStream()
        {
            recvThread.Abort();
        }

        void recv()
        {
            try
            {
                // Set properties, deciding what url completion to use by MediaType.
                dashboard.myAMC.MediaUsername = "FRC";
                dashboard.myAMC.MediaPassword = "FRC";
                dashboard.myAMC.MediaType = "mjpg";
                dashboard.myAMC.MediaURL = "http://10.2.63.11/axis-cgi/mjpg/video.cgi";

                // Start the streaming
                dashboard.myAMC.Play();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Unable to play stream: " + ex.Message);
            }
        }
    }
}
