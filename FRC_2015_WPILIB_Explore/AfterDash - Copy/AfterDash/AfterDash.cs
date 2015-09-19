using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms; 
using System.Net;
using System.Net.Sockets;
using System.Threading;
using AquaControls;
using System.Runtime.InteropServices;

namespace AfterDash
{
    public partial class AfterDash : Form
    {
        DashboardData dataReciever;
        AxisCamera axisCamera;
        Rectangle[] shootData;
        string[] particleAreas;
        string[] particleColors;

        public AfterDash()
        {
            InitializeComponent();
        }

        public void DisplayData(string stringData)
        {
            string[] specific_packets = stringData.Split('$');
            for (int i = 0; i < specific_packets.Length; i++)
            {
                string[] packet = specific_packets[i].Split(':');
                #region Shooter Information
                if (packet[0].Equals("topWheel"))
                {
                    txt_topWheelVolts.Invoke(new MethodInvoker(delegate { txt_topWheelVolts.Text = (Convert.ToDouble(packet[1].ToString()) * 100).ToString(); }));
                    topWheelGauge.Invoke(new MethodInvoker(delegate { topWheelGauge.CircularGauges[0].Pointers[0].Value = Convert.ToDouble(packet[1].ToString()) * 100; }));
                }
                if (packet[0].Equals("botWheel"))
                {
                    txt_bottomWheelVolts.Invoke(new MethodInvoker(delegate { txt_bottomWheelVolts.Text = packet[1].ToString(); }));
                }
                /*if (packet[0].Equals("wheelSpeed"))
                {
                    topWheelGauge.Invoke(new MethodInvoker(delegate {
                        try
                        {
                            topWheelGauge.CircularGauges[0].Pointers[1].Value = Convert.ToDouble(packet[1].ToString()) * 100;
                        }
                        catch (Exception e) { }
                    }));
                }*/
                if (packet[0].Equals("shotInfo"))
                {
                    string[] trackInfoRaw = packet[1].Split('#');
                    txt_Debug.Invoke(new MethodInvoker(delegate { txt_Debug.Text = trackInfoRaw[0].ToString(); }));
                    if (trackInfoRaw.Length - 1 > 0)
                    {
                        shootData = new Rectangle[trackInfoRaw.Length - 1];
                        particleAreas = new string[trackInfoRaw.Length - 1];
                        particleColors = new string[trackInfoRaw.Length - 1];
                        for (int x = 0; x < trackInfoRaw.Length - 1; x++)
                        {
                            string[] trackInfo = trackInfoRaw[x].Split(','); 
                            shootData[x] = new Rectangle(myAMC.Location.X + Convert.ToInt32(Convert.ToDouble(trackInfo[0])) - (Convert.ToInt32(trackInfo[2]) / 2), myAMC.Location.Y + Convert.ToInt32(Convert.ToDouble(trackInfo[1])) - (Convert.ToInt32(trackInfo[3]) / 2), Convert.ToInt32(trackInfo[2]), Convert.ToInt32(trackInfo[3]));
                            particleAreas[x] = trackInfo[4];
                            particleColors[x] = trackInfo[5];
                            //MessageBox.Show(shootData[x].ToString());
                        }

                        // shootData = new Rectangle(myAMC.Location.X + Convert.ToInt32(Convert.ToDouble(trackInfo[0])) - (Convert.ToInt32(trackInfo[3])/2), myAMC.Location.Y + Convert.ToInt32(Convert.ToDouble(trackInfo[1])) - (Convert.ToInt32(trackInfo[3])/2), Convert.ToInt32(trackInfo[2]), Convert.ToInt32(trackInfo[3]));
                        //trackPanel.Invoke(new MethodInvoker(delegate { trackPanel.Refresh(); }));
                    }
                    //this.Invoke(new MethodInvoker(delegate { this.Refresh(); }));
                    //this.Invoke(new MethodInvoker(delegate { this.Invalidate(); }));
                    IntPtr desktopDC = GetDC(IntPtr.Zero);
                    Graphics g = Graphics.FromHdc(desktopDC);
                    Pen myPen = new Pen(System.Drawing.Color.Blue, 5);

                    //this.Invoke(new MethodInvoker(delegate { this.Invalidate(); }));

                    for (int x = 0; x < shootData.Length; x++)
                    {
                        if(particleColors[x].Equals("G"))
                            myPen = new Pen(Color.Green, 5);
                        else
                            myPen = new Pen(Color.Blue, 5);

                        g.DrawRectangle(myPen, shootData[x]);
                        g.DrawString(particleAreas[x], new Font(FontFamily.GenericSansSerif, 12, FontStyle.Bold), new SolidBrush(Color.White), shootData[x]);
                    }
                    g.Flush();
                    g.Dispose();
                    Array.Clear(shootData, 0, shootData.Length);
                    Array.Clear(particleAreas, 0, particleAreas.Length);
                }
                #endregion
            }
        }

        private void AfterDash_Load(object sender, EventArgs e)
        {
            this.BringToFront();
            this.Location = new Point(0, 0);
            dataReciever = new DashboardData(this);
            dataReciever.StartDashboard();

            axisCamera = new AxisCamera(this);
            axisCamera.StartStream();
        }

        private void AfterDash_FormClosing(object sender, FormClosingEventArgs e)
        {
            dataReciever.StopDashboard();
            axisCamera.StopStream();
        }

        [DllImport("User32.dll")]
        public static extern IntPtr GetDC(IntPtr hwnd);

        [DllImport("User32.dll")]
        public static extern void ReleaseDC(IntPtr dc);
    }
}

